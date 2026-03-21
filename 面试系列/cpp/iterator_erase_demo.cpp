// 编译指令：g++ iterator_erase_demo.cpp -o iterator_erase_demo
// 运行指令：./iterator_erase_demo

#include <iostream>
#include <vector>
using namespace std;

int main()
{
    // 特意选奇数连续的数组，更容易暴露问题
    vector<int> arr = {1, 3, 2, 4, 5, 6};
    cout << "【原始数组】：";
    for (int num : arr)
        cout << num << " ";
    cout << "\n目标：删除所有奇数，预期正确结果：2 4 6" << endl;
    cout << "-------------------------" << endl;

    auto it = arr.begin();
    // 【错误写法：vector中绝对不能用 erase(it++)】
    while (it != arr.end())
    {
        cout << "\n当前迭代器指向元素：" << *it << endl;
        if (*it % 2 == 1)
        { // 删除奇数
            cout << "执行 erase(it++)，删除元素：" << *it << endl;
            arr.erase(it++); // 致命错误
        }
        else
        {
            cout << "不删除，迭代器后移" << endl;
            it++;
        }
    }

    cout << "\n-------------------------" << endl;
    cout << "【错误写法执行后】：";
    for (int num : arr)
        cout << num << " ";
    cout << endl;
    cout << "【预期正确结果】：2 4 6" << endl;

    return 0;
}

/*
 * 为什么会跳过元素3：
 * it++是后置自增，执行顺序严格分为 3 步：
 * 1. 先传参：把it的当前值（指向元素1，索引 0）传给erase函数；
 * 2. 再自增：对it执行自增，此时it指向索引 1（原本的元素3）；
 * 3. 最后执行 erase：删除索引 0 的元素1，vector是连续内存，删除后后面的所有元素会整体前移：
 *      原本的元素3从索引 1，被前移到了索引 0；
 *      原本的元素2从索引 2，被前移到了索引 1；
 *      此时，步骤 2 里自增后的it，指向的是索引 1，现在索引 1 的元素是2，我们永远不会再访问到被前移到索引 0 的元素3！
 * 这就是错误的核心：erase执行后，自增后的it已经变成了无效迭代器（被删元素之后的所有迭代器都会失效），
 * 导致元素被跳过，结果错误，极端情况下会直接触发程序崩溃。
 *
 */

/*
 * 为什么list/map可以用erase(it++)？
 * list/map/set是节点式容器，内存不连续，erase只会让被删除元素的迭代器失效，
 * 其他迭代器依然有效，所以erase(it++)在这类容器中是可行的。
 *
 */

/*
 * C++11 之后，所有标准容器的erase都会返回下一个有效迭代器，
 * 因此it = 容器.erase(it);是全容器通用的安全写法，
 * 不管是 vector、deque，还是 list、map、set，都可以用这个写法，
 * 不用单独记不同容器的失效规则，兼容性和安全性拉满。
 *
 */