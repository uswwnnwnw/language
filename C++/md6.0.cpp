#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string owner;                           // 账户持有人姓名
    double balance;                         // 账户余额
    static int totalAccounts;               // 静态成员：记录所有账户总数
    mutable int queryCount;                 // 可变成员：记录该账户被查询的次数，允许在const函数中修改

public:
    // 构造函数：初始化持有人和余额，账户总数+1，查询次数初始为0
    BankAccount(const string& name, double initialBalance)
        : owner(name), balance(initialBalance), queryCount(0) {
        totalAccounts++;                    // 每创建一个对象，静态计数器加1
        cout << "构造函数：创建账户 " << owner << "，余额 " << balance << "，当前账户总数 " << totalAccounts << endl;
    }

    // 析构函数：对象销毁时账户总数-1
    ~BankAccount() {
        totalAccounts--;                    // 每销毁一个对象，静态计数器减1
        cout << "析构函数：销毁账户 " << owner << "，当前账户总数 " << totalAccounts << endl;
    }

    // 存款函数：增加余额
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << owner << " 存款 " << amount << "，当前余额 " << balance << endl;
        }
    }

    // 取款函数：余额不足返回false，否则扣款并返回true
    bool withdraw(double amount) {
        if (amount > balance) {
            cout << owner << " 取款失败：余额不足（请求 " << amount << "，余额 " << balance << "）" << endl;
            return false;
        }
        balance -= amount;
        cout << owner << " 取款 " << amount << "，当前余额 " << balance << endl;
        return true;
    }

    // 静态成员函数：返回当前账户总数
    static int getTotalAccounts() {
        return totalAccounts;
    }

    // 常量成员函数：显示账户信息，并自增查询计数（因为queryCount是mutable）
    void display() const {
        cout << "账户持有人：" << owner << "，余额：" << balance << endl;
        ++queryCount;                       // mutable允许在const函数中修改
        cout << "该账户已被查询 " << queryCount << " 次" << endl;
    }
};

// 静态成员变量必须在类外定义并初始化
int BankAccount::totalAccounts = 0;

int main() {
    cout << "初始账户总数：" << BankAccount::getTotalAccounts() << endl;

    // 创建三个账户，观察构造函数和totalAccounts变化
    BankAccount acc1("张三", 1000.0);
    BankAccount acc2("李四", 500.0);
    BankAccount acc3("王五", 2000.0);

    cout << "\n当前账户总数：" << BankAccount::getTotalAccounts() << endl;

    // 测试存取款操作
    acc1.deposit(200);
    acc1.withdraw(300);
    acc1.withdraw(1500);                   // 余额不足

    acc2.withdraw(100);
    acc2.deposit(50);

    // 测试查询和mutable成员
    acc1.display();
    acc1.display();                         // 查询次数会累加
    acc3.display();

    // 创建一个块作用域，观察析构函数
    {
        BankAccount temp("临时账户", 100.0);
        cout << "块内账户总数：" << BankAccount::getTotalAccounts() << endl;
    }                                       // temp在此析构，总数减1
    cout << "离开块后账户总数：" << BankAccount::getTotalAccounts() << endl;

    cout << "\n主函数即将结束，所有局部对象将自动析构..." << endl;
    return 0;
}