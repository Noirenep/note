# C++基础
## 01
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
2. 常量指针 
    指针的地址不能改变,地址的内容可以改变  
    `int* const pdata{&data};`
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