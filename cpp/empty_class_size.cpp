// 编译指令：g++ empty_class_size.cpp -o empty_class_size
// 运行指令：./empty_class_size

#include <iostream>
using namespace std;

// ========== 1. 基础空类 ==========
class EmptyClass
{
};

// ========== 2. 带虚函数的空类 ==========
class EmptyWithVirtual
{
public:
    virtual void dummyFunc() {}
};

// ========== 3. 空白基类优化（EBO） ==========
class EmptyBase
{
};
class DerivedWithEBO : public EmptyBase
{
private:
    int num;

public:
    DerivedWithEBO(int n) : num(n) {}
};

// ========== 4. 只含静态成员变量的类 ==========
// 静态成员存于静态存储区，不占用类的大小
class ClassWithStatic
{
public:
    static int staticMember; // 静态成员
};
// 静态成员需要在类外初始化
int ClassWithStatic::staticMember = 0;

// ========== 5. 含静态 + 非静态成员的类 ==========
// 静态成员存放在静态存储区，不占用类的大小, 普通函数也不占用类大小，类大小由非静态成员决定
class ClassWithStaticAndNonStatic
{
public:
    static int staticMember; // 静态成员
    int nonStaticMember;     // 非静态成员
};
int ClassWithStaticAndNonStatic::staticMember = 0;

int main()
{
    // ---------------- 演示1：基础空类测试 ----------------
    cout << "===== 基础空类测试 =====" << endl;
    cout << "EmptyClass 的大小：" << sizeof(EmptyClass) << " 字节" << endl;
    EmptyClass obj1, obj2;
    cout << "obj1 地址：" << &obj1 << "，obj2 地址：" << &obj2 << endl;
    cout << "obj1 和 obj2 地址不同：" << boolalpha << (&obj1 != &obj2) << endl;

    // ---------------- 演示2：带虚函数的空类 ----------------
    cout << "\n===== 带虚函数的空类测试 =====" << endl;
    cout << "EmptyWithVirtual 的大小：" << sizeof(EmptyWithVirtual) << " 字节" << endl;
    EmptyWithVirtual vobj1, vobj2;
    cout << "vobj1 地址：" << &vobj1 << "，vobj2 地址：" << &vobj2 << endl;

    // ---------------- 演示3：空白基类优化（EBO） ----------------
    cout << "\n===== 空白基类优化（EBO）测试 =====" << endl;
    cout << "DerivedWithEBO 的大小：" << sizeof(DerivedWithEBO) << " 字节" << endl;
    DerivedWithEBO d1(10), d2(20);
    cout << "d1 地址：" << &d1 << "，d2 地址：" << &d2 << endl;

    // ---------------- 演示4：只含静态成员的类 ----------------
    cout << "\n===== 只含静态成员的类测试 =====" << endl;
    cout << "ClassWithStatic 的大小：" << sizeof(ClassWithStatic) << " 字节" << endl;
    ClassWithStatic sObj1, sObj2;
    cout << "sObj1 地址：" << &sObj1 << "，sObj2 地址：" << &sObj2 << endl;
    cout << "静态成员地址：" << &ClassWithStatic::staticMember << endl;

    // ---------------- 演示5：含静态 + 非静态成员的类 ----------------
    cout << "\n===== 含静态 + 非静态成员的类测试 =====" << endl;
    cout << "ClassWithStaticAndNonStatic 的大小：" << sizeof(ClassWithStaticAndNonStatic) << " 字节" << endl;
    ClassWithStaticAndNonStatic snObj1, snObj2;
    cout << "snObj1 地址：" << &snObj1 << "，snObj2 地址：" << &snObj2 << endl;
    cout << "非静态成员地址（snObj1）：" << &snObj1.nonStaticMember << endl;
    cout << "静态成员地址：" << &ClassWithStaticAndNonStatic::staticMember << endl;

    return 0;
}