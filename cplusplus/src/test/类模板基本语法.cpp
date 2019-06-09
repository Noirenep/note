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

protected:
	T a;
};


//��ģ��������ģ����
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



//��ģ������ʱ,��Ҫ���廯ģ����,C++������Ҫ֪�����˾͵�����������ʲô���ӵ�
//Ҫ֪��������ռ���ڴ��С�Ƕ���,ֻ���������͹̶�������֪����η����ڴ�

//��ģ����������ͨ��
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


//��ģ��Ķ���
//��ģ���ʹ��
//��ģ������������

//C++������Ҫ�������� ����Ҫ<int>
void UseA( A<int> &a)
{
	a.printA();
}

int main01()
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