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


## 类和对象
### 类的封装

- public  
可以在类的内部和类的外部使用
- private  
只能在类内部被访问,不能在类的外部访问(子类中也不能用)
- protected  
只能在类的内部访问(在继承的子类中可以用),为了在家族中使用,为了继承

### 类的声明和类的实现分开
添加.h文件,编写class声明  
添加.cpp文件  
在.cpp中#include "类.h"  
在.cpp中添加域作用符 类名::

## day03
### 构造函数与析构函数
>C++的类可以定义一个与类名字相同的特殊成员函数  
可以有参数  
没有返回类型

### 构造函数的分类
- 无参数构造函数
- 有参数构造函数
- 拷贝构造函数:类名(const 类名& obj)
- 默认构造函数(默认的浅拷贝)

>C++对=操作符进行了增强


### 拷贝构造函数的四种调用时机
>用一个对象去初始化另一个对象
1.  = 
2. ()
3. 做函数参数(实参初始化形参)
4. 返回了一个新的匿名对象,return的时候调用拷贝构造

### new 和 delete
> malloc free / new delete

使用方法:

```c++
//基础类型:
    指针变量 = new 类型;
    指针变量 = new 类型(初始值);

    delete 指针变量;

//分配数组:
    指针变量 = new 类型[10];
    delete [] 指针变量;

//动态分配对象:
    对象指针变量 = new 类名(构造参数);
    delete 对象指针变量;
    
```

### static关键字
>属于所以对象的属性(静态成员变量)

class X{static int s;......};  
s属于整个类  
需要在全局初始化 int 类名::变量 = 0;  

>(静态成员函数)


用对象.函数名();  
用类名::函数名();  

**静态成员函数不能调用普通成员变量**


### 面向对象模型
> C++将变量和函数集中定义在一起 

代码是如何区分对象的?(this指针)  
静态成员函数没有this指针

### this指针
this -> a = a;

## day04
### 1. const写在什么地方没关系
const void const OPVar(int a,int b)const  
const修饰的this指针,this指向的内存空间不能改变

### 友元函数
friend
>全局函数,在类里声明friend,第一个参数是类的指针  
在外部可以访问私有属性  
友元破坏了类的封装性

### 友元类
```c++
class A
{
    friend class B;//B是A的友元
};
class B
{
private:
    A Aobject;//B中有个A , A是B的子属性
};
```

### 运算符重载
>不能重载的运算符 : `.   ::   .*   ?:   sizeof`
```c++
类型 类名::operator op(参数表)
{

}
```
全局函数(友元函数)  
`Complex operator+(Complex &c1,Complex &c2);`  
成员函数(具有this指针)  
`public: Complex operator-(Complex &c2);`  
成员函数比全局函数少一个参数  

根据需要,看函数返回引用,指针还是元素

### 一元运算符重载
```c++
//全局 前置++
friend Complex& operator++(Complex &c1);

//用成员函数 重载前置--
public:
Complex& operator--()
{
    this->a --;
    this->b --;
    return *this;
}
```

```c++
//全局  后置++
friend Complex operator++(Complex &c1,int);
//新拷贝一个  返回 然后再++

//成员函数 后置--
public:
Complex operator--(int)
{
    Complex tmp = *this;
    this->a--;
    this->b--;
    return tmp;
}
```

输入输出流 只能使用友元全局函数  
`friend ostream& operator <<(ostream &out ,Complex &c1);`  
> `>>   << 运算符`  结合顺序:从左到右

函数返回值当左值需要返回一个引用

### operator=
>等号操作符 从右到左  
`类名& operator=(类名 &obj)`  
释放旧内存,  
分配新内存,  
复制内容.  
return *this 

### operator[]
`int& operator[](int i)`

### operator==
`bool operator==(类名& obj)`


## day05
### operator()重载括号

### 字符串类
1. 无参构造函数
2. 有参构造函数
3. 拷贝构造函数

操作符重载:  
`<< >> != == > < = []`

## day06 继承 多继承 多态
>has-A包含关系  
 uses-A使用  
 is-A继承关系  
### 继承的基本概念
```c++
class 派生类名:访问属性 基类名表
{
    数据成员和函数声明
};
public      //公有继承 父类成员在子类中保持原有的访问属性
private     //私有继承 父类成员在子类中变为private成员
protected   //保护继承 父类的public变成protected 其他不变
```
1. 子类拥有父类所有的成员变量和成员函数
2. 子类就是一种特殊的父类
3. 子类对象可以当做父类对象使用
4. 子类对象可以拥有父类没有的方法和属性

>项目开发中,一般使用 **public** 继承

### 继承中的构造和析构
#### 类型(赋值)兼容性原则
类型兼容规则是指在需要基类对象的任何地方，都可以使用公有派生类的对象来替代。通过公有继承，派生类得到了基类中除构造函数、析构函数之外的所有成员。这样，公有派生类实际就具备了基类的所有功能，凡是基类能解决的问题，公有派生类都可以解决。类型兼容规则中所指的替代包括以下情况: 

- 子类对象可以当作父类对象使用
- 子类对象可以直接赋值给父类对象
- 子类对象可以直接初始化父类对象
- 父类指针可以直接指向子类对象
- 父类引用可以直接引用子类对象

用子类对象初始化父类对象

### 继承的内存模型
父类的加上子类新增加的属性

### 继承中的构造和析构
- 在子类对象构造时,需要调用父类构造函数对其继承得来的成员进行初始化
- 在子类对象析构时,需要调用父类析构函数对其继承得来的成员进行清理

先调用父类构造函数,再调用子类,析构的顺序和构造相反.


### 继承和混搭的构造和析构
子类构造函数
```c++
public:
    //子类构造      父类构造       组合对象构造
    child(char* p):Parent(p),obj1(3,4),obj2(5,6)
    {
        this->myp = p;
    }
```
调用顺序:  
先构造父类,再构造成员变量,再构造自己  
先析构自己,再析构成员变量,最后析构父类

### 继承中同名成员变量的处理方法
1. 当子类成员变量与父类重名,子类依然继承同名成员
2. 需要用域分辨符::进行同名区分(使用基类的需要显示使用限定符)
2. 默认使用自己类(子类)中的变量
3. 同名成员在存储在内存不同位置


### 继承中的static关键字
```c++
class A 
{
public:
    static int a;
};
int A::a = 100; //在类的外部初始化static变量
```
1. static关键字遵循派生类的访问控制规则


### 多继承
`class C: public A,public B`

### 多继承的二义性
解决方法 加virtual

### 多态
> 一个调用语句有多种表示形态  
在父类的函数写virtual关键字


### 多态的意义
>多态是设计模式的基础,是框架的基础

多态的3个条件:  
1. 要有继承
2. 要有虚函数重写  
3. 用父类指针(引用)指向子对象

### 虚析构函数
>指引 delete 运算符正确析构动态对象  
通过父类指针 把 所有子类对象的析构函数都执行一遍

### 重写 重载 重定义
函数重载:
- 必须在同一个类中
- 子类无法重载父类的函数,父类的同名函数将被名称覆盖
- 重载是在编译期间根据参数类型和个数决定函数调用

函数重写:
- 必须发生在父类和子类之间
- 父类和子类的函数原型完全相同
    - 使用virtual声明后产生多态
    - 不使用virtual是重定义
- 多态是在运行期间根据具体函数对象的类型决定函数调用

### 纯虚函数
>在基类中说明的虚函数,在基类中没有定义

格式:  
`virtual 类型 函数名(参数表) = 0;`

>含有纯虚函数的基类叫抽象类,抽象类不能建立对象,可以声明指针


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
