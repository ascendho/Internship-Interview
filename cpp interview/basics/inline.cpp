// 编译指令：g++ inline.cpp -o inline
// 运行指令：./inline

#include <iostream>
// 宏定义实现最大值：通过文本替换返回a和b中的较大值
// 注意：宏是预处理阶段文本替换，无类型检查，且可能引发副作用
#define MAX(a, b) ((a) > (b) ? (a) : (b))
using namespace std;

/**
 * @brief 内联函数实现最大值
 * @note 内联函数是编译阶段展开，有类型检查，无宏的副作用，更安全
 * @param a 待比较的整数1
 * @param b 待比较的整数2
 * @return int a和b中的较大值
 */
inline int fun_max(int a, int b)
{
    return a > b ? a : b;
}

int main()
{
    int var = 1;

    // 宏替换：MAX(var,5) → ((var)>(5)?(var):(5)) → 输出5
    cout << MAX(var, 5) << endl;
    // 内联函数调用：fun_max(var,0) → 1>0返回1 → 输出1
    cout << fun_max(var, 0) << endl;

    return 0;
}