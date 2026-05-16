#include <iostream>
using namespace std;
//类定义
class Date { // 重点：class。定义名为 Date 的类（设计图）
private: // 重点：private。私有权限，下方的变量只能在类内部访问（封装性）
    int year, month, day; // 重点：成员变量。存储对象的状态数据

public: // 重点：public。公有权限，外部 main 函数可以调用的接口
    Date(); // 重点：Date()。无参构造函数声明，用于初始化默认对象
    Date(int y, int m, int d); // 重点：重载构造。带参数初始化，提供灵活性
    Date(const Date& other); // 重点：拷贝构造。用一个已存在的对象去创建新对象
    ~Date(); // 重点：~Date()。析构函数，对象销毁（生命周期结束）时自动调用

    void setYear(int year); // 重点：void。设置年份的成员函数（Setter）
    Date& addYear(int n); // 重点：Date&。返回引用，支持链式编程（如 d1.add(1).display()）
    void display() const; // 重点：const。只读函数，保证函数内不会修改成员变量
}; // 注意：类定义结束必须有分号
//类成员函数实现
// 默认构造函数：当执行 Date d1; 时触发
Date::Date() { // 重点：::。作用域解析符，表示这个函数属于 Date 类
    year = 2000; // 默认初始化
    month = 1;
    day = 1;

    cout << "默认构造函数被调用，日期设置为："
         << year << "-" << month << "-" << day << endl;
}

// 带参构造函数：当执行 Date d2(2026, 5, 2); 时触发
Date::Date(int y, int m, int d) { 
    year = y; // 重点：赋值。将传入的参数 y 存入成员变量 year
    month = m;
    day = d;

    cout << "带参构造函数被调用，日期设置为："
         << year << "-" << month << "-" << day << endl;
}

// 拷贝构造函数：当执行 Date d3(d2); 时触发
Date::Date(const Date& other) { // 重点：const &other。通过引用访问原对象，避免无限递归
    year = other.year; // 重点：other.year。从“别人”那里复制数据
    month = other.month;
    day = other.day;

    cout << "拷贝构造函数被调用" << endl;
}

// 析构函数：在 main 结束、对象超出作用域时触发
Date::~Date() { // 重点：~。代表“反向”构造，清理现场
    cout << "析构函数被调用" << endl;
}

// Setter 函数
void Date::setYear(int year) { 
    this->year = year; // 重点：this->。区分“参数 year”和“成员变量 year”
}

// 功能函数：修改对象并返回自身
Date& Date::addYear(int n) { 
    year += n; // 修改成员变量
    return *this; // 重点：*this。返回当前对象本身，以便后续继续调用方法
}

// 打印函数
void Date::display() const { 
    cout << year << "-" << month << "-" << day << endl;
}
//主函数运行
int main() {
    Date d1; // 重点：d1。触发【默认构造函数】，创建对象 d1
    d1.display(); // 调用 display，显示 2000-1-1

    Date d2(2026, 5, 2); // 重点：参数。触发【带参构造函数】，创建对象 d2
    d2.display(); // 显示 2026-5-2

    Date d3(d2); // 重点：d3(d2)。触发【拷贝构造函数】，d3 的数据变得和 d2 一模一样
    d3.display(); // 显示 2026-5-2

    return 0; // 重点：return。main 函数结束，d1, d2, d3 依次触发【析构函数】
}