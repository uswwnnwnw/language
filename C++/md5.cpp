#include<iostream>
using namespace std;

class emp {
private:
	string name;
	int id;
public:
	emp(string n,int i):name(n),id(i){}
	virtual double pay()const = 0;
	virtual void show()const {
		cout << "姓名：" << name << "\t工号：" << id;
	}
	virtual ~emp() {
		cout << "emp析构：" << name << endl;
	}
	friend void showpay(const emp& e);
};

class salaried :public emp {
private:
	double sal;
public:
	salaried(string n,int i,double s):emp(n,i),sal(s){}
	double pay() const override {
		return sal;
	}
	void show() const override {
		cout << "[正式]";
		emp::show();
	}
	~salaried() {
		cout << "salaried析构" << endl;
	}
};

class hourly :public emp {
private:
	double w;
	double h;
public:
	hourly(string n,int i,double wage,double hour):emp(n,i),w(wage),h(hour){}
	double pay() const override {
		if (h <= 160)
			return w * h;
		else
			return w * 160 + w * (h - 160) * 1.5;
	}
	void show() const override {
		cout << "[小时工]";
		emp::show();
	}
	~hourly() {
		cout << "hourly析构" << endl;
	}
};

class sales :public emp {
private:
	double base;
	double sale;
public:
	sales(string n,int i,double b,double s):emp(n,i),base(b),sale(s){}

	double pay() const override {
		return base + sale * 0.1;
	}
	void show() const override {
		cout << "[销售]";
		emp::show();
	}
	~sales() {
		cout << "sales析构" << endl;
	}
};
void showpay(const emp& e) {
	cout << "工资" << e.pay() << endl;
}

int main()
{
	emp* e[3];
	e[0] = new salaried("张三", 1001, 8000);
	e[1] = new hourly("李四", 1002, 50, 180);
	e[2] = new sales("王五", 1003, 2000, 50000);

	for (int i = 0;i < 3;++i) {
		e[i]->show();
		cout << "\t";
		showpay(*e[i]);
		cout << "--------" << endl;
	}
	for (int i = 0;i < 3;++i) {
		delete e[i];
		cout << endl;
	}
	return 0;
}
