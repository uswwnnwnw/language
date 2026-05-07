#include <iostream>
#include <string>
using namespace std;

// 定义基类 Person
class Person {
private:
    string name;                                     // 私有：姓名
    int age;                                         // 私有：年龄
public:
    Person(const string& n, int a) : name(n), age(a) { // 构造函数，初始化姓名和年龄
        cout << "Person 构造函数: " << name << ", " << age << endl; // 输出构造信息
    }

    virtual ~Person() {                              // 虚析构函数，确保多态时正确释放
        cout << "Person 析构函数: " << name << endl; // 输出析构信息
    }

    void display() const {                           // 显示基本信息，只读
        cout << "姓名: " << name << ", 年龄: " << age << endl;
    }

    string getName() const { return name; }          // 获取姓名，供派生类间接访问私有成员
};

// 定义派生类 Student，public 继承 Person
class Student : public Person {
private:
    string school;                                   // 私有：学校
    int grade;                                       // 私有：年级
public:
    Student(const string& n, int a, const string& s, int g)
        : Person(n, a), school(s), grade(g) {        // 初始化列表显式调用基类构造函数
        cout << "Student 构造函数: " << school << ", " << grade << endl; // 输出派生类构造信息
    }

    ~Student() {                                     // 派生类析构函数
        cout << "Student 析构函数: " << getName() << endl; // 调用基类公有函数获取名字
    }

    void study() const {                             // 派生类新增功能：学习
        cout << getName() << " 正在学习，年级 " << grade << endl;
    }

    void displayInfo() const {                       // 展示所有信息（基类+派生类）
        display();                                   // 调用基类的 display
        cout << "学校: " << school << ", 年级: " << grade << endl;
    }
};

int main() {
    cout << "=== 直接创建派生类对象 ===" << endl;
    Student stu("张三", 20, "清华大学", 3);           // 创建 Student 对象，观察构造顺序
    stu.displayInfo();                               // 显示完整信息
    stu.study();                                     // 调用派生类方法

    cout << "\n=== 向上转型：基类指针指向派生类对象 ===" << endl;
    Person* pPerson = &stu;                          // 将派生类对象的地址赋给基类指针
    pPerson->display();                              // 通过基类指针调用 display，只能访问基类成员

    cout << "\n=== 动态分配派生类对象，基类指针管理 ===" << endl;
    Person* p = new Student("李四", 22, "北京大学", 4); // 在堆上创建 Student，基类指针指向它
    p->display();                                    // 调用 display
    delete p;                                        // 通过虚析构正确释放派生类对象

    cout << "\n=== 程序结束，局部对象自动析构 ===" << endl;
    return 0;                                        // stu 离开作用域，自动调用析构（先派生后基类）
}