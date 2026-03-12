// 编译指令：g++ double_free.cpp -o double_free_demo
// 运行指令：./double_free_demo

#include <iostream>
#include <memory>

class MyClass
{
public:
    MyClass() { std::cout << "[MyClass] 构造函数被调用" << std::endl; }
    ~MyClass() { std::cout << "[MyClass] 析构函数被调用" << std::endl; }
};

int main()
{
    // 步骤1：创建裸指针（一栋房子）
    MyClass *raw = new MyClass();

    // 步骤2：从同一个裸指针创建两个独立的shared_ptr（两个管家）
    std::shared_ptr<MyClass> ptr1(raw); // 管家1：以为自己是唯一管这栋房子的
    std::shared_ptr<MyClass> ptr2(raw); // 管家2：也以为自己是唯一管这栋房子的

    // 步骤3：main函数结束，里面的局部变量会按“定义的逆序”销毁：先销毁 ptr2，再销毁 ptr1
    // 因此，第一次触发 MyClass 析构的是 ptr2，不是 ptr1
    return 0;
}

/*
 * 1. 重复释放的根源：多个 shared_ptr 从同一裸指针构造 → 引用计数独立 → 每个 shared_ptr 都尝试释放裸指针；
 * 2. shared_ptr 的计数规则：只有拷贝 / 赋值 shared_ptr 才会共享计数，从裸指针构造的 shared_ptr 计数互不相关；
      正确实践：
 *              优先用 std::make_shared<T>() 创建 shared_ptr，全程不碰裸指针；
 *              若必须用裸指针，仅让一个 shared_ptr 接管，其他通过拷贝获取。
 * 3. 重复释放是 C++ 中非常危险的未定义行为，轻则程序崩溃，重则破坏内存布局导致诡异 bug，
 *    而避免的核心就是「不让多个 shared_ptr 独立管理同一个裸指针」。
 *
 */