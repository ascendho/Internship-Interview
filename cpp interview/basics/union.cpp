// 编译指令：g++ union.cpp -o union
// 运行指令：./union

/*
    1. Union 的核心：共享内存，大小 =“装下最大成员” 且 “满足最大对齐模数” 的最小字节数。
    2. Struct 的核心：独立内存，成员按顺序存储（需对齐），总大小 =“成员 + 填充” 且 “满足最大对齐模数”（顺序会影响大小）。
    3. 内存对齐的本质：牺牲少量内存空白，换取 CPU 更快的内存访问效率（这是编译器的默认优化行为）。
*/

// 包含标准输入输出头文件，用于使用 cout 打印信息
#include <iostream>
using namespace std;

// 定义联合体 u11
typedef union
{
    char c[10]; // 字符数组，占用10字节
    char cc1;   // 单个字符，占用1字节
} u11;
// union 大小计算：
// 最大成员是 c[10]，大小为10字节。
// 最大成员的对齐要求是 alignof(char) = 1。
// 所以 sizeof(u11) = 10 字节（10是1的倍数）。

// 定义联合体 u22
typedef union
{
    char c[10]; // 字符数组，占用10字节
    int i;      // 整型，占用4字节，对齐要求为4字节
} u22;
// union 大小计算：
// 最大成员是 c[10]，大小为10字节。
// 最大成员的对齐要求是 alignof(int) = 4。
// 所以 union 的大小必须是 >=10 且是4的倍数的最小整数，即 12 字节。

// 定义联合体 u33
typedef union
{
    char c[10]; // 字符数组，占用10字节
    double d;   // 双精度浮点，占用8字节，对齐要求为8字节
} u33;
// union 大小计算：
// 最大成员是 c[10]，大小为10字节。
// 最大成员的对齐要求是 alignof(double) = 8。
// 所以 union 的大小必须是 >=10 且是8的倍数的最小整数，即 16 字节。

// 定义结构体 s11
typedef struct s1
{
    char c;   // 1字节
    double d; // 8字节，对齐要求为8字节
} s11;
// struct 内存对齐计算：
// 1. 结构体的对齐模数是其最大成员 double 的对齐要求，即8字节。
// 2. char c 占1字节，为了让后面的 double 地址对齐到8的倍数，需要填充7字节。
// 3. double d 占8字节。
// 4. 总大小 = 1 + 7 + 8 = 16字节。16是8的倍数，无需末尾填充。
// 所以 sizeof(s11) = 16 字节。

// 定义结构体 s22
typedef struct s2
{
    char c;   // 1字节
    char cc;  // 1字节
    double d; // 8字节，对齐要求为8字节
} s22;
// struct 内存对齐计算：
// 1. 对齐模数为8字节。
// 2. char c (1) + char cc (1) = 2字节。
// 3. 为了让 double d 地址对齐到8的倍数，需要填充 8 - 2 = 6字节。
// 4. double d 占8字节。
// 5. 总大小 = 2 + 6 + 8 = 16字节。16是8的倍数。
// 所以 sizeof(s22) = 16 字节。

// 定义结构体 s33
typedef struct s3
{
    char c;   // 1字节
    double d; // 8字节，对齐要求为8字节
    char cc;  // 1字节
} s33;
// struct 内存对齐计算：
// 1. 对齐模数为8字节。
// 2. char c (1) + 填充(7) + double d (8) = 16字节。
// 3. char cc 占1字节，此时总大小为17字节。
// 4. 结构体总大小必须是对齐模数(8)的倍数，所以需要在末尾填充 8 - (17 % 8) = 7字节。
// 5. 总大小 = 17 + 7 = 24字节。
// 所以 sizeof(s33) = 24 字节。

int main()
{
    // 打印各个 union 和 struct 的大小，验证我们的计算
    cout << sizeof(u11) << endl; // 输出：10
    cout << sizeof(u22) << endl; // 输出：12
    cout << sizeof(u33) << endl; // 输出：16
    cout << sizeof(s11) << endl; // 输出：16
    cout << sizeof(s22) << endl; // 输出：16
    cout << sizeof(s33) << endl; // 输出：24

    // 打印基础类型的大小作为参考
    cout << sizeof(int) << endl;    // 输出：4
    cout << sizeof(double) << endl; // 输出：8

    return 0;
}