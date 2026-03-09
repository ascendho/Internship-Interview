// 编译指令：g++ explicit_constructor.cpp -o explicit_constructor
// 运行指令：./explicit_constructor

#include <iostream>
using namespace std;

class A
{
public:      
    int var; 

    /**
     * @brief 类A的构造函数，带单个int类型参数
     * @param tmp 用于初始化成员变量var的整数参数
     * @note explicit关键字：禁止编译器将int类型隐式转换为A类型对象
     */
    explicit A(int tmp)
    {
        var = tmp;
        cout << var << endl;
    }
};

int main()
{
    // 合法：显式调用构造函数初始化A类对象ex
    // explicit构造函数允许“直接初始化”的方式创建对象
    A ex(100);

    // 编译报错：error: conversion from 'int' to non-scalar type 'A' requested
    // 原因：explicit关键字禁止了int到A的隐式转换，而“拷贝初始化（=）”会触发隐式转换
    // 对比：如果构造函数没有explicit，这行代码会隐式调用A(10)创建临时对象，再初始化ex1
    // A ex1 = 10;

    return 0;
}