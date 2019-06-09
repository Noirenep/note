#include <iostream>
using namespace std;

//template 告诉C++开始泛型编程
template <typename T>
void myswap(T &a, T &b)
{
	T c;
	c = a;
	a = b;
	b = c;
}

//函数模版的调用
int main()
{
	//显示类型调用
	{
		int x = 10;
		int y = 20;
		myswap<int>(x, y);//函数模版显示类型调用
		myswap(x, y);//自动类型推导(很少用)
	}
	{
		char a = 'a';
		char b = 'b';
		myswap<char>(a, b);//函数模版显示类型调用
	}
	//自动类型推导
	return 0;
}