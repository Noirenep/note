#include <iostream>

using namespace std;

//ģ���� ���Ͳ�����

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

//��ģ��Ķ���
//��ģ���ʹ��
//��ģ������������

//C++������Ҫ�������� ����Ҫ<int>
void UseA( A<int> &a)
{
	a.printA();
}

int main()
{
	//A a1(21);//ģ�����ǳ����,��Ҫ���廯 
	A<int> a1(33),a2(22),a3(66);
	//A<double> a1(3.3);
	a1.printA();

	//��ģ������������
	UseA(a1);
	UseA(a2);
	UseA(a3);

	return 0;
}