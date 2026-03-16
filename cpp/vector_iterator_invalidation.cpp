// 编译指令：g++ vector_iterator_invalidation.cpp -o vector_iterator_invalidation
// 运行指令：./vector_iterator_invalidation

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    cout << "==================== 场景1：插入导致内存重分配，所有迭代器失效 ====================" << endl;
    vector<int> vec1 = {1, 2, 3};
    cout << "初始 vector：";
    for (int x : vec1)
        cout << x << " ";
    cout << "\n初始容量 capacity: " << vec1.capacity() << ", 大小 size: " << vec1.size() << endl;

    auto it1 = vec1.begin(); // 指向第一个元素 1
    cout << "\n插入前，迭代器 it1 指向元素: " << *it1 << endl;

    // 插入元素，触发内存重分配（此时 size=3，capacity=3，push_back 后需要扩容）
    vec1.push_back(4);
    cout << "push_back(4) 后，容量 capacity: " << vec1.capacity() << ", 大小 size: " << vec1.size() << endl;

    // 注意：此时 it1 已经失效！访问 *it1 是未定义行为，可能崩溃、乱码或输出旧值
    // 取消注释下面这行，会触发未定义行为（不同编译器表现不同）
    cout << "插入后，尝试访问失效迭代器 it1: " << *it1 << endl;

    cout << "\n--- 结论：插入导致内存重分配时，所有旧迭代器/指针/引用全部失效 ---" << endl;

    // -------------------------------------------------------------------------

    cout << "\n==================== 场景2：删除元素，被删位置之后的迭代器失效 ====================" << endl;
    vector<int> vec2 = {1, 2, 3};
    cout << "初始 vector：";
    for (int x : vec2)
        cout << x << " ";
    cout << endl;

    auto it2 = vec2.begin() + 1; // 指向第二个元素 2
    cout << "删除前，迭代器 it2 指向元素: " << *it2 << endl;

    // 删除第一个元素（it2 指向的是删除位置之后的元素，因此 it2 失效）
    vec2.erase(vec2.begin());
    cout << "删除 vec2.begin() 后，vector 变为：";
    for (int x : vec2)
        cout << x << " ";
    cout << endl;

    // 注意：此时 it2 已经失效！访问 *it2 是未定义行为
    // 取消注释下面这行，会触发未定义行为
    cout << "删除后，尝试访问失效迭代器 it2: " << *it2 << endl;

    cout << "\n--- 结论：删除元素时，被删元素及之后的所有迭代器/指针/引用全部失效 ---" << endl;

    return 0;
}

/*
 * deque 的迭代器失效规则比 vector 更精细：
 *      中间操作（插入 / 删除）：所有迭代器全部失效；
 *      首尾操作：插入无扩容时迭代器有效，删除时仅被删元素的迭代器失效；
 *      通用安全写法：用 erase 的返回值更新迭代器，兼容所有容器类型。
 *
 */

/*
 * 针对 set/map：
 *      插入后无需重新获取迭代器（所有旧迭代器有效）；
 *      删除后，仅需废弃被删元素的迭代器，其他迭代器可继续使用；
 *      若需安全删除，推荐用 erase 返回值的写法（但 set/map 的 erase 无返回值，这点和 vector/deque 不同）
 *
 */

/*
 * std::list 是 C++ 容器中迭代器最稳定的容器：插入永远不失效，删除只失效被删元素。
 * 只要不访问被删元素的迭代器，其他所有迭代器都可以安全使用。
 *
 */