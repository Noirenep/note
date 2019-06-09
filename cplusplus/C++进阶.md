# C++进阶

## 函数模版
代码: [泛型编程语法.cpp](./src/泛型编程语法.cpp)
```c++
template <typename T>
void myswap(T &a, T &b)
{
	T c;
	c = a;
	a = b;
	b = c;
}
```


### 函数模版当函数参数
对字符数组  int数组进行排序  
代码: [函数模版当函数参数.cpp](./src/函数模版当函数参数.cpp)
```c++
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
```

### 函数模版遇上函数重载
#### 函数模版和普通函数区别结论:  
- 函数模版不允许自动类型转化
- 普通函数能够自动类型转换

代码: [函数模版遇上函数重载.cpp](./src/函数模版遇上函数重载.cpp)


#### 函数模版和普通函数一起调用规则:  
1. 函数模版可以像普通函数一样被重载
2. C++编译器优先考虑普通函数
3. 如果函数模版可以产生一个更好的匹配,那么选择模版
4. 可以通过空模版实参列表的语法限定编译器只通过模版匹配

代码: [函数模版遇上函数重载调用探究.cpp](./src/函数模版遇上函数重载调用探究.cpp)


### 函数模版机制剖析
预处理(Pre-Processing)  
编译(Compiling)  
汇编(Assembling)  
链接(Linking)  
```bash
gcc -E 1.c -o 1.i
gcc -S 1.i -o 1.s
gcc -c 1.s -o 1.o
gcc 1.o -o 1.exe
```
本质:C++编译器生成了两个函数
> day09_09

## 类模板
### 单个类的语法
```cpp
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

```
### 模板类继承
//从模板类派生普通类
```c++
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
```

//从模板类派生模板类
```c++
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
```


## C++的类型转换



## 异常处理机制


## C++输出输出流