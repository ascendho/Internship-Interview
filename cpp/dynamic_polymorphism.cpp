// 编译指令：g++ dynamic_polymorphism.cpp -o dynamic_polymorphism
// 运行指令：./dynamic_polymorphism

#include <iostream>
using namespace std;

/**
 * @brief 抽象基类：形状（定义所有图形的通用接口）
 * @note 包含虚函数，作为多态的核心基类，必须定义虚析构函数
 */
class Shape
{
public:
    /**
     * @brief 虚函数：绘图接口（核心多态接口）
     * @note 加virtual后支持动态绑定，派生类可重写该函数实现具体绘图逻辑
     */
    virtual void draw()
    {
        cout << "Drawing Shape" << endl; // 基类默认实现
    }

    /**
     * @brief 虚析构函数（C++多态基类的必写项）
     * @details 1. = default：C++11语法，编译器生成默认析构函数（等价于空函数体）；
     *          2. 加virtual：确保通过基类指针删除派生类对象时，先调用派生类析构，再调用基类析构；
     *          3. 若不写虚析构，派生类析构函数不会执行，易导致内存/资源泄漏。
     */
    virtual ~Shape() = default;
};

/**
 * @brief 派生类：圆形（公有继承Shape基类）
 * @note 重写基类的draw虚函数，实现圆形的绘图逻辑
 */
class Circle : public Shape
{
public:
    /**
     * @brief 重写基类虚函数draw
     * @details override关键字：显式标注该函数是重写基类的虚函数，编译器会检查：
     *          1. 基类是否有该虚函数；
     *          2. 函数签名（返回值、参数、const等）是否完全匹配；
     *          避免因签名不一致导致“重定义而非重写”的低级错误。
     */
    void draw() override
    {
        cout << "Drawing Circle" << endl; // 圆形的具体绘图逻辑
    }
};

/**
 * @brief 派生类：正方形（公有继承Shape基类）
 * @note 重写基类的draw虚函数，实现正方形的绘图逻辑
 */
class Square : public Shape
{
public:
    /**
     * @brief 重写基类虚函数draw
     * @details override关键字增强代码可读性和安全性，强制编译器校验重写合法性
     */
    void draw() override
    {
        cout << "Drawing Square" << endl; // 正方形的具体绘图逻辑
    }
};

/**
 * @brief 统一渲染图形的函数（多态的核心应用）
 * @param shape 基类指针，可接收任意Shape派生类对象（Circle/Square）
 * @note 因draw是虚函数，此处会触发“动态绑定”：
 *       运行时根据shape指向的「对象实际类型」，调用对应派生类的draw版本，而非基类版本
 */
void renderShape(Shape *shape)
{
    shape->draw(); // 动态绑定：调用派生类重写的draw函数
}

int main()
{
    // 1. 基类指针指向派生类对象（多态的典型用法）
    // Shape* 类型的指针，实际指向Circle类型的对象
    Shape *shape1 = new Circle();
    // Shape* 类型的指针，实际指向Square类型的对象
    Shape *shape2 = new Square();

    // 2. 调用统一的渲染函数，自动匹配对象实际类型的draw逻辑
    renderShape(shape1); // 输出: Drawing Circle（调用Circle::draw）
    renderShape(shape2); // 输出: Drawing Square（调用Square::draw）

    // 3. 释放动态分配的内存（虚析构函数的作用体现）
    // 因Shape有虚析构，delete时先调用派生类析构（~Circle()），再调用基类析构（~Shape()）
    delete shape1;
    // 同理：先调用~Square()，再调用~Shape()，确保资源完整释放
    delete shape2;

    return 0;
}