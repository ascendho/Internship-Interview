// 编译指令：g++ nullptr_vs_null_demo.cpp -o nullptr_vs_null_demo
// 运行指令：./nullptr_vs_null_demo

#include <iostream>
#include <typeinfo>
#include <cstddef>
using namespace std;

// 函数重载示例
void fun(char const *p)
{
    cout << "✅ 匹配到：fun(char const* p) —— 指针类型重载\n";
}
void fun(int tmp)
{
    cout << "⚠️  匹配到：fun(int tmp) —— 整型重载\n";
}

int main()
{
    // 场景1：类型差异对比
    cout << "=== 场景1：类型差异对比 ===\n";
    cout << "NULL 的本质值：" << NULL << "（注意：它是 #define NULL 0）\n";
    cout << "nullptr 的类型名：" << typeid(nullptr).name() << "\n";
    cout << "nullptr_t 类型名：" << typeid(nullptr_t).name() << "\n\n";

    // 场景2：函数重载歧义测试
    cout << "=== 场景2：函数重载歧义测试 ===\n";
    cout << "调用 fun(nullptr) → ";
    fun(nullptr);

    // ❌ 取消注释后，编译会直接报错：
    // error: call of overloaded 'fun(NULL)' is ambiguous
    // 原因：NULL 本质是 0，既可以隐式转 int，也可以隐式转指针，编译器不知道选哪个重载
    // cout << "调用 fun(NULL) → ";
    // fun(NULL);

    cout << "\n";

    // 场景3：类型转换测试（修复：把 char* 转成 void* 打印，避免乱码）
    cout << "=== 场景3：类型转换测试 ===\n";
    int *p_int = nullptr;
    char *p_char = nullptr;
    void *p_void = nullptr;

    cout << "int* p_int = nullptr → 地址值：" << p_int << "\n";
    // 修复：转成 void* 再打印，避免 cout 把 char* 当字符串处理
    cout << "char* p_char = nullptr → 地址值：" << static_cast<void *>(p_char) << "\n";
    cout << "void* p_void = nullptr → 地址值：" << p_void << "\n";

    // 这行原本被截断，现在会正常输出
    int y = NULL;
    cout << "int y = NULL → y = " << y << "（NULL 本质是 0，所以可以赋值给 int）\n";

    return 0;
}