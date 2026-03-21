// 编译指令：g++ virtual_override.cpp -o virtual_override
// 运行指令：./virtual_override

#include <iostream>
using namespace std;

// 定义基类 Base
class Base
{
public:
    // 声明虚函数 fun：加virtual后，该函数支持“运行时多态”
    virtual void fun(int tmp)
    {
        cout << "Base::fun(int tmp) : " << tmp << endl;
    }
};

// 定义派生类 Derived，公有继承 Base
class Derived : public Base
{
public:
    // 重写（override）基类的虚函数 fun
    // 注：派生类的virtual可省略（继承自基类），但显式写更易读
    virtual void fun(int tmp) override
    {
        cout << "Derived::fun(int tmp) : " << tmp << endl;
    }
};

int main()
{
    // 核心：基类指针 p 指向派生类对象（Derived实例）
    Base *p = new Derived();

    // 调用 fun 函数：因fun是虚函数，执行派生类Derived的fun版本
    p->fun(3); // 输出：Derived::fun(int) : 3

    return 0;
}

/*
 * 为什么要加 virtual?
 * C++ 中函数调用默认是 静态绑定（编译时绑定）—— 编译器根据「指针 / 引用的类型」决定调用哪个函数，
 * 而非「指针 / 引用指向的对象的实际类型」。virtual 的核心作用是将绑定方式改为 动态绑定（运行时绑定）。
 *
 */

/*
 * 加 virtual 的核心作用：
 * 1. 开启动态绑定：编译器不在编译时确定调用哪个函数，而是在程序运行时，根据指针指向的「对象实际类型」（Derived），调用对应的重写函数；
 * 2. 实现多态：基类指针可以指向任意派生类对象，调用 fun 时自动匹配派生类的版本，这是面向对象 “多态性” 的核心体现；
 * 3. 底层实现：编译器会为含虚函数的类生成「虚函数表（vtable）」，存储虚函数地址；
 *            对象会包含一个「虚表指针（vptr）」指向所属类的虚表。运行时通过 vptr 找到实际类型的虚函数，完成调用。
 *
 */