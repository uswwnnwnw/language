#include<iostream>
#include<cmath>
using namespace std;

class Shape {
public:
	virtual double area() const = 0;
	virtual double perimeter() const = 0;
	virtual ~Shape(){}
};

class Rectangle :public Shape {
private:
	double length;
	double width;
public:
	Rectangle(double l, double w) :length(l), width(w) {}

	double area() const override {
		return length * width;
	}

	double perimeter() const override {
		return 2 * (length + width);
	}
};
class Circle :public Shape {
private:
	double radius;
	const double PI = acos(-1.0);
public:
	Circle(double r):radius(r){}

	double area() const override {
		return PI * radius * radius;
	}
	double perimeter() const override {
		return 2 * PI * radius;
	}
};


int main()
{
	cout << "===直接创建派生类对象===" << endl;
	Rectangle rect(5.0, 3.0);
	Circle circ(4.0);

	cout << "\n===通过基类指针调用函数===" << endl;
	Shape* pShape = &rect;
	cout << "矩形面积：" << pShape->area() << endl;
	cout << "矩形周长：" << pShape->perimeter() << endl;

	pShape = &circ;
	cout << "园面积:" << pShape->area() << endl;
	cout << "圆周长：" << pShape->perimeter() << endl;

	cout << "\n===动态分配对象===" << endl;
	Shape* pRect = new Rectangle(4.0, 2.0);
	Shape* pCirc = new Circle(3.0);

	cout << "动态矩形面积：" << pRect->area() << endl;
	cout << "动态圆形周长：" << pCirc->perimeter() << endl;

	delete pRect;
	delete pCirc;
	cout << "\n===程序结束，局部对象将自动关闭析构===" << endl;
	return 0;

}