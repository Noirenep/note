#include<iostream>
using namespace std;

int Max(int a, int b)
{
	cout << "普通函数" << endl;
	return a > b ? a : b;
}

template <typename T>
T Max(T a, T b)
{
	cout << "模版函数" << endl;
	return a > b ? a : b;
}
template <typename T>
T Max(T a, T b, T c)
{
	cout << "3个参数的模版函数" << endl;
	return Max(Max(a, b), c);
}


int main()
{
	int a = 1;
	int b = 2;

	cout << Max(a, b) << endl;//都符合调用,优先普通函数
	cout << Max<>(a, b) << endl;//使用<>调用模版函数

	cout << Max(3.0, 4.0) << endl;//如果有更好的匹配
	cout << Max('c', 'd') << endl;//也是模版

	cout << Max(5.0, 6.0, 7.0) << endl; //重载
	cout << Max(5, 6, 7) << endl;//在模版函数里调用普通函数

	cout << Max('a', '100') << endl;//普通函数可以隐式类型转换

	return 0;
}