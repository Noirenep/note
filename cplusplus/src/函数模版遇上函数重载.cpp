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

//����   ������ͬһ������
void myswap(int a, char c)
{
	cout << "��ͨ����:a " << a << "c " << c << endl;
}

int main()
{
	int a = 10;
	char c = 'z';

	myswap(a, c);//��ͨ�����ĵ��� ���Խ�����ʽ������ת��  
	myswap(c, a);//��ͨ����
	myswap(a, a);//����ģ��ĵ��� ���������Ͳ����� ���ϸ�������ƥ��,�����Զ�����ת��

	return 0;
}