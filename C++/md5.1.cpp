#include<iostream>                              // 引入标准输入输出流
#include<cmath>                                 // 引入数学函数库，用于计算圆周率
using namespace std;                            // 使用标准命名空间，省略 std:: 前缀

class Shape {                                   // 定义抽象基类 Shape
public:
    virtual double area() const = 0;            // 纯虚函数：计算面积，子类必须实现
    virtual double perimeter() const = 0;       // 纯虚函数：计算周长，子类必须实现
    virtual ~Shape() {}                         // 虚析构函数，确保通过基类指针删除派生类对象时正确调用派生类析构
};

class Rectangle : public Shape {                // 矩形类，公有继承 Shape
private:
    double length;                              // 私有成员：长度
    double width;                               // 私有成员：宽度
public:
    Rectangle(double l, double w) : length(l), width(w) {} // 构造函数，用初始化列表初始化长和宽
    double area() const override {              // 重写 area，计算矩形面积
        return length * width;                  // 面积 = 长 × 宽
    }
    double perimeter() const override {         // 重写 perimeter，计算矩形周长
        return 2 * (length + width);            // 周长 = 2 × (长 + 宽)
    }
};

class Circle : public Shape {                   // 圆形类，公有继承 Shape
private:
    double radius;                              // 私有成员：半径
    const double PI = acos(-1.0);               // 常量 π，通过反余弦 -1 获取精确值
public:
    Circle(double r) : radius(r) {}             // 构造函数，用初始化列表初始化半径
    double area() const override {              // 重写 area，计算圆形面积
        return PI * radius * radius;            // 面积 = π × r²
    }
    double perimeter() const override {         // 重写 perimeter，计算圆周长
        return 2 * PI * radius;                 // 周长 = 2 × π × r
    }
};

int main() {                                    // 主函数入口
    cout << "===直接创建派生类对象===" << endl; // 输出提示：直接创建派生类对象
    Rectangle rect(5.0, 3.0);                   // 创建一个矩形对象，长 5.0，宽 3.0
    Circle circ(4.0);                           // 创建一个圆形对象，半径 4.0

    cout << "\n===通过基类指针调用函数===" << endl; // 输出提示：通过基类指针调用虚函数
    Shape* pShape = &rect;                      // 基类指针指向矩形对象 rect
    cout << "矩形面积：" << pShape->area() << endl;      // 通过指针调用虚函数 area，输出矩形面积
    cout << "矩形周长：" << pShape->perimeter() << endl; // 通过指针调用虚函数 perimeter，输出矩形周长
    pShape = &circ;                             // 基类指针改为指向圆形对象 circ
    cout << "园面积:" << pShape->area() << endl;        // 通过指针调用虚函数 area，输出圆形面积
    cout << "圆周长：" << pShape->perimeter() << endl;   // 通过指针调用虚函数 perimeter，输出圆形周长

    cout << "\n===动态分配对象===" << endl;     // 输出提示：动态分配对象
    Shape* pRect = new Rectangle(4.0, 2.0);     // 在堆上创建矩形对象，长 4.0，宽 2.0，基类指针指向它
    Shape* pCirc = new Circle(3.0);             // 在堆上创建圆形对象，半径 3.0，基类指针指向它
    cout << "动态矩形面积：" << pRect->area() << endl;  // 输出动态创建的矩形面积
    cout << "动态圆形周长：" << pCirc->perimeter() << endl; // 输出动态创建的圆形周长
    delete pRect;                               // 释放动态分配的矩形对象，通过虚析构正确销毁
    delete pCirc;                               // 释放动态分配的圆形对象

    cout << "\n===程序结束，局部对象将自动关闭析构===" << endl; // 提示程序即将结束，栈上对象自动销毁
    return 0;                                   // 程序正常退出
}