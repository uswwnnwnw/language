#include <iostream>
using namespace std;

class Date {
private:
    int year, month, day;

public:
    Date();
    Date(int y, int m, int d);
    Date(const Date& other);
    ~Date();

    void setYear(int year);
    Date& addYear(int n);
    void display() const;
};

Date::Date() {
    year = 2000;
    month = 1;
    day = 1;

    cout << "默认构造函数被调用，日期设置为："
         << year << "-" << month << "-" << day << endl;
}

Date::Date(int y, int m, int d) {
    year = y;
    month = m;
    day = d;

    cout << "带参构造函数被调用，日期设置为："
         << year << "-" << month << "-" << day << endl;
}

Date::Date(const Date& other) {
    year = other.year;
    month = other.month;
    day = other.day;

    cout << "拷贝构造函数被调用" << endl;
}

Date::~Date() {
    cout << "析构函数被调用" << endl;
}

void Date::setYear(int year) {
    this->year = year;
}

Date& Date::addYear(int n) {
    year += n;
    return *this;
}

void Date::display() const {
    cout << year << "-" << month << "-" << day << endl;
}

int main() {
    Date d1;
    d1.display();

    Date d2(2026, 5, 2);
    d2.display();

    Date d3(d2);
    d3.display();

    return 0;
}