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

### 浮点数
```python
>>> 1/3
0.3333333333333333 

#转换
>>> float(100)
100.0
>>> float("-100.123")
-100.123

>>> int(2.6),int(-2.6)# 截掉小数部分
(2, -2) 

#使用math库对浮点数进行处理、
>>> from math import trunc,floor,ceil
>>> trunc(2.6), trunc(-2.6)#截掉小数部分
(2, -2)
>>> floor(2.6),floor(-2.6)#往数字小的方向取整数
(2, -3)
>>> ceil(2.6),ceil(-2.6)#往数字大的方向取整数
(3, -2)
```

### 四舍五入
```python
>>> round(0.5)
0
>>> round(1.5)
2
#python对四舍五入操作存在不确定性 不同版本存在差异
>>> round(0.500001)
1
```
### 字符串

字符串用法见才叫教程网站：[菜鸟教程--字符串](http://www.runoob.com/python3/python3-string.html)

字符串存储Unicode文本
```python
>>> s = "汉字"
>>> len(s)
2
>>> hex(ord("汉"))
'0x6c49'
>>> chr(0x6c49)
'汉'
```
### 元组（tuple）
>注：元组只能读 不能修改
```python 
tup1 = ('Google', 'Runoob', 1997, 2000)#定义元组
tup2 = (1, 2, 3, 4, 5, 6, 7 )
 
print ("tup1[0]: ", tup1[0])#访问元组
print ("tup2[1:5]: ", tup2[1:5])


tup1 = ();#创建空元组

#元组中只包含一个元素时，需要在元素后面添加逗号，否则括号会被当作运算符使用：
>>> tup1 = (50,)
>>> type(tup1)     # 加上逗号，类型为元组
<class 'tuple'>
```

|Python 表达式|	结果|	描述|
| :------: | :------: | :------: |
|len((1, 2, 3))|	3	|计算元素个数
|(1, 2, 3) + (4, 5, 6)|	(1, 2, 3, 4, 5, 6)	|连接
|('Hi!',) * 4|	('Hi!', 'Hi!', 'Hi!', 'Hi!')	|复制
|3 in (1, 2, 3)|	True|	元素是否存在
|for x in (1, 2, 3): print (x,)	|1 2 3	|迭代

### 字典 （dictionary）
须是唯一的，但值则不必。
```python
#!/usr/bin/python3
 
dict = {'Name': 'Runoob', 'Age': 7, 'Class': 'First'}
 
print ("dict['Name']: ", dict['Name'])
print ("dict['Age']: ", dict['Age'])

#修改
dict['Age'] = 8;               # 更新 Age
dict['School'] = "菜鸟教程"  # 添加信息
print ("dict['Age']: ", dict['Age'])#打印
print ("dict['School']: ", dict['School'])

#删除
del dict['Name'] # 删除键 'Name'
dict.clear()     # 清空字典
del dict         # 删除字典
```

### 集合（set）
>存储非重复元素 , 
集合（set）是一个无序的不重复元素序列。

可以使用大括号 { } 或者 set() 函数创建集合，注意：创建一个空集合必须用 set() 而不是 { }，因为 { } 是用来创建一个空字典。  
创建格式：
```python
>>>basket = {'apple', 'orange', 'apple', 'pear', 'orange', 'banana'}
>>> print(basket)                      # 这里演示的是去重功能
{'orange', 'banana', 'pear', 'apple'}
>>> 'orange' in basket                 # 快速判断元素是否在集合内
True
>>> 'crabgrass' in basket
False
 
>>> # 下面展示两个集合间的运算.
...
>>> a = set('abracadabra')
>>> b = set('alacazam')
>>> a                                  
{'a', 'r', 'b', 'c', 'd'}
>>> a - b                              # 集合a中包含而集合b中不包含的元素
{'r', 'd', 'b'}
>>> a | b                              # 集合a或b中包含的所有元素
{'a', 'c', 'r', 'd', 'b', 'm', 'z', 'l'}
>>> a & b                              # 集合a和b中都包含了的元素
{'a', 'c'}
>>> a ^ b                              # 不同时包含于a和b的元素
{'r', 'd', 'b', 'm', 'z', 'l'}
```


### 列表（list）
序列都可以进行的操作包括索引，切片，加，乘，检查成员。
```python
#!/usr/bin/python3
 
list = [1, 2, 3, 4, 5, 6, 7 ];
 
print ("list[0]: ", list[0])
print ("list[1:5]: ", list[1:5])

#列表的更新
print ("第三个元素为 : ", list[2])
list[2] = 2001
print ("更新后的第三个元素为 : ", list[2])

#列表的删除
print ("原始列表 : ", list)
del list[2]
print ("删除第三个元素 : ", list)
```
|Python 表达式|	结果|	描述|
| :------: | :------: | :------: |
|len([1, 2, 3])	|3|	长度
|[1, 2, 3] + [4, 5, 6]|	[1, 2, 3, 4, 5, 6]|	组合
|['Hi!'] * 4|	['Hi!', 'Hi!', 'Hi!', 'Hi!']	|重复
|3 in [1, 2, 3]	|True	|元素是否存在于列表中
|for x in [1, 2, 3]: print(x, end=" ")|	1 2 3	|迭代

---
## 3.表达式 
### 切片
```python
>>> x = [0,1,2,3,4,5,6]
>>> s = x[2:5]
>>> s
[2, 3, 4]
```
```
x[开始：结束：步长]  
x[:5]省略开始
x[2:]省略结束
x[:]完整复制
```
- 索引0表示正向第一个元素 -1表示反向第一个元素
```
x[::-1]反向步进 全部复制
x[5:2:-1] //5 4 3 反向
x[-2:-5:-1]// 负索引 5 4 3
x[-5:-2] //2 3 4
```
### 删除
```python
del x[3:7]
```

### 赋值
```python
>>> x = [0,1,2,3,4,5,6]
>>> x[2:5] =[100,200] #相当于先删除 再插入
>>> x
[0, 1, 100, 200, 5, 6]
```

### 控制流
#### if语句
>与其他语言if语句无太大差别,注意缩进就行了
```python
if condition_1:
    statement_block_1
elif condition_2:
    statement_block_2
else:
    statement_block_3
```
#### for
```
for <variable> in <sequence>:
    <statements>
else:
    <statements>
```
```python
languages = ["C", "C++", "Perl", "Python"] 
for x in languages:
    print (x)

#range
>>>for i in range(5):
...     print(i)
```
#### 推导式
[输出表达式 + 数据迭代源 + 过滤表达式（可选）]  
`[x+10 for x in range(10) if x%2==0]`  
[10, 12, 14, 16, 18]
#### while
```
while 判断条件：
    语句
```
while例子
```python
#!/usr/bin/env python3
 
n = 100
 
sum = 0
counter = 1
while counter <= n:
    sum = sum + counter
    counter += 1
 
print("1 到 %d 之和为: %d" % (n,sum))
```
while。。。else。。。
```python
#!/usr/bin/python3
 
count = 0
while count < 5:
   print (count, " 小于 5")
   count = count + 1
else:
   print (count, " 大于或等于 5")
```
>break语句会导致else语句不被执行，有break但是未被执行也算else
---
## 4.函数
`//TODO`

---
> *看到134页 函数 2019年03月03日16:40:53*

