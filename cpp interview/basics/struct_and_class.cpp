// 编译指令：g++ struct_and_class.cpp -o struct_and_class
// 运行指令：./struct_and_class

// 引入C++标准输入输出头文件（用于打印提示信息）
#include <iostream>

// 基类：struct关键字定义，成员默认public
struct Base
{
    int x; // public成员（struct默认）
};

// 1. struct默认public继承：
// Base的public成员（x）在Derived1中仍为public
struct Derived1 : Base
{
    // 类内可直接访问Base::x（继承的public成员）
    void setX(int val)
    {
        x = val; // 合法：直接访问基类的public成员
    }
};

// 2. class默认private继承：
// Base的public成员（x）在Derived2中变为private
class Derived2 : Base
{
    // 类内可直接访问Base::x（虽然继承方式是private，但类内仍可访问）
    void setX(int val)
    {
        x = val; // 合法：类内访问继承的private成员
    }
};

int main()
{
    // ====== 测试Derived1（public继承）======
    Derived1 d1;
    d1.x = 10; // 合法：public继承，x对外仍为public
    std::cout << "Derived1对象访问x：" << d1.x << std::endl;

    // ====== 测试Derived2（private继承）======
    Derived2 d2;
    // d2.x = 20; // 编译错误！private继承，x对外是private，外部无法访问
    // 如需修改Derived2的x，需通过类内的成员函数（如setX）
    // 但由于setX是Derived2的private成员（class默认），外部也无法直接调用
    // 如需外部调用，需将setX声明为public：
    // class Derived2 : Base {
    // public: // 显式声明public
    //     void setX(int val) { x = val; }
    // };

    return 0;
}