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


