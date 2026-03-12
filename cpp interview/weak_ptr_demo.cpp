// 编译指令：g++ weak_ptr_demo.cpp -o weak_ptr_demo
// 运行指令：./weak_ptr_demo

#include <iostream>
#include <memory>

// 前向声明类 B
class B;

// -------------------------- 【正确版本】使用 weak_ptr 打破循环引用 --------------------------
class A
{
public:
    std::shared_ptr<B> b_ptr; // A 持有 B 的 shared_ptr
    A() { std::cout << "[A] 构造函数被调用" << std::endl; }
    ~A() { std::cout << "[A] 析构函数被调用" << std::endl; }
};

class B
{
public:
    // ✅ 关键：使用 weak_ptr 不会增加引用计数，打破循环引用
    std::weak_ptr<A> a_ptr;
    B() { std::cout << "[B] 构造函数被调用" << std::endl; }
    ~B() { std::cout << "[B] 析构函数被调用" << std::endl; }
};

// -------------------------- 【错误版本】全用 shared_ptr 导致循环引用 --------------------------
// 前向声明类 B_Bad
class B_Bad;

class A_Bad
{
public:
    std::shared_ptr<B_Bad> b_ptr;
    A_Bad() { std::cout << "[A_Bad] 构造函数被调用" << std::endl; }
    ~A_Bad() { std::cout << "[A_Bad] 析构函数被调用" << std::endl; }
};

class B_Bad
{
public:
    // ❌ 错误：使用 shared_ptr 会形成循环引用
    std::shared_ptr<A_Bad> a_ptr;
    B_Bad() { std::cout << "[B_Bad] 构造函数被调用" << std::endl; }
    ~B_Bad() { std::cout << "[B_Bad] 析构函数被调用" << std::endl; }
};

// -------------------------- 主函数：对比演示 --------------------------
int main()
{
    // ==================================================
    // 场景1：错误用法（全用 shared_ptr，循环引用导致内存泄漏）
    // ==================================================
    std::cout << "===== 场景1：错误用法（循环引用 → 内存泄漏） =====" << std::endl;
    {
        std::shared_ptr<A_Bad> a_bad = std::make_shared<A_Bad>();
        std::shared_ptr<B_Bad> b_bad = std::make_shared<B_Bad>();
        // 互相持有 shared_ptr，形成循环引用
        a_bad->b_ptr = b_bad;
        b_bad->a_ptr = a_bad;

        std::cout << "a_bad 引用计数: " << a_bad.use_count() << std::endl;
        std::cout << "b_bad 引用计数: " << b_bad.use_count() << std::endl;
    }
    // 离开作用域后，A_Bad/B_Bad 的析构函数不会被调用！内存泄漏
    std::cout << "⚠️  注意：A_Bad 和 B_Bad 的析构函数未执行，内存泄漏！\n"
              << std::endl;

    // ==================================================
    // 场景2：正确用法（B 中用 weak_ptr，打破循环引用）
    // ==================================================
    std::cout << "===== 场景2：正确用法（weak_ptr 打破循环 → 正常释放） =====" << std::endl;
    std::weak_ptr<A> weak_a; // 用于观察 A 的生命周期（不增加引用计数）
    {
        std::shared_ptr<A> a = std::make_shared<A>();
        std::shared_ptr<B> b = std::make_shared<B>();
        // A 持有 B 的 shared_ptr，B 持有 A 的 weak_ptr
        a->b_ptr = b;
        b->a_ptr = a;

        std::cout << "a 引用计数: " << a.use_count() << std::endl;
        std::cout << "b 引用计数: " << b.use_count() << std::endl;

        // 用 weak_ptr 观察对象生命周期
        weak_a = a;
        std::cout << "weak_a 观察到的引用计数: " << weak_a.use_count() << std::endl;
        std::cout << "weak_a 是否过期（对象已释放）: " << (weak_a.expired() ? "是" : "否") << std::endl;

        // 演示 weak_ptr::lock()：获取有效的 shared_ptr（若对象未被释放）
        if (auto locked_a = weak_a.lock())
        {
            std::cout << "weak_a lock 成功，locked_a 引用计数: " << locked_a.use_count() << std::endl;
        }
    }

    // 离开作用域后，A/B 的析构函数正常调用，内存正确释放
    std::cout << "✅ 注意：A 和 B 的析构函数已执行，内存正常释放！" << std::endl;

    // 再次观察 weak_a：对象已释放，expired() 返回 true
    std::cout << "weak_a 是否过期（对象已释放）: " << (weak_a.expired() ? "是" : "否") << std::endl;
    if (weak_a.lock() == nullptr)
    {
        std::cout << "weak_a lock 失败，对象已被释放" << std::endl;
    }

    return 0;
}

/*
 * 临时变量（a_bad/b_bad）销毁 → 只是 “归还了自己手里的所有权”，但对象内部的成员指针（a_bad->b_ptr）只有当对象本身析构时才会销毁；
 * 场景 1 的死循环：对象因为计数≠0 无法析构 → 成员指针一直存在 → 对方对象计数也≠0 → 永远析构不了；
 * 场景 2 的关键：weak_ptr 不算 “所有权”，让一方计数能归 0 → 对象析构 → 成员指针销毁 → 另一方计数也归 0。
 *
 */