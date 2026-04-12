#include<iostream>
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
	void display()const;
};
Date::Date() {
	year = 2000;
	month = 1;
	day = 1;
	cout << "默认构造函数被调用，日期设置为：" << year << "-" << "-" << day << endl;
}
Date::Date(const Date &other) {
	year = other.year;
	month = other.month;
	day = other.day;
	cout << "拷贝构造函数被调用，复制日期为：" << year << "-" << "-" << day << endl;
}
Date::~Date() {
	cout << "析构函数被调用，销毁日期：" << year << "-" << month << "-" << day << endl;
}
void Date::setYear(int year) {
	this->year = year;
	cout << "setYear:年份修改为" << this->year << endl;
}
Date& Date::addYear(int n) {
	year += n;
	cout << "addYear:年份增加" << n << ",现在为" << year << endl;
	return *this;
}
void Date::display()const {
	cout << "当前日期：" << year << "-" << month << "-" << day << endl;
}
void func(Date d) {
	cout << "进入func函数，接收到的日期:";
	d.display();
	d.setYear(9999);
}
Date createDate() {
	Date temp(2025, 1, 1);
	cout << "createDate即将返回" << endl;
	return temp;
}
int main()
{
	cout << "---测试1;默认构造函数---" << endl;
	Date d1;
	d1.display();

	cout << "\n---测试2;带参构造函数---" << endl;
	Date d2(2023,4,5);
	d2.display();

	cout << "\n---测试3;拷贝构造函数(d2初始化d3)---" << endl;
	Date d3(d2);
	d2.display();

	cout << "\n---测试4;拷贝构造函数（赋值风格)---" << endl;
	Date d4 = d2;
	d4.display();

	cout << "\n----- 测试5：传值调用函数 -----" << endl;
	func(d2);              
	cout << "func调用结束后，原d2对象：";
	d2.display();          

	cout << "\n----- 测试6：返回局部对象 -----" << endl;
	Date d5 = createDate(); 
	d5.display();

	cout << "\n----- 测试7：使用this指针的链式调用 -----" << endl;
	d1.setYear(2020);
	d1.addYear(3);
	d1.addYear(1); 
	d1.display();

	cout << "\n----- 测试8：观察析构顺序 -----" << endl;
	{
		Date blockDate(2024, 12, 25);
		cout << "进入代码块" << endl;
	} 
	cout << "离开代码块" << endl;

	cout << "\n----- main函数结束，所有局部对象将依次析构 -----" << endl;
	return 0;
}






