#include<iostream>
using namespace std;
//基类
class Person{
private:
	string name;
	int age;
public:
	Person(string n, int a) :name(n), age(a) {};
	void display(void);
	//方法纯虚，只是一个接口，具体表现要看派生
	virtual void study(void);

};
//派生
class Student:public Person{
	//扩展
private:
	string school;
	int grade;
public:
	Student(string n, int a, string s, int g)
		:Person(n, a), school(s), grade(g) {};
	void display(void);
	void take(void);
};

void Person::display(void)
{
	cout << "name is" << name << " " << "age is" << age << endl;
}

void Student::take(void)
{
	cout << "I need take class！" << endl;
}

void Person::study(void)
{
	cout << "I can study!" << endl;
}

void Student::display(void)
{
	//调用基类display
	Person::display();
	//增加显示自身
	cout << "school is" << school << endl;
	cout << "grade is" << grade << endl;
}

int main()
{
	Person p1("老王", 50);
	Student s1("小李", 18, "DP", 2);

	p1.display();
	p1.study();

	s1.display();
	s1.study();
	s1.take();

	//向上转型
	Person* p = &p1;
	p->display();

	p = &s1;//s1向上转型Person
	p->display();
	
	//p->take();p本身person类型没有take行为

	return 0;
}
