// 编译指令：g++ array_decay_size.cpp -o array_decay_size
// 运行指令：./array_decay_size


#include <iostream>
#include <cstring> // 包含strlen函数的头文件
using namespace std;

/**
 * @brief 演示数组作为函数参数时的退化行为
 * @param arr 形式上是字符数组，实际会退化为char*指针（数组名丢失长度信息）
 * 注意：
 * 1. sizeof(arr)：计算的是指针大小（64位系统8字节，32位4字节），而非数组长度；
 * 2. strlen(arr)：计算字符串实际长度（不含'\0'），和数组物理长度无关。
 */
void size_of(char arr[])
{
    // 警告原因：数组参数退化为指针，sizeof(arr)等价于sizeof(char*)
    // 64位系统指针大小为8字节，因此输出8；32位系统输出4
    cout << sizeof(arr) << endl;
    // strlen计算字符串有效长度："hello"有5个字符（h/e/l/l/o），不含末尾的'\0'，输出5
    cout << strlen(arr) << endl;
}

int main()
{
    // 定义长度为20的字符数组，初始化为"hello"（末尾自动补'\0'）
    // 数组物理长度：20字节；字符串有效长度：5字节
    char arr[20] = "hello";
    // 数组名作为参数传递时，会退化为指向数组首元素的指针（char*），丢失长度信息
    size_of(arr);

    return 0;
}