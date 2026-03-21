// 编译指令：g++ variadic_template_demo.cpp -o variadic_template_demo
// 运行指令：./variadic_template_demo

#include <iostream>
#include <string>
using namespace std;

// ==================== 1. 递归终止函数（参数包为空时调用）
// 当参数包只剩最后1个参数时，匹配这个单参数模板，终止递归
template <typename T>
void print_fun(const T &t)
{
    cout << t << endl; // 最后一个元素，换行结束打印
}

// ==================== 2. 可变参数模板核心函数（递归展开参数包）
// typename... Args ：模板参数包，代表0个或多个任意类型参数
// const Args &...args ：函数参数包，代表0个或多个函数入参
template <typename T, typename... Args>
void print_fun(const T &t, const Args &...args)
{
    cout << t << " ";   // 处理当前参数包的第一个参数
    print_fun(args...); // 递归展开：把剩余参数包继续传递，处理下一个参数
}

// ==================== 3. 补充：sizeof... 运算符（统计参数包的元素个数）
// 专门用于计算参数包中的参数数量，是编译期常量，无运行时开销
template <typename... Args>
void print_args_count(const Args &...args)
{
    /*
     * sizeof... 是专门为可变参数模板设计的运算符，
     * 用于计算参数包中包含的元素个数（注意是 “个数”，不是字节数），
     * 操作数只能是 “参数包名”（模板参数包或函数参数包均可）。
     * 和 sizeof 是完全不同的两个运算符
     *
     */
    cout << "当前传入的参数总个数：" << sizeof...(args) << endl;
}

// ==================== 4. 补充：C++17 折叠表达式（更简洁的参数包展开，无需递归）
// 现代C++的简化写法，一行代码完成参数包遍历，无需写递归终止函数
template <typename... Args>
void print_fold(const Args &...args)
{
    // 左折叠表达式：逐个打印参数，用空格分隔，最后换行
    (cout << ... << (cout << args, " ")) << endl;
}

int main()
{
    cout << "===== 原示例基础测试 =====" << endl;
    // 原示例的调用：3个字符串参数
    print_fun("Hello", "world", "!");

    cout << "\n===== 多类型混合参数测试 =====" << endl;
    // 支持任意数量、任意可打印类型的参数（字符串、整数、浮点数、string类）
    print_fun("年龄：", 25, "，身高：", 178.5, "，姓名：", string("张三"));

    cout << "\n===== 参数包个数统计测试 =====" << endl;
    print_args_count(1, 2, 3, "test", 3.14);
    print_args_count("Hello", "world");

    cout << "\n===== C++17 折叠表达式简化版测试 =====" << endl;
    print_fold("折叠", "表达式", "测试", 100, 66.6);

    return 0;
}