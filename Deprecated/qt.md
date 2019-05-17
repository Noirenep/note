# Qt 5.9 C++开发笔记

## 1.信号与槽
- 信号(Signal)就是在特定情况下被发射的事件
- 槽(SLot)就是对信号响应的函数

信号与槽关联是用QObject::connect()函数实现的
```c++
QObject::connect(sender,SINGAL(singal()),receiver,SLOT(slot()));

connect(btn,SIGNAL(clicked()),this,SLOT(on_clicked()));
connect(btn,&QPushButton::clicked,this,&Widget::on_clicked);
//connect函数 每个参数都是指针类型  不一定是窗口
```