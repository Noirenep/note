# PHP

> 和c语言差不多 不用学了

## 函数
```php
function fun_name($str1,$str2......){
    //fun_body
    return 0;
}
```

### 变量函数
>变量函数调用通过函数名实现
```php
<?php
function fun()
{
    echo "fun"
}
$func="fun";
$func();
?>
```


## 字符串
```php
$mystr ='world';
echo "Hello,$mystr";#Hello,world
echo 'Hello,$mystr';#Hello,$mystr
echo "Hi\tthere";   #Hi    there
echo 'Hi\tthere';   #Hi\tthere
```

- 字符串长度  
`int strlen(string $string)`

- 搜索字符串 替换字符串
```php
strstr()//返回bool 是否包含字符串
strpos() strrpos()//字符串第一次和最后一次出现的位置
substr_count()//出现次数
strpbrk()//再字符串中搜索字符集中的任意一个字符

str_replace()//替换
substr_replace()
strtr()

print()//格式化字符串
sprintf()

trim()//删除空白
ltrim()//只删除首部
rtrim()//只删除尾部

str_pad()//填充字符串函数
```

## 数组
创建数组  
`$authers = array("tom","tangyuan","ty");`

访问数组元素  
`数组名[索引];`

输出所有元素  
`print_r($array);`

## 正则表达式
### 语法规则
1. 行定位符  
 "^"表示行的开始  
 "$"表示行的结尾  

2. 单词定界符 `\b \B`   
 查找一个完整的单词`\bword\b`  

3. 正则表达式区分大小写   

4. 选择字符 "|"  

5. 连字符 "-"  
 `[a-zA-Z]`

6. 排除字符 "^"  

    `[^1-5]`  
7. 限定符
```
*   零次或多次   等价于{0,}
+   一次或多次   等价于{1,}
?   零次或一次   等价于{0,1}
{n} 匹配N次
{n,}至少n次
{n,m} n到m次
```

8. 点字符"." 匹配除了换行符以外的任意一个字符  

9. 转义字符
`. ? \ ( ) $ + [ ] ^& |`  
加`"\"`后转义  

10. `"\"`
```bash
    POSIX                   PCRE
[[:digit:]]  任何数字        \d
[[:alnum:]]  任何数字字母    \w
[[:alpha:]]  任何字母
[[:blank:]]  任何空白
[[:upper:]]  所有大写字母
[[:lower:]]  所有小写字母
[[:space:]]  空白字符        \s  相当于[\f\n\r\t\v]  \S非空白
```
11. 圆括号
    1. 改变作用范围 `|*^`  例如:`(my|your)baby`
    2. 分组(\.[0-9]{1,3}){3}
