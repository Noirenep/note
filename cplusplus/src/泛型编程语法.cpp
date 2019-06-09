#include <iostream>
using namespace std;

//template ����C++��ʼ���ͱ��
template <typename T>
void myswap(T &a, T &b)
{
	T c;
	c = a;
	a = b;
	b = c;
}

//����ģ��ĵ���
int main()
{
	//��ʾ���͵���
	{
		int x = 10;
		int y = 20;
		myswap<int>(x, y);//����ģ����ʾ���͵���
		myswap(x, y);//�Զ������Ƶ�(������)
	}
	{
		char a = 'a';
		char b = 'b';
		myswap<char>(a, b);//����ģ����ʾ���͵���
	}
	//�Զ������Ƶ�
	return 0;
}