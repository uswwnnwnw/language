#include<iostream>
using namespace std;

// 基类 Person 的定义
class Person{
private:
    string name; // 私有变量：姓名
    int age;     // 私有变量：年龄
public:
    // 构造函数，初始化对象时使用
	Person(string n, int a) :name(n), age(a) {};
    void display(void); // 显示方法
    virtual void study(void); // 纯虚函数，用于多态实现
};

// 派生类 Student 的定义
class Student:public Person{
private:
    string school; // 私有变量：学校名称
    int grade;     // 私有变量：年级
public:
    // 构造函数，初始化对象时使用
	Student(string n, int a, string s, int g)
		:Person(n, a), school(s), grade(g) {};
    void display(void); // 显示方法
    void take(void);     // 具体行为的实现
};

// 基类 Person 的显示方法实现
void Person::display(void){
	cout << "name is" << name << " " << "age is" << age << endl;
}

// 派生类 Student 的具体行为实现：study 方法
void Student::take(void){
	cout << "I need take class！" << endl;
}

// 基类 Person 的显示方法实现
void Person::study(void){
	cout << "I can study!" << endl;
}

// 派生类 Student 的显示方法实现，调用基类 display 方法并增加自身信息
void Student::display(void){
    // 调用基类的 display 方法
	Person::display();
    // 增加显示自身的信息
	cout << "school is" << school << endl;
	cout << "grade is" << grade << endl;
}

int main(){
    // 创建 Person 类的对象 p1，初始化姓名为“老王”，年龄为 50
	Person p1("老王", 50);
    // 创建 Student 类的对象 s1，初始化姓名为“小李”，年龄为 18，学校名称为“DP”，年级为 2
	Student s1("小李", 18, "DP", 2);

    // 调用显示方法 display 和 study 对 p1 进行操作
	p1.display();
	p1.study();

    // 调用显示方法 display 和 study 对 s1 进行操作
	s1.display();
	s1.study();
	s1.take();

    // 向上转型，将 Student 类的对象 s1 指针转换为 Person 类的指针 p
	Person* p = &p1;
    // 调用 display 方法显示 p1 的信息
	p->display();

    // 将 s1 指针转换为 Person 类的指针 p，再次调用 display 方法
    p = &s1;
	p->display();
	
    // 由于 Person 类没有定义 take 方法，尝试访问会导致错误或编译失败
    // p->take(); 这一行代码在实际运行时会报错，因为 p 指向的是 Person 类的对象，
    // 而 Student 类的 take 方法无法通过 Person 类的对象调用。
	return 0;
}

