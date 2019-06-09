#include<iostream>
using namespace std;

template <typename T>
void myswap(T& a, T& b)
{
	T c;
	c = a;
	a = b;
	b = c;
}

//重载   发生在同一作用域
void myswap(int a, char c)
{
	cout << "普通函数:a " << a << "c " << c << endl;
}

int main()
{
	int a = 10;
	char c = 'z';

	myswap(a, c);//普通函数的调用 可以进行隐式的类型转换  
	myswap(c, a);//普通函数
	myswap(a, a);//函数模版的调用 本质是类型参数化 将严格按照类型匹配,不会自动类型转换

	return 0;
}