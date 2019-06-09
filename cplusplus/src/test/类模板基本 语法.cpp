#include <iostream>

using namespace std;

//模板类 类型参数化

template <typename T>
class A
{
public:
	A(T a)
	{
		this->a = a;
	}

	void printA()
	{
		cout << "a: " << a << endl;
	}

private:
	T a;
};

//类模板的定义
//类模板的使用
//类模板做函数参数

//C++编译器要求具体的类 所以要<int>
void UseA( A<int> &a)
{
	a.printA();
}

int main()
{
	//A a1(21);//模板类是抽象的,需要具体化 
	A<int> a1(33),a2(22),a3(66);
	//A<double> a1(3.3);
	a1.printA();

	//类模板做函数参数
	UseA(a1);
	UseA(a2);
	UseA(a3);

	return 0;
}