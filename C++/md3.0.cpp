#include<iostream>                            // 引入输入输出流头文件
using namespace std;                          // 使用标准命名空间，省略std::前缀

class Complex                                // 定义复数类
{
private:                                     // 私有访问区域
    int real;                                // 存储实部
    int imag;                                // 存储虚部
public:                                      // 公有访问区域
    Complex(int r, int i) :real(r), imag(i) {}; // 构造函数，用初始化列表初始化实部和虚部
    Complex operator+(Complex other);        // 声明加法运算符重载
    Complex operator-(Complex other);        // 声明减法运算符重载
    Complex operator*(Complex other);        // 声明乘法运算符重载
    Complex operator-=(Complex other);       // 声明复合赋值减法运算符重载
    void show();                             // 声明显示复数的普通成员函数
    friend istream& operator>>(istream& in, Complex& c); // 声明友元输入重载，允许cin>>复数
    friend ostream& operator<<(ostream& out, const Complex& c); // 声明友元输出重载，允许cout<<复数
};

Complex Complex::operator*(Complex other)    // 乘法运算符重载的实现
{
    int r, i;                                // 定义临时实部和虚部
    r = this->real * other.real;             // 左操作数的实部乘以右操作数的实部
    i = this->imag * other.imag;             // 左操作数的虚部乘以右操作数的虚部
    return Complex(r, i);                    // 返回乘积复数（注意：此实现非数学上复数乘法）
}

Complex Complex::operator-=(Complex other)   // 复合赋值减法运算符重载的实现
{
    int r, i;                                // 定义临时变量（实际未使用）
    r = real -= other.real;                  // 实部减去右操作数的实部，并赋值给临时r
    i = imag -= other.imag;                  // 虚部减去右操作数的虚部，并赋值给临时i
    return *this;                            // 返回修改后的当前对象，支持链式调用
}

void Complex::show()                          // 普通成员函数：显示复数
{
    if (imag >= 0)                            // 如果虚部非负
    {
        cout << real << "+" << imag << "i" << endl; // 输出形如 a+bi 的格式
    }
    else {                                   // 如果虚部为负
        cout << real << "-" << imag << "i" << endl; // 输出 a-bi 格式（imag本身为负，显示负号）
    }
}

istream& operator>>(istream& in, Complex& c)  // 友元输入重载实现
{
    cout << "输入实部，虚部";                // 提示用户输入
    in >> c.real >> c.imag;                  // 从输入流读取实部和虚部
    return in;                               // 返回输入流引用，支持连续输入
}

ostream& operator<<(ostream& out, const Complex& c) // 友元输出重载实现
{
    if (c.imag >= 0)                          // 如果虚部大于等于0
    {
        cout << c.real << "+" << c.imag << "i" << endl; // 输出 a+bi 并换行
    }
    else {                                   // 如果虚部为负
        cout << c.real << "-" << c.imag << "i" << endl; // 输出 a-bi（imag带符号）并换行
    }
    return out;                              // 返回输出流引用，支持连续输出
}   

Complex Complex::operator+(Complex other)    // 加法运算符重载的实现
{
    int r, i;                                // 定义临时实部和虚部
    r = this->real + other.real;             // 左操作数实部加右操作数实部
    i = this->imag + other.imag;             // 左操作数虚部加右操作数虚部
    return Complex(r, i);                    // 返回和复数
}

Complex Complex::operator-(Complex other)    // 减法运算符重载的实现
{
    int r, i;                                // 定义临时实部和虚部
    r = this->real - other.real;             // 左操作数实部减右操作数实部
    i = this->imag - other.imag;             // 左操作数虚部减右操作数虚部
    return Complex(r, i);                    // 返回差复数
}

int main()                                   // 主函数入口
{
    Complex c1(100,20);                      // 创建复数对象 c1：100+20i
    Complex c2(20, 100);                     // 创建复数对象 c2：20+100i
    cout << "c1" << c1 << endl;              // 输出 c1 的标识和内容
    cout << "c2" << c2 << endl;              // 输出 c2 的标识和内容
    Complex c3 = c1 * c2;                    // 使用重载的*计算 c1*c2，并初始化 c3
    cout << "c3=c1*c2" << c3 << endl;        // 输出乘法结果
    c3 -= c1;                                // 使用重载的 -=，将 c3 减去 c1
    cout << "c3-=c1" << c3 << endl;          // 输减去后的结果
    cin >> c3;                               // 使用重载的>>从键盘输入新的 c3
    cout << "输入c3后：" << c3 << endl;      // 输出新输入的复数
    return 0;                                // 程序正常结束
}