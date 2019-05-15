# C++基础

## day01
- 最简单的C++程序
- 命名空间
- C++对C语言的增强
    - 实用性
    - struct
    - 变量检测
    - 所有变量必须有类型
    + bool类型
    + 三目运算符返回运算本身
    + 引用(内部:常量指针)
    + const
    + C++引入符号表 常量是符号表 key value
    * const和#define (const有类型和作用域检查)
    * C++引用当左值,链式编程  
        函数当左值 必须返回一个引用
## day02

### 指针的引用
做输出:在被调用函数内分配内存(二级指针)

引用: 直接传入指针,修改引用的指针就是修改main函数中的指针  
int (Teacher **\* & pt1**);

### 常量引用
- 普通引用
```c++
int a = 10;
int &b = a;
```
- 常引用 
```c++
//常引用的初始化分为两种情况:

1. 用变量初始化常引用
//作用: 让变量拥有只读属性 ,,也就是不能通过y修改x
{
    int x = 20;
    const int &y = x;//常引用
}

2. 用字面量(常量)初始化常引用
{
    const int a = 10;
    const 
}
```
### 内联函数
inline  
1. 内联函数在编译时直接将函数体插入函数调用的地方
2. inline只是一种请求,编译器不一定会做
3. 内联省去了普通函数调用时的压栈,跳转和返回的开销

### 默认参数和占位参数
```c++
int fun(int a,int b = 3){}//默认参数
int fun(int a,int b,int){}//占位参数
int fun(int a,int b,int=0){}//默认参数+占位参数
```
占位参数调用时必须写上参数

### 函数重载
> 函数名和不同参数搭配  
函数重载是在静态编译时  
**函数的返回值不是重载判断的标准**

函数重载不能存在二义性(默认参数)

### 函数重载和函数指针在一起
>会严格比配函数指针的数据类型和候选者的数据类型
```c++
void myfunc(int a)
{
    printf("a:%d \n",a);
}

void myfunc(char* p)
{
    printf("p:%s \n",p);
}

void myfunc(int a,int b)
{
    printf("a:%d b:%d \n",a,b);
}

void myfunc(char* p1,char*  p2)
{
    printf("p1:%s p2:%s \n",p1,p2);
}
//1.声明一个函数类型
//void myfunc(int a,int b)
typedef void myTypeFunc(int a,int b);
//myTypeFunc* myfuncp = NULL;//通过函数类型定义函数指针变量

//2.声明一个函数指针类型
typedef void (* myPTypeFunc)(int a,int b);
//2.定义一个函数指针变量
//myPTypeFunc fp = NULL;通过函数指针类型定义一个函数指针

//直接定义函数指针变量
void (*myVarPFunc)(int a,int b);

int main()
{
    myPTypeFunc fp = NULL;//定义了一个函数指针变量,指向函数入口地址

    fp = myfunc;

    fp(1);//参数不对


    return 0;
}
```

## 08 TODO


---
# C++入门

## 第2章 基本数据类型
### 定义整型变量
```c++
int app_count{15};//用初始化列表
int foot_count{2},toe_count{10},head_count{1};//定义和初始化多个变量
```
>{ }是初始化列表 除了{}还可以用=或者() ,当然{}是C++11引入的语法,推荐使用

一些变量定义的示例
```c++
signed cahr ch{20};
long temperature{-50L};
long long height{250LL};
unsigned int toe_count{10U};
unsigned long angle_count{1000000UL};
```

等号左边的操作数可以是变量或者表达式,如果是表达式,必须是一个lvalue,lvalue表示一个永久的额内存位置(变量是lvalue)

### op=赋值运算符
一般形式:`lhs op= rhs;`  
例如:`x += 1`  
lhs是某个变量,rhs是一个表达式  
等价于`lhs = lhs op (rhs);`

### using
using std::cin;  
using std::cout;  
或者
using namespace std;//导入名称空间的所有名称

### 显示类型转换
`static_cast<type> (表达式)`

### 变量的生存期
三种:
- auto自动变量,从定义到块的结束
- static变量,从定义到程序结束
- 运行时分配的变量


## 第四章
### 条件运算符
```c
c = a > b ? a : b;
//等价于
if(a > b)
{
    c = a;
}
else
{
    c = b;
}

```

## 第5章 数组
### 数组的替代品
STL中定义了数组  
std::array<T,N> 和 std::vector<T>+0

### array<>
`#include <array>`   //For array<T,N>  
array不需要额外的系统开销 推荐使用  
只要array<>存储相同数量 类型的元素,就可以把一个array<>赋值给另一个array<>容器
```c
double total{};
for(size_t i {}, i< value.size(); ++i)
{
    total += values[i];
    total += values.at(i);//会检查安全性
        //如果超出范围 会抛出std::out_of_range类型的异常
}

for(auto value : values)
{
    total += value;
}
```
### vector
`#include <vector>`  //For vector<T>  
大小可以自动增加

std::vector<double> values;  
values.push_back(3.14159);

## 第六章 指针
>指针 = 地址+数据类型

### char类型的指针
`const char * pchar {"Hello world."}`

### 指针数组

### 常量指针和指向常量的指针
1. 指向常量的指针.  
    指针指向的内容不能改变,指针可以设置为指向其他内容  
    `const char* pstring {"some text that cannot be changed"}`  
    例如:`const int* pvalue{&value};`  
    **const在*的左边**
2. 常量指针 
    指针的地址不能改变,地址的内容可以改变  
    `int* const pdata{&data};`  
    **const在*的右边**
3. 指向常量的常量指针  
    都不能修改  
    `const int* const pvalue{&value}`

### 引用
假定定义了变量:  
double data {3.5};  
就可以定义一个左值引用,作为变量 data的别名   
double& rdata{data}; //Defomnes a reference to the variable data  
rdata += 2.5;

## 第七章 操作字符串
### 更好的丝捶英类型
首先 要定义头文件`#include <string>`  
string类型是有一个类模板定义  

### 定义string对象
1. 没有初始化列表(或者空对象)  
    string empty;
2. 初始化列表包含字符串字面量  
    string proverb {"Helloworld."};
3. 初始化列表包含已有的string对象  
    string sentence{ proverb };  
4.  初始化列表包含两个初始器 一个是字符串常量 一个是字面量用于初始化string对象的字符长度  
    string part_literal {"Helloworld",5};//Hello
5. 重复次数和字符字面量 比如6个z  
    string sleeping {6,'z'};
6. 初始化列表包含3个初始化器 一个是已有的string对象,一个是开头的索引,一个是字符串长度
    string phrase {proverb,0,5} ; //Hello

### string 对象的操作
- 赋值:  
string word{"rubbish"};  
word = "adjective"
- 连接字符串:  
string description{sleeping + " " +word + "whippersnapper"};
>注意:不能连续连接两个字符串字面量
- 访问

## 一些函数

```c
#include <cmath>  //三角函数 数值函数 abs sin co asin

```