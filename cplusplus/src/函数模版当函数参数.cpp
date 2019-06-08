#include<iostream>
using namespace std;

//函数模版本质:类型参数化
template <typename T,typename T2>
int mySort(T* array, T2 size)
{
	if (array== NULL)
	{
		return -1;
	}

	for (T2 i = 0; i < size; i++)
	{
		for (T2 j = i+1; j < size; j++)
		{
			if (array[i]<array[j])
			{
				T tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
		}
	}
	return 0;
}

template <typename T>
int myPrint(T* array, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << array[i]<< ", ";
	}
	cout << endl;
	return 0;
}

int main()
{
	{//int 类型
		int myarray[] = { 11,22,33,44,565,8,48,18,54 };
		int size = sizeof(myarray) / sizeof(*myarray);

		mySort<int, int>(myarray, size);
		myPrint<int>(myarray, size);
	}
	{//char类型的
		char buf[] = "wertyuios7d5f1g6bnm";
		int len = strlen(buf);

		mySort<char, int>(buf, len);
		myPrint<char>(buf, len);
	}

	return 0;
}