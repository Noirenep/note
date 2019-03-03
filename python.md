# Python学习笔记
> 书 图书馆《Python3学习笔记》TP311.561 143：1

## 1.概述

## 2.类型
使用type返回实例所属的类型  
```python
>>>type(123)
int
>>>type(1.2)
float
>>>type(“hello”)
str
```
每个对象都有唯一的id  
使用id()查看  
判断实例是否属于特定类型  
`>>>isinstance(1,int)  # Ture`  

```python
>>> type(int)
<class 'type'>
```

赋值
```python
>>> x=100
>>> x
100
>>> x += 2
>>> x
102
```

### 保留字  
`'False', 'None', 'True', 'and', 'as', 'assert', 'break', 'class', 'continue', 'def', 'del', 'elif', 'else', 'except', 'finally', 'for', 'from', 'global', 'if', 'import', 'in', 'is', 'lambda', 'nonlocal', 'not', 'or', 'pass', 'raise', 'return', 'try', 'while', 'with', 'yield'`


### 注释
```python
# 第一个注释
# 第二个注释
 
'''
第三注释
第四注释
'''
 
"""
第五注释
第六注释
"""
```

### 基本类型
```python
#!/usr/bin/python3
 
counter = 100          # 整型变量
miles   = 1000.0       # 浮点型变量
name    = "胖猫"     # 字符串
 
print (counter)
print (miles)
print (name)
```
多变量赋值  
```python
a = b = c = 1
a, b, c = 1, 2, "helloworld"
```

Python3 中有六个标准的数据类型：
- Number（数字）
- String（字符串）
- List（列表）
- Tuple（元组）
- Set（集合）
- Dictionary（字典）


Python3 的六个标准数据类型中：

- 不可变数据（3 个）：Number（数字）、String（字符串）、Tuple（元组）；
- 可变数据（3 个）：List（列表）、Dictionary（字典）、Set（集合）。  

进制
```python
0b110011 # bin 51
0o12  #oct 10
0x64  #hex 100

bin(100) #'0b1100100'
#同理 oct(100) hex(100) int()还原

#也可以指定
int("0b1100100",2)
 ```
```python
#python3
>>>4/2
2.0
>>>3//2
1
>>> 1.0//2.0
0.0
>>> -5/2
-2.5
>>> -5//2
-3

```

深拷贝浅拷贝
```python
import copy

x2 = copy.copy(x) #浅

x3 = copy.deepcopy(x) #深
```

>看到44页 浮点数 2019年03月03日11:52:05

