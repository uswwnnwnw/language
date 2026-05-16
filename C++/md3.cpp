#include<iostream>
using namespace std;

class Complex { // 重点：Complex。定义一个“复数”类
private: // 重点：private。封装特性，实部和虚部不让外部直接修改
    int real; // 重点：real。存储实部
    int imag; // 重点：imag。存储虚部
public:
    // 重点：初始化列表。构造函数，用于创建对象时给 real 和 imag 赋值
    Complex(int r, int i) :real(r), imag(i) {}; 

    // 重点：operator。运算符重载声明，告诉编译器 + - * 如何处理 Complex 对象
    Complex operator+(Complex other); 
    Complex operator-(Complex other);
    Complex operator*(Complex other);
    Complex operator-=(Complex other);

    void show(); // 普通成员函数：打印复数

    // 重点：friend。友元函数，允许类外的重载函数访问 private 成员
    // 重点：istream&/ostream&。为了实现 cin >> c1 和 cout << c1 这种操作
    friend istream& operator>>(istream& in, Complex& c); 
    friend ostream& operator<<(ostream& out, const Complex& c);
};

// 乘法重载：c1 * c2 时触发
Complex Complex::operator*(Complex other) { 
    int r, i;
    r = this->real * other.real; // 重点：this->。指代左操作数（c1）
    i = this->imag * other.imag; // 重点：other.imag。指代右操作数（c2）
    return Complex(r, i); // 返回一个新的匿名对象
}

// 复合赋值重载：c3 -= c1 时触发
Complex Complex::operator-=(Complex other) {
    // 重点：修改自身。-= 会改变左边对象的值
    real -= other.real; 
    imag -= other.imag; 
    return *this; // 重点：*this。返回修改后的自己
}

// 传统的显示函数（本代码中 main 没用它，被 << 替代了）
void Complex::show() {
    if (imag >= 0) cout << real << "+" << imag << "i" << endl;
    else cout << real << "-" << imag << "i" << endl;
}

// 输入重载：cin >> c3 时触发
istream& operator>>(istream& in, Complex& c) {
    cout << "输入实部，虚部";
    in >> c.real >> c.imag; // 重点：引用传递。直接修改传入的对象 c
    return in; // 重点：return in。支持连续输入 cin >> a >> b;
}

// 输出重载：cout << c1 时触发
ostream& operator<<(ostream& out, const Complex& c) {
    if (c.imag >= 0) out << c.real << "+" << c.imag << "i"; // 重点：out。将数据流向输出流
    else out << c.real << "-" << c.imag << "i";
    return out; // 重点：return out。支持连续输出 cout << a << b;
}

// 加法重载
Complex Complex::operator+(Complex other) {
    return Complex(this->real + other.real, this->imag + other.imag);
}

// 减法重载
Complex Complex::operator-(Complex other) {
    return Complex(this->real - other.real, this->imag - other.imag);
}

int main() {
    Complex c1(100, 20); // 因：调用带参构造函数。果：创建复数 100+20i
    Complex c2(20, 100); 

    // 因：重载了 <<。果：可以直接用 cout 打印对象，不再需要写 c1.show()
    cout << "c1=" << c1 << endl; 
    cout << "c2=" << c2 << endl;

    // 因：重载了 *。果：执行 c1 * c2 的函数逻辑，结果存入 c3
    Complex c3 = c1 * c2; 
    cout << "c3=c1*c2=" << c3 << endl;

    // 因：重载了 -=。果：c3 的实部虚部被减去 c1 的部分，c3 自身被修改
    c3 -= c1; 
    cout << "c3=c3-c1=" << c3 << endl;

    // 因：重载了 >>。果：程序暂停等待键盘输入，并直接赋值给 c3
    cin >> c3; 
    cout << "输入c3后：" << c3 << endl;

    return 0;
}