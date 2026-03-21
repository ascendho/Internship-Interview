// 编译指令：g++ default_delete_demo.cpp -o default_delete_demo
// 运行指令：./default_delete_demo

#include <iostream>
using namespace std;

// -------------------------- 核心示例类：演示 default 和 delete 的组合使用 --------------------------
class DemoClass
{
public:
    // 1. = default：让编译器自动生成【默认构造函数】
    DemoClass() = default;

    // 2. = default：让编译器自动生成【默认析构函数】
    ~DemoClass() = default;

    // 3. = delete：显式禁用【拷贝构造函数】，禁止对象间拷贝
    DemoClass(const DemoClass &) = delete;

    // 4. = delete：显式禁用【拷贝赋值运算符】，禁止对象间赋值
    DemoClass &operator=(const DemoClass &) = delete;

    // 5. = default：也可以用于移动构造/移动赋值（C++11 及以上）
    DemoClass(DemoClass &&) = default;
    DemoClass &operator=(DemoClass &&) = default;

    // 辅助方法：测试对象是否正常创建
    void say_hello() const
    {
        cout << "Hello from DemoClass object!\n";
    }
};

// -------------------------- 测试场景1：默认构造/析构（default 生效） --------------------------
void test_default_constructor()
{
    cout << "=== 测试 default 构造/析构 ===" << endl;
    DemoClass obj; // 调用默认构造函数（编译器自动生成）
    obj.say_hello();
    // 离开作用域时自动调用默认析构函数
}

// -------------------------- 测试场景2：拷贝构造/赋值被 delete（编译报错） --------------------------
void test_delete_copy()
{
    cout << "\n=== 测试 delete 拷贝构造/赋值 ===" << endl;
    DemoClass obj1;
    obj1.say_hello();

    // ❌ 错误：拷贝构造被 delete，无法创建新对象
    // DemoClass obj2 = obj1;  // 编译报错：use of deleted function 'DemoClass::DemoClass(const DemoClass&)'

    DemoClass obj3;
    // ❌ 错误：拷贝赋值被 delete，无法赋值
    // obj3 = obj1;  // 编译报错：use of deleted function 'DemoClass& DemoClass::operator=(const DemoClass&)'

    // ✅ 正确：移动构造/赋值是 default，可以正常转移所有权（C++11 及以上）
    DemoClass obj4 = move(obj1);
    obj4.say_hello();
}

// -------------------------- 测试场景3：对比手动实现 vs default --------------------------
class ManualVsDefault
{
public:
    // 手动实现构造函数
    ManualVsDefault() { cout << "Manual constructor called\n"; }
    ~ManualVsDefault() { cout << "Manual destructor called\n"; }

    // 显式让编译器生成默认拷贝构造（和手动实现等价）
    ManualVsDefault(const ManualVsDefault &) = default;
    ManualVsDefault &operator=(const ManualVsDefault &) = default;
};

void test_manual_vs_default()
{
    cout << "\n=== 测试手动实现 vs default 生成 ===" << endl;
    ManualVsDefault m1;
    ManualVsDefault m2 = m1; // 调用默认拷贝构造
    ManualVsDefault m3;
    m3 = m2; // 调用默认拷贝赋值
}

// -------------------------- 主函数：依次运行所有测试 --------------------------
int main()
{
    test_default_constructor();
    test_delete_copy();
    test_manual_vs_default();
    return 0;
}