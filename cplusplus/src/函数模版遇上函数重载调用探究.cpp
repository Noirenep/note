#include<iostream>
using namespace std;

int Max(int a, int b)
{
	cout << "��ͨ����" << endl;
	return a > b ? a : b;
}

template <typename T>
T Max(T a, T b)
{
	cout << "ģ�溯��" << endl;
	return a > b ? a : b;
}
template <typename T>
T Max(T a, T b, T c)
{
	cout << "3��������ģ�溯��" << endl;
	return Max(Max(a, b), c);
}


int main()
{
	int a = 1;
	int b = 2;

	cout << Max(a, b) << endl;//�����ϵ���,������ͨ����
	cout << Max<>(a, b) << endl;//ʹ��<>����ģ�溯��

	cout << Max(3.0, 4.0) << endl;//����и��õ�ƥ��
	cout << Max('c', 'd') << endl;//Ҳ��ģ��

	cout << Max(5.0, 6.0, 7.0) << endl; //����
	cout << Max(5, 6, 7) << endl;//��ģ�溯���������ͨ����

	cout << Max('a', '100') << endl;//��ͨ����������ʽ����ת��

	return 0;
}