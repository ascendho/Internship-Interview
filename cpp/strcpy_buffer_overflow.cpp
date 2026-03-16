// 编译指令：g++ strcpy_buffer_overflow.cpp -o strcpy_buffer_overflow
// 运行指令：./strcpy_buffer_overflow

#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    // 定义int型变量var，初始化为16进制值0x11112222（十进制对应28696090）
    int var = 0x11112222;

    // 定义字符数组arr，长度为10个char（最多存储9个有效字符 + 1个字符串结束符'\0'）
    char arr[10];

    // 输出var的内存地址（cout默认以十六进制输出指针/地址）
    cout << "Address : var " << &var << endl;

    // 输出arr的内存地址（&arr是数组的地址，类型为char (*)[10]，cout会转为指针格式输出）
    cout << "Address : arr " << &arr << endl;

    // 【致命问题：缓冲区溢出】
    // "hello world!" 包含的字符：h e l l o   w o r l d ! \0 → 共13个字节（含'\0'）
    // arr仅能容纳10个字节，strcpy会无脑拷贝直到'\0'，导致越界写入，覆盖相邻内存（var）
    strcpy(arr, "hello world!");

    // 以十六进制格式输出var的值（hex操纵符修改cout输出格式，后续输出均为十六进制）
    cout << "var:" << hex << var << endl;

    // 输出arr的内容（因缓冲区溢出，arr内容可能乱码，且var的内存被篡改）
    cout << "arr:" << arr << endl;

    return 0; // 程序正常退出
}

/*
 * 【运行结果分析注释 - 留存用】
 * 1. 内存地址特征：
 *    - arr地址(0x16b356ca0) < var地址(0x16b356cac)，两者内存相邻，地址差12字节(0xC)；
 *    - arr占用10字节空间，var占用4字节空间，arr在后的内存区域直接衔接var的内存。
 * 2. var值被篡改的原因：
 *    - "hello world!"含'\0'共13字节，arr仅10字节，strcpy无边界检查，无脑拷贝至'\0'为止；
 *    - 拷贝超出arr边界后，字符串结束符'\0'(0x00)被写入var的最低字节地址(0x16b356cac)；
 *    - 小端字节序下，var原内存布局(0x22 0x22 0x11 0x11)被改为(0x00 0x22 0x11 0x11)，故输出0x11112200。
 * 3. arr输出完整字符串的本质：
 *    - cout输出字符串时，从arr[0]开始读取，直到遇到'\0'停止；
 *    - 此处'\0'被写入var的内存中，因此能完整输出"hello world!"，这是未定义行为的巧合，并非程序合法。
 * 4. 核心结论：
 *    - strcpy是高危函数，无缓冲区大小检查，会导致缓冲区溢出，篡改相邻内存数据；
 *    - 即使输出看似正常，程序内存状态已被破坏，存在崩溃、数据错乱等风险。
 *
 */
