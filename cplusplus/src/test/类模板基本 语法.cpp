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

protected:
	T a;
};


//从模板类派生模板类
template<typename T>
class C :public A<T>
{
public:
	C(T c, T a) :A<T>(a)
	{
		this->c = c;
	}
	void printC()
	{
		cout <<"c: "<< c << endl;
	}
private:
	T c;
};

int main()
{

	C<int > c1(3, 5);
	c1.printA();
	c1.printC();
	return 0;
}



//子模版派生时,需要具体化模板类,C++编译器要知道服了就的数据类型是什么样子的
//要知道父类所占的内存大小是多少,只有数据类型固定下来才知道如何分配内存

//从模板类派生普通类
class B :public  A<int>
{
public:
	B(int a = 20, int b=10) :A<int>(a)
	{
		this->b = b;
	}
	void printB()
	{
		cout << "a: " << a << "  B: " << b << endl;
	}
private:
	int b;
};

int main02()
{
	B b1(1,2);
	b1.printB();
	
	return 0;
}


//类模板的定义
//类模板的使用
//类模板做函数参数

//C++编译器要求具体的类 所以要<int>
void UseA( A<int> &a)
{
	a.printA();
}

int main01()
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