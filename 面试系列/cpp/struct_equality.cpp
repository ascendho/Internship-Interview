// 编译指令：g++ -o struct_equality struct_equality.cpp
// 运行指令：./struct_equality

#include <iostream>
#include <cstring> // 必须包含memcmp的头文件
using namespace std;

// 定义结构体：char(1字节) + int(4字节)，因字节对齐会填充3个字节
struct A
{
    char c;
    int val;

    // 修复语法错误：去掉多余的};
    A(char c_tmp, int tmp) : c(c_tmp), val(tmp) {}

    // 优化：无需友元，直接重载为成员函数（更简洁）
    // 结构体A的成员是public的，无需将operator==声明为友元，直接定义为普通非成员函数即可，简化代码。
    bool operator==(const A &other) const
    {
        return this->c == other.c && this->val == other.val;
    }
};

int main()
{
    // ========== 场景1：成员值相同，验证重载==的正确性 ==========
    A a1('x', 100);
    A a2('x', 100);

    // 1. 用重载的==比较（正确：成员相同则相等）
    if (a1 == a2)
        cout << "【重载==】a1 和 a2 相等" << endl;
    else
        cout << "【重载==】a1 和 a2 不相等" << endl;

    // 2. 用memcmp比较（错误：填充字节随机，导致判为不相等）
    /*
     * C++ 编译器的「字节对齐填充」只是为了满足 CPU 的内存访问效率，
     * 在结构体成员之间 / 末尾 “占位置”，但不会主动初始化这些填充字节。
     * 这些填充字节的值，取决于这块内存区域上一次被使用时留下的残留数据
     *（可以理解为 “内存里的垃圾”）
     * 它适合对比字符串、纯数组等 “无填充的连续字节序列”；
     * 但绝对不能用来对比结构体 / 类
     *（会把填充字节、虚函数表指针等无意义字节纳入对比，导致误判）；
     *
     */

    // 注意：memcmp按字节比较，结构体A的大小是8字节（1+3填充+4）
    /*
     * memcmp 的核心原理是：无类型感知的逐字节内存对比，
     * 它只关注 “内存里的原始字节值”，不理解字节的 “语义”
     *（哪些是有效数据，哪些是填充 / 无用数据）。
     *
     */

    if (memcmp(&a1, &a2, sizeof(A)) == 0)
        cout << "【memcmp】a1 和 a2 相等" << endl;
    else
        cout << "【memcmp】a1 和 a2 不相等（填充字节导致误判）" << endl;

    // ========== 场景2：成员值不同，两者都判为不相等 ==========
    A a3('a', 90);
    A a4('b', 80);
    cout << "\n--- 成员值不同的情况 ---" << endl;
    if (a3 == a4)
        cout << "【重载==】a3 和 a4 相等" << endl;
    else
        cout << "【重载==】a3 和 a4 不相等" << endl;

    if (memcmp(&a3, &a4, sizeof(A)) == 0)
        cout << "【memcmp】a3 和 a4 相等" << endl;
    else
        cout << "【memcmp】a3 和 a4 不相等" << endl;

    return 0;
}