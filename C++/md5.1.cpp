#include<iostream>                              // 引入标准输入输出流，用于 cout 打印
#include<cmath>                                 // 引入数学函数库，用于 acos(-1.0) 计算圆周率 π
using namespace std;                            // 使用标准命名空间，省得每个地方写 std::cout、std::endl

// ==================== 抽象基类 Shape ====================
// Shape 是"形状"这个概念本身——你见过纯"形状"吗？没有。
// 所以它不能 new，只能当模板用。两个 =0 让它变成抽象类。
class Shape {
public:
    virtual double area() const = 0;            // 纯虚函数 = 欠条："所有形状都有面积，但我不知道怎么算，子类必须自己写"
    virtual double perimeter() const = 0;       // 纯虚函数 = 欠条："所有形状都有周长，但我不知道怎么算，子类必须自己写"
    virtual ~Shape() {}                         // 虚析构：保证 delete 基类指针时，能从"顶层拆到地基"，
                                                // 先调派生类析构 → 再调基类析构，不会漏拆任何层
};

// ==================== 矩形类 Rectangle ====================
class Rectangle : public Shape {                // 公有继承 Shape，矩形是形状的一种
private:
    double length;                              // 长（不直接暴露，通过公有方法间接访问——封装）
    double width;                               // 宽
public:
    Rectangle(double l, double w)               // 构造函数：出生时就定好长宽，不允许无参创建
        : length(l), width(w) {}                // 初始化列表：直接给成员赋初值，比在函数体里赋值更高效
    double area() const override {              // override = 向编译器报备"我在覆写基类虚函数"，写错名编译器会骂你
        return length * width;                  // S = 长 × 宽
    }
    double perimeter() const override {         // 覆写周长
        return 2 * (length + width);            // C = 2 × (长 + 宽)
    }
};

// ==================== 圆形类 Circle ====================
class Circle : public Shape {                   // 公有继承 Shape，圆是形状的一种
private:
    double radius;                              // 半径
    const double PI = acos(-1.0);               // 用 acos(-1) 算 π：acos 是反余弦，cos(π)=-1，反过来 acos(-1)=π
                                                // const 表示这辈子不会变，谁也别想改
public:
    Circle(double r) : radius(r) {}             // 构造函数：出生就定半径
    double area() const override {              // 覆写面积
        return PI * radius * radius;            // S = π × r²
    }
    double perimeter() const override {         // 覆写周长
        return 2 * PI * radius;                 // C = 2 × π × r
    }
};

// ==================== 主函数 ====================
int main() {
    // ----- 第一幕：栈上直接创建对象 -----
    // new 都不用，编译器自动在栈上分配+构造，离开作用域自动析构
    cout << "=== 直接创建派生类对象 ===" << endl;
    Rectangle rect(5.0, 3.0);                   // 长5宽3的矩形，生在栈上
    Circle circ(4.0);                           // 半径4的圆，生在栈上

    // ----- 第二幕：多态——同一句命令，不同对象执行出不同结果 -----
    // pShape 是基类指针（记事本），它只管喊 area()/perimeter()，
    // 具体怎么算是对象自己说了算——这就是多态
    cout << "\n=== 通过基类指针调用函数（多态） ===" << endl;
    Shape* pShape = &rect;                      // 记事本记下矩形的地址（戴 Shape 眼镜，只能看见 Shape 那部分接口）
    cout << "矩形面积：" << pShape->area() << endl;       // -> 跟着地址走，查 vtable → 找到 Rectangle::area() → 执行
    cout << "矩形周长：" << pShape->perimeter() << endl;  // 同上，vtable 分派到 Rectangle::perimeter()
    pShape = &circ;                             // 记事本擦掉重写，现在指向圆形
    cout << "圆形面积：" << pShape->area() << endl;       // 同一句 pShape->area()，这次 vtable 分派到 Circle::area()
    cout << "圆形周长：" << pShape->perimeter() << endl;  // 分派到 Circle::perimeter()

    // ----- 第三幕：堆上动态分配，手动管理生命周期 -----
    // new = 在堆上建房（手动申请），delete = 拆房（手动释放）
    // 栈上的对象离开大括号自动死，堆上的必须手动 delete，不然内存泄漏
    cout << "\n=== 动态分配对象（堆） ===" << endl;
    Shape* pRect = new Rectangle(4.0, 2.0);     // 堆上 new 矩形，返回地址存进 pRect
    Shape* pCirc = new Circle(3.0);             // 堆上 new 圆形，返回地址存进 pCirc
    cout << "动态矩形面积：" << pRect->area() << endl;     // 基类指针调派生类方法，多态
    cout << "动态圆形周长：" << pCirc->perimeter() << endl; // 同上
    delete pRect;                               // 释放矩形：先调 ~Rectangle()，再调 ~Shape()（因为析构是 virtual）
    delete pCirc;                               // 释放圆形：同上
    // 注意：如果 ~Shape() 没写 virtual，delete 时只调 ~Shape()，
    // 派生类那部分不会被析构——相当于只拆了门框没拆房间，内存泄漏！

    cout << "\n=== 程序结束，局部对象将自动析构 ===" << endl;
    // rect 和 circ 离开 main 的 } 时自动析构（栈对象），不需要手动管
    return 0;
}
