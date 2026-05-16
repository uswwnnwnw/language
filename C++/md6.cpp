#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

class ba {
private:
	string name;
	double bal;
	static int total;
	mutable int qc;
public:
	ba(string n, double initbal) {
		name = n;
		bal = initbal;
		total++;
		qc = 0;
		cout << "[构造]" << name << "开户成功(余额:" << bal << ")|总户数:" << total << endl;
	}
	~ba() {
		cout << "[析构]" << name << "销户成功|剩余总户数:" << total - 1 << endl;
		total--;
	}
	void dep(double amount) {
		if (amount > 0) {
			bal += amount;
			cout << ">>" << name << "存入" << amount << "，当前余额" << bal << endl;

		}
	}
	bool wdraw(double amount) {
		if (amount > 0 && amount <= bal) {
			bal -= amount;
			cout << ">>" << name << "取出" << amount << ",当前余额：" << bal << endl;
			return true;
		}
		else {
			cout << "!!" << name << "取款:" << amount << "失败余额不足" << endl;
			return false;
		}
	}
	static int gettotal() {
		return total;
	}
	void disp()const {
		qc++;
		cout << "**" << name << "查询余额" << bal << "已被查" << qc << "次" << endl;
	}
};
int ba::total = 0;
int main() {
	cout << "=======start=======" << endl;
	ba b1("ss", 1000);
	ba b2("we", 100);
	ba b3("ojm", 8000);
	cout << "\n===" << endl;
	b1.dep(500);
	b2.wdraw(100);
	b2.wdraw(1000);
	cout << "\n显示信息" << endl;
	b1.disp();
	b1.disp();
	b2.disp();
	cout << "\rejwjrge" << endl;
	const ba b4("errge", 3000);
	b4.disp();
	return 0;

}

