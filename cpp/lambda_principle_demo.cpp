// 编译指令：g++ lambda_principle_demo.cpp -o lambda_principle_demo
// 运行指令：./lambda_principle_demo

#include <iostream>
#include <string>
using namespace std;

// -------------------------- 场景1：无捕获 Lambda --------------------------
void demo_no_capture()
{
    cout << "=== 场景1：无捕获 Lambda ===" << endl;
    // Lambda 表达式：无捕获，接收两个 int，返回和
    auto add_lambda = [](int a, int b) -> int
    {
        return a + b;
    };
    int result = add_lambda(3, 4);
    cout << "3 + 4 = " << result << endl;

    // 等价的手动仿函数类（编译器自动生成的就是这种结构）
    class __lambda_add
    {
    public:
        // 默认构造函数（编译器自动生成）
        __lambda_add() = default;
        // 重载 operator()，实现加法逻辑
        int operator()(int a, int b) const
        {
            return a + b;
        }
    };
    __lambda_add manual_add;
    cout << "手动仿函数类调用：3 + 4 = " << manual_add(3, 4) << "\n"
         << endl;
}

// -------------------------- 场景2：值捕获 Lambda（编译器会生成带成员变量的类） --------------------------
void demo_value_capture()
{
    cout << "=== 场景2：值捕获 Lambda ===" << endl;
    int base = 10;
    // Lambda 表达式：值捕获 base，接收一个 int，返回 base + x
    // 捕获的变量会被拷贝到类的成员变量中，lambda 内部使用的是拷贝副本，不受外部变量修改影响；
    auto add_base = [base](int x) -> int
    {
        return base + x;
    };
    cout << "base = 10，add_base(5) = " << add_base(5) << endl;

    // 修改 base，观察值捕获的特性（捕获的是拷贝，不受后续修改影响）
    base = 20;
    cout << "base 修改为 20 后，add_base(5) = " << add_base(5) << "（值捕获是拷贝，不受外部修改影响）\n"
         << endl;

    // 等价的手动仿函数类（编译器会把捕获的变量作为类成员）
    class __lambda_add_base
    {
    private:
        int base; // 捕获的变量成为类的成员变量
    public:
        // 构造函数：用捕获的变量初始化成员
        explicit __lambda_add_base(int b) : base(b) {}
        // 重载 operator()，使用成员变量计算
        int operator()(int x) const
        {
            return base + x;
        }
    };
    __lambda_add_base manual_add_base(10);
    cout << "手动仿函数类调用：10 + 5 = " << manual_add_base(5) << "\n"
         << endl;
}

// -------------------------- 场景3：引用捕获 Lambda（成员变量为引用类型） --------------------------
void demo_ref_capture()
{
    cout << "=== 场景3：引用捕获 Lambda ===" << endl;
    string msg = "Hello";
    // Lambda 表达式：引用捕获 msg，接收一个字符串后缀，拼接后返回
    // 捕获的变量会以引用的形式成为类的成员变量，lambda 内部使用的是外部变量的别名，外部修改会同步反映。
    auto append_msg = [&msg](const string &suffix) -> string
    {
        return msg + suffix;
    };
    cout << append_msg(" Lambda!") << endl;

    // 修改 msg，观察引用捕获的特性（捕获的是引用，会同步变化）
    msg = "Hi";
    cout << append_msg(" C++!") << "（引用捕获是别名，外部修改会同步反映）\n"
         << endl;

    // 等价的手动仿函数类（成员变量是引用类型）
    class __lambda_append_msg
    {
    private:
        string &msg; // 引用捕获的变量成为类的引用成员
    public:
        // 构造函数：用捕获的引用初始化成员
        explicit __lambda_append_msg(string &m) : msg(m) {}
        // 重载 operator()，使用引用成员计算
        string operator()(const string &suffix) const
        {
            return msg + suffix;
        }
    };
    __lambda_append_msg manual_append_msg(msg);
    cout << "手动仿函数类调用：" << manual_append_msg(" World!") << "\n"
         << endl;
}

// -------------------------- 主函数：依次运行所有 Demo --------------------------
int main()
{
    demo_no_capture();
    demo_value_capture();
    demo_ref_capture();
    return 0;
}