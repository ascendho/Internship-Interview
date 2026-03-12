// 编译指令：g++ unique_ptr_demo.cpp -o unique_ptr_demo
// 运行指令：./unique_ptr_demo

#include <iostream>
#include <memory> // unique_ptr/make_unique 头文件
#include <string>
using namespace std;

// 自定义类 A，用于观察构造/析构时机，直观体现内存管理
class A
{
private:
    int id;

public:
    A(int id) : id(id)
    {
        cout << "[A 构造] id = " << id << "，对象创建" << endl;
    }
    ~A()
    {
        cout << "[A 析构] id = " << id << "，对象释放" << endl;
    }
    void show() const
    {
        cout << "[A 方法] id = " << id << "，对象正常使用" << endl;
    }
};

int main()
{
    // ==================================================
    // 场景1：基础用法（独占所有权，禁止拷贝）
    // ==================================================
    cout << "=== 场景1：基础 unique_ptr（独占所有权） ===" << endl;
    // 用 make_unique 创建 unique_ptr（C++14 推荐，比 new 更安全）
    unique_ptr<A> ptr1 = make_unique<A>(1);
    // ❌ 错误：unique_ptr 不支持拷贝赋值，会直接编译报错
    // unique_ptr<A> ptr2 = ptr1;

    cout << "ptr1 是否为空？" << boolalpha << (ptr1 == nullptr) << endl; // 输出 false
    ptr1->show();                                                        // 正常调用成员方法
    cout << endl;

    // ==================================================
    // 场景2：std::move() 转移所有权（图片中的核心用法）
    // ==================================================
    cout << "=== 场景2：std::move() 转移所有权 ===" << endl;
    unique_ptr<A> ptr2 = make_unique<A>(2);
    cout << "转移前：ptr2 是否为空？" << (ptr2 == nullptr) << endl; // false

    // ✅ 正确：用 move 转移所有权，ptr2 失去所有权（变为空），ptr3 获得所有权
    unique_ptr<A> ptr3 = move(ptr2);
    cout << "转移后：ptr2 是否为空？" << (ptr2 == nullptr) << endl; // true（关键！）
    cout << "转移后：ptr3 是否为空？" << (ptr3 == nullptr) << endl; // false

    ptr3->show(); // ptr3 持有所有权，可正常访问
    cout << endl;

    // ==================================================
    // 场景3：release() 释放控制权，移交裸指针（图片中的进阶用法）
    // ==================================================
    cout << "=== 场景3：release() 释放控制权 ===" << endl;
    unique_ptr<A> ptr4 = make_unique<A>(3);
    // 🔑 release()：释放对 ptr 的控制权，返回裸指针，同时 ptr 变为空
    A *raw_ptr = ptr4.release();
    cout << "release 后：ptr4 是否为空？" << (ptr4 == nullptr) << endl; // true（关键！）

    // ✅ 用裸指针构造新的 unique_ptr，完成所有权转移
    unique_ptr<A> ptr5(raw_ptr);
    cout << "转移后：ptr5 是否为空？" << (ptr5 == nullptr) << endl; // false

    ptr5->show(); // ptr5 持有所有权，正常访问
    cout << endl;

    // ==================================================
    // 补充：reset() 用法（主动释放资源，置空）
    // ==================================================
    cout << "=== 补充：reset() 主动释放 ===" << endl;
    unique_ptr<A> ptr6 = make_unique<A>(4);
    ptr6.reset();                                                     // 释放对象，ptr6 置空
    cout << "reset 后：ptr6 是否为空？" << (ptr6 == nullptr) << endl; // true

    return 0;
}