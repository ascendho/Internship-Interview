// 编译指令：g++ function_object.cpp -o function_object
// 运行指令：./function_object

#include <iostream>
using namespace std;

// 普通函数：实现两数相加
int add(int a, int b)
{
    return a + b;
}

// 函数对象（仿函数）类：重载()运算符，实现两数相加
// 函数对象的优势：可携带状态、可作为模板参数、可复用性更强
class Add
{
public:
    // operator()声明为const：表明调用该函数不会修改对象的任何成员变量（最佳实践）
    int operator()(int a, int b) const
    {
        return a + b;
    }
};

int main()
{
    // 1. 调用普通函数add
    int res1 = add(2, 3);
    cout << "普通函数 add(2, 3) 的结果：" << res1 << endl;

    // 2. 使用函数对象（仿函数）
    // 第一步：创建Add类的实例（函数对象）
    Add add_obj;

    // 第二步：像调用函数一样调用对象（本质是调用operator()）
    int res2 = add_obj.operator()(4, 5);
    cout << "函数对象 add_obj(4, 5) 的结果：" << res2 << endl;

    // 拓展：展示函数对象的核心优势——可携带状态（普通函数无法做到）
    class AddWithOffset
    {
    private:
        // 函数对象携带的状态：偏移量
        int offset;

    public:
        // 构造函数初始化偏移量
        AddWithOffset(int offset_val) : offset(offset_val) {}

        // 两数相加后再加上偏移量
        int operator()(int a, int b) const
        {
            return a + b + offset;
        }
    };

    // 创建带偏移量的函数对象（偏移量为10）
    AddWithOffset add_with_offset(10);
    int res3 = add_with_offset.operator()(2, 3);
    cout << "带状态的函数对象 add_with_offset(2, 3)（偏移量10）的结果：" << res3 << endl;

    return 0;
}