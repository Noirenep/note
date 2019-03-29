# HTML5学习笔记

## 第一章

### 创建第一个HTML5界面
工具使用HBuilder  



## 第二章
### 块级标签
- h1~h6  
`<h1>标题文字</h1>`

- 水平线标签  
`<hr/>`

- 段落标签  
`<p>段落文字</p>`  
不同的段落之间会自动增加换行符  
段落上下方会各有一个空行的间隔  

- 换行标签  
`<br/>`  

- 预格式标签  
`<pre>按照原格式显示</pre>`

- 无序列表标签
```html
<ul type="disc">
	<li>第一项</li>
	<li>第二项</li>
</ul>
```
还可以是空圆点和方形  
`<ul type="circle">  <ul type="square">`  

- 有序列表标签
```html
<ol type="i">
	<li>第一项</li>
	<li>第二项</li>
	<li>第三项</li>
</ol>
```
`type可以为1 a A I i  `  

- div分区标签
`<div>这是一个div</div>`

### 行级标签
- `<img/>`图片标签  
`<img src="xx.png" alt="" title=""/>`  
> title属性 鼠标指上去显示的标题  
alt属性 图片无法加载显示的文字

- `<a></a>`超链接标签  
`<a href="#">这是一个超链接</a>`

## 第三章 表格

## 第四章 表单

## 第五章 CSS
>选择器和声明构成  

`selector {declaration1;declaration2....declarationN}`
- 选择器通常是需要改变的HTML元素
- 每条声明由一个属性(property)和一个值(value)构成,属性和值用冒号隔开
`selector{property:value}`

## JavaScript

## 备注
```html
<head>

</head>

<body></body>
```