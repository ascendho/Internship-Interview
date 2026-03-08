// 编译指令：g++ static_local_variables.cpp -o static_local_variables
// 运行指令：./static_local_variables

/*
 * @brief 演示C++静态局部变量（static local variable）的核心特性
 * @details 1. 静态局部变量仅初始化一次，存储在静态存储区
 *          2. 函数执行结束后不销毁，保留上一次的修改值
 *          3. 作用域仍局限于函数内部，外部无法直接访问
 */

#include <iostream>

using namespace std;

/**
 * @brief 包含静态局部变量的测试函数
 * @return int 自增后的静态变量值
 * @details 静态变量var初始值为1，每次调用函数时自增1，且仅初始化一次
 */
int fun()
{
    // 静态局部变量核心特性说明：
    // - 初始化时机：仅第一次进入函数时执行初始化（var = 1）
    // - 存储位置：静态存储区（而非栈区），程序生命周期内一直存在
    // - 作用域：仅在fun()函数内部可见，main()无法直接访问
    static int var = 1;

    // 静态变量自增（每次调用都会执行，值会持续保留）
    var += 1;

    // 返回当前var值
    return var;
}

int main()
{
    // 第一部分测试：循环调用10次，验证静态变量的持续自增
    cout << "===== 循环调用10次fun() =====" << endl;
    for (int i = 0; i < 10; ++i)
        // 输出格式：第N次调用 → 返回值（增强可读性）
        cout << "第" << i + 1 << "次调用：" << fun() << endl;

    cout << endl;

    // 第二部分测试：单次调用，验证静态变量值未重置
    cout << "===== 单次额外调用fun() =====" << endl;
    int last_value = fun();
    cout << "额外调用的返回值：" << last_value << endl;
    cout << "说明：静态变量在上次11的基础上继续自增为12" << endl;

    // 第三部分：演示静态变量的作用域（注释+代码示例）
    cout << endl;
    cout << "===== 静态变量作用域测试 =====" << endl;
    // 错误示例：直接访问fun()内的var会编译报错，因为var的作用域仅限fun()内部
    // cout << var << endl; // 取消注释后编译会提示：‘var’ was not declared in this scope
    cout << "注：无法直接访问fun()内的var变量（作用域限制），取消上方注释会编译报错" << endl;

    // 程序正常退出
    return 0;
}