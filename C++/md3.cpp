#include<iostream>
using namespace std;

class Complex
{
private:
	int real;
	int imag;
public:

	Complex(int r, int i) :real(r), imag(i) {};
	Complex operator+(Complex other);
	Complex operator-(Complex other);
	Complex operator*(Complex other);
	Complex operator-=(Complex other);

	
	void show();
	friend istream& operator>>(istream& in, Complex& c);
	friend ostream& operator<<(ostream& out, const Complex& c);
};
Complex Complex::operator*(Complex other)
{
	int r, i;
	r = this->real * other.real;
	i = this->imag * other.imag;
	return Complex(r, i);
}
Complex Complex::operator-=(Complex other)
{
	int r, i;
	r = real -= other.real;
	i = imag -= other.imag;
	return *this;
}
void Complex::show()
{
	if (imag >= 0)
	{
		cout << real << "+" << imag << "i" << endl;
	}
	else {
		cout << real << "-" << imag << "i" << endl;
	}
}
istream& operator>>(istream& in, Complex& c)
{
	cout << "输入实部，虚部";
	in >> c.real >> c.imag;
	return in;
}
ostream& operator<<(ostream& out, const Complex& c)
{
	if (c.imag >= 0)
	{
		cout << c.real << "+" << c.imag << "i" << endl;
	}
	else {
		cout << c.real << "-" << c.imag << "i" << endl;
	}
	return out;
}	
Complex Complex::operator+(Complex other)
{
	int r, i;
	r = this->real + other.real;
	i = this->imag + other.imag;
	return Complex(r, i);
}
Complex Complex::operator-(Complex other)
{
	int r, i;
	r = this->real - other.real;
	i = this->imag - other.imag;
	return Complex(r, i);
}



int main()
{
	Complex c1(100,20);
	Complex c2(20, 100);
	cout << "c1" << c1 << endl;
	cout << "c2" << c2 << endl;
	Complex c3 = c1 * c2;
	cout << "c3=c1*c2" << c3 << endl;
	c3 -= c1;
	cout << "c3-=c1" << c3 << endl;
	cin >> c3;
	cout << "输入c3后：" << c3 << endl;

	return 0;
}

