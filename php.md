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


