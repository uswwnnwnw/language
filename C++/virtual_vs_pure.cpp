#include <iostream>
using namespace std;

// ========== 1. 普通虚函数：基类有默认实现，子类可以不改 ==========
class Animal {
public:
    virtual void eat() { cout << "动物吃东西（默认吃法）" << endl; }  // 虚函数，有实现
};

class Dog : public Animal {
public:
    void eat() override { cout << "狗啃骨头" << endl; }  // 改了
};

class Fish : public Animal {
    // 啥也不写，直接用基类的默认吃法
};

// ========== 2. 纯虚函数：基类不写实现，子类必须自己写 ==========
class Animal2 {
public:
    virtual void eat() = 0;  // 纯虚函数，没有实现，就是个空契约
};

class Dog2 : public Animal2 {
public:
    void eat() override { cout << "狗啃骨头" << endl; }  // 必须写，不写编译不过
};

// class Fish2 : public Animal2 { };  // ← 删掉这行注释去编译会报错！
// 报错：Fish2 没实现 eat()，所以 Fish2 也是抽象类，不能 new

// ========== 主函数对比 ==========
int main() {
    cout << "=== 普通虚函数 ===" << endl;
    Animal a;           // ✅ 能创建基类对象，它有完整实现
    a.eat();            // 输出：动物吃东西
    Dog d;              // ✅ 子类改了
    d.eat();            // 输出：狗啃骨头
    Fish f;             // ✅ 子类没改，也能用
    f.eat();            // 输出：动物吃东西（用的基类默认）

    cout << "\n=== 纯虚函数 ===" << endl;
    // Animal2 a2;      // ❌ 注释掉，不然编译报错：抽象类不能 new
    Dog2 d2;            // ✅ 子类实现了 eat，能创建
    d2.eat();           // 输出：狗啃骨头
    // Fish2 f2;        // ❌ 没实现 eat，还是抽象类，不能 new

    // 指针都能用：
    Animal2* p = &d2;   // 抽象类虽不能 new，但指针活得好好的
    p->eat();           // 输出：狗啃骨头（多态生效）

    return 0;
}
