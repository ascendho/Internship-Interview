// 编译指令：g++ const.cpp -o const
// 运行指令：./const

#include <iostream>
#define INTPTR1 int *
typedef int *INTPTR2;
using namespace std;

int main()
{
    int var = 1;
    int var2 = 2;

    const INTPTR1 p5 = &var;         // 等价于 const int * p5; 常量指针
    cout << "*p5 = " << *p5 << endl; // 输出 1
    // *p5 = 10; // ❌ 非法：assignment of read-only location '*p5'
    p5 = &var2;                      // ✅ 合法：指针本身可改
    cout << "*p5 = " << *p5 << endl; // 输出 2

    const INTPTR2 p6 = &var; // 等价于 int * const p6; 指针常量
    *p6 = 10;                // ✅ 合法：指向的内容可改
    // p6 = &var2; // ❌ 非法：assignment of read-only variable 'p6'

    cout << "var = " << var << endl; // 输出 10
    return 0;
}