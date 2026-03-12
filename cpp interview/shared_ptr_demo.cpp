// 编译指令：g++ shared_ptr_demo.cpp -o shared_ptr_demo
// 运行指令：./shared_ptr_demo

#include <iostream>
#include <memory> // 包含 shared_ptr/make_shared 等智能指针头文件

// 自定义类，用于观察构造/析构时机，直观体现内存管理
class MyClass
{
public:
    MyClass() { std::cout << "[MyClass] 构造函数被调用" << std::endl; }
    ~MyClass() { std::cout << "[MyClass] 析构函数被调用" << std::endl; }
};

int main()
{
    // ==================================================
    // 场景1：初始化 shared_ptr，引用计数 = 1
    // ==================================================
    std::cout << "=== 场景1：初始化 shared_ptr ===" << std::endl;
    std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>();
    std::cout << "ptr1 引用计数: " << ptr1.use_count() << "\n"
              << std::endl;

    // ==================================================
    // 场景2：拷贝构造，共享所有权，引用计数 +1
    // ==================================================
    std::cout << "=== 场景2：拷贝构造共享所有权 ===" << std::endl;
    std::shared_ptr<MyClass> ptr2 = ptr1; // 拷贝构造，共享同一个对象
    std::shared_ptr<MyClass> ptr3 = ptr1;
    std::cout << "ptr1 引用计数: " << ptr1.use_count() << "\n"
              << std::endl;

    // ==================================================
    // 场景3：reset() 释放所有权，引用计数 -1
    // ==================================================
    std::cout << "=== 场景3：reset() 释放所有权 ===" << std::endl;
    ptr2.reset(); // 主动释放 ptr2 的所有权
    std::cout << "ptr1 引用计数: " << ptr1.use_count() << "\n"
              << std::endl;

    // ==================================================
    // 场景4：赋值为 nullptr，等价于 reset()，引用计数 -1
    // ==================================================
    std::cout << "=== 场景4：赋值 nullptr 释放所有权 ===" << std::endl;
    ptr3 = nullptr; // 与 reset() 效果一致，释放 ptr3 的所有权
    std::cout << "ptr1 引用计数: " << ptr1.use_count() << "\n"
              << std::endl;

    // ==================================================
    // 场景5：移动语义，转移所有权（原指针失效，引用计数不变）
    // ==================================================
    std::cout << "=== 场景5：移动语义转移所有权 ===" << std::endl;
    std::shared_ptr<MyClass> ptr4 = std::move(ptr1); // 所有权从 ptr1 转移到 ptr4
    std::cout << "ptr1 引用计数: " << ptr1.use_count() << "  (ptr1 已失效)" << std::endl;
    std::cout << "ptr4 引用计数: " << ptr4.use_count() << "\n"
              << std::endl;

    // ==================================================
    // 场景6：离开作用域，引用计数归 0，自动释放内存
    // ==================================================
    std::cout << "=== 场景6：离开作用域，自动释放内存 ===" << std::endl;
    // 当 ptr4 离开 main 作用域时，引用计数变为 0，MyClass 对象自动被销毁
    return 0;
}

/*
 *  1. 优先使用 std::make_shared<T>()：比直接 new 更高效，能一次性分配对象和控制块内存，避免内存泄漏。
 *  2. 避免循环引用：若两个对象互相持有 shared_ptr，会导致引用计数永远无法归 0，内存泄漏 —— 需配合 std::weak_ptr 解决。
 *  3. 不要混合使用裸指针和 shared_ptr：比如 MyClass* raw = new MyClass();
 *     shared_ptr<MyClass> ptr(raw);，若多个 shared_ptr 从同一个裸指针构造，会导致重复释放。
 *     原因：shared_ptr 的 “引用计数” 是绑定到 shared_ptr 对象本身的，而非绑定到裸指针。
 *          如果多个 shared_ptr 从同一个裸指针构造，它们的引用计数是相互独立的（各算各的），每个 shared_ptr 都会在自己销毁时尝试释放裸指针，
 *          导致「重复释放同一块内存」（double free），触发程序崩溃 / 未定义行为。
 *
 */