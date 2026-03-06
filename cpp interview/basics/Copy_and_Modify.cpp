// 编译指令：g++ Copy_and_Modify.cpp -o Copy_and_Modify
// 运行指令：./Copy_and_Modify

#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 操作1：拷贝节点内容（*head = *(head->next)）
void copyNodeContent(ListNode *head)
{
    if (head != nullptr && head->next != nullptr)
    {
        *head = *(head->next); // 拷贝下一个节点的所有成员到当前节点
    }
}

// 操作2：直接修改next指针（改变结构）
void modifyNextPointer(ListNode *head)
{
    if (head != nullptr && head->next != nullptr)
    {
        head->next = head->next->next; // 直接修改连接关系
    }
}

int main()
{
    // 构建链表：1 -> 2 -> 3
    ListNode *node1 = new ListNode(1);
    ListNode *node2 = new ListNode(2);
    ListNode *node3 = new ListNode(3);
    node1->next = node2;
    node2->next = node3;

    // 打印初始链表
    cout << "初始链表：";
    ListNode *p = node1;
    while (p)
    {
        cout << p->val << " -> ";
        p = p->next;
    }
    cout << "nullptr\n"
         << endl;

    // 操作1：拷贝节点内容
    copyNodeContent(node1);
    cout << "执行 *head = *(head->next) 后：" << endl;
    cout << "node1->val = " << node1->val << endl;             // 输出2（内容被覆盖）
    cout << "node1->next->val = " << node1->next->val << endl; // 输出3（node1的next被覆盖为指向node3）
    cout << "node2->val = " << node2->val << endl;             // 输出2（node2本身完全没变）
    cout << "链表遍历：";
    p = node1;
    while (p)
    {
        cout << p->val << " -> ";
        p = p->next;
    }
    cout << "nullptr\n"
         << endl;

    // 重置链表：1 -> 2 -> 3
    node1->val = 1;
    node1->next = node2;
    node2->next = node3;

    // 操作2：直接修改next指针
    modifyNextPointer(node1);
    cout << "执行 head->next = head->next->next 后：" << endl;
    cout << "node1->next->val = " << node1->next->val << endl; // 输出3
    cout << "node2->val = " << node2->val << endl;             // 输出2（node2仍存在，只是被跳过）
    cout << "链表遍历：";
    p = node1;
    while (p)
    {
        cout << p->val << " -> ";
        p = p->next;
    }
    cout << "nullptr" << endl;

    return 0;
}