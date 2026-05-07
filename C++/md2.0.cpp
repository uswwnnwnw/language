#include<iostream>
using namespace std;

class Date {
private:
    int year, month, day;                         // 私密数据：年、月、日

public:
    Date();                                       // 声明默认构造函数
    Date(int y, int m, int d);                    // 声明带参构造函数
    Date(const Date& other);                      // 声明拷贝构造函数
    ~Date();                                      // 声明析构函数
    void setYear(int year);                       // 声明设置年份的成员函数
    Date& addYear(int n);                         // 声明增加年份并返回自身引用的函数
    void display() const;                         // 声明只读显示日期信息的函数
};

// 默认构造函数的定义：给一个默认日期 2000-1-1
Date::Date() {
    year = 2000;                                  // 默认年份 2000
    month = 1;                                    // 默认月份 1
    day = 1;                                      // 默认天数 1
    cout << "默认构造函数被调用，日期设置为：" << year << "-" << "-" << day << endl;
}

// 带参构造函数的定义：用外部传入的 y,m,d 初始化
Date::Date(int y, int m, int d) {
    year = y;                                     // 使用参数 y 设置年份
    month = m;                                    // 使用参数 m 设置月份
    day = d;                                      // 使用参数 d 设置天数
    // 伪代码提示：下面输出提示信息
    cout << "带参构造函数被调用，日期为：" << year << "-" << month << "-" << day << endl;
}

// 拷贝构造函数的定义：根据另一个 Date 对象创建新对象
Date::Date(const Date &other) {
    year = other.year;                            // 复制原对象的年份
    month = other.month;                          // 复制原对象的月份
    day = other.day;                              // 复制原对象的天数
    cout << "拷贝构造函数被调用，复制日期为：" << year << "-" << month << "-" << day << endl;
}

// 析构函数的定义：对象销毁时自动调用，显示被销毁的对象信息
Date::~Date() {
    cout << "析构函数被调用，销毁日期：" << year << "-" << month << "-" << day << endl;
}

// setYear 成员函数：用参数修改年份（通过 this 指针区分成员与参数）
void Date::setYear(int year) {
    this->year = year;                            // 将新年份赋值给当前对象的 year 成员
    cout << "setYear:年份修改为" << this->year << endl;
}

// addYear 成员函数：将年份增加 n，返回对象自身以支持链式调用
Date& Date::addYear(int n) {
    year += n;                                    // 当前对象年份加 n
    cout << "addYear:年份增加" << n << ",现在为" << year << endl;
    return *this;                                 // 返回当前对象的引用，支持 d.addYear(1).addYear(2)
}

// display 成员函数：在屏幕上显示当前日期（只读，不修改对象）
void Date::display() const {
    cout << "当前日期：" << year << "-" << month << "-" << day << endl;
}

// 普通函数 func：接收一个 Date 对象（传值，会调用拷贝构造函数）
void func(Date d) {                                // 伪代码：形参 d 是传值方式，会调用拷贝构造复制实参
    cout << "进入func函数，接收到的日期:";
    d.display();                                   // 显示传入副本的日期
    d.setYear(9999);                               // 修改副本的年份，不会影响原对象
}

// createDate 函数：在函数内部创建局部 Date 对象并返回（可能触发拷贝或移动）
Date createDate() {
    Date temp(2025, 1, 1);                        // 用带参构造函数创建局部对象 temp
    cout << "createDate即将返回" << endl;
    return temp;                                   // 返回局部对象，编译器可能优化掉拷贝
}

int main() {
    cout << "---测试1;默认构造函数---" << endl;
    Date d1;                                       // 调用默认构造函数，创建对象 d1，日期 2000-1-1
    d1.display();                                  // 显示 d1 的日期

    cout << "\n---测试2;带参构造函数---" << endl;
    Date d2(2023,4,5);                            // 调用带参构造函数，创建 d2：2023-4-5
    d2.display();                                  // 显示 d2 的日期

    cout << "\n---测试3;拷贝构造函数(d2初始化d3)---" << endl;
    Date d3(d2);                                   // 用 d2 初始化 d3，调用拷贝构造函数
    d2.display();                                  // 显示 d2，证明 d2 未变

    cout << "\n---测试4;拷贝构造函数（赋值风格)---" << endl;
    Date d4 = d2;                                  // 等价于 Date d4(d2)，调用拷贝构造函数
    d4.display();                                  // 显示 d4

    cout << "\n----- 测试5：传值调用函数 -----" << endl;
    func(d2);                                      // 将 d2 按值传递给 func，内部修改不影响原 d2
    cout << "func调用结束后，原d2对象：";
    d2.display();                                  // 再次显示 d2，验证年份未被修改

    cout << "\n----- 测试6：返回局部对象 -----" << endl;
    Date d5 = createDate();                        // 接收 createDate 返回的局部对象，可能触发拷贝或移动操作
    d5.display();                                  // 显示 d5 的日期

    cout << "\n----- 测试7：使用this指针的链式调用 -----" << endl;
    d1.setYear(2020);                              // 设置 d1 的年份为 2020
    d1.addYear(3);                                 // d1 的年份加 3 (2023)
    d1.addYear(1);                                 // d1 的年份再加 1 (2024)
    d1.display();                                  // 显示链式操作后的结果

    cout << "\n----- 测试8：观察析构顺序 -----" << endl;
    {
        Date blockDate(2024, 12, 25);             // 在代码块内创建局部对象，离开块时会析构
        cout << "进入代码块" << endl;
    }                                              // 代码块结束，blockDate 被析构
    cout << "离开代码块" << endl;

    cout << "\n----- main函数结束，所有局部对象将依次析构 -----" << endl;
    return 0;
}