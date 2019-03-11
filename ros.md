# ROS笔记
> 编辑时间：2019年3月11日20:13:18

## 1.安装

[官网教程链接](http://wiki.ros.org/kinetic/Installation/Ubuntu)
> 根据官网的安装步骤，添加仓库，添加key，更新

镜像选择清华的  
`sudo sh -c '. /etc/lsb-release && echo "deb http://mirrors.tuna.tsinghua.edu.cn/ros/ubuntu/ $DISTRIB_CODENAME main" > /etc/apt/sources.list.d/ros-latest.list'
`
> sudo apt-get install ros-kinetic-desktop-full

### 配置ROS
初始化rosdep  
`sudo	rosdep	init	&&	rosdep	update`

### 环境配置
`echo "source /opt/ros/kinetic/setup.bash" >> ~/.bashrc
`   
然后执行  
`source ~/.bashrc
`
### 安装其他一些需要的包
`sudo apt install python-rosinstall python-rosinstall-generator python-wstool build-essential
`

## 2.测试ROS
输入代码 roscore  
rosrun	turtlesim turtlesim_node    
rosrun	turtlesim turtle_teleop_key    

## 3.ROS工程文件系统结构
#### catkin workspace
```bash
build
devel
src CMakeLists.txt
    /package1 #src下面有若干package
    /package2
        CMakeList.txt #源文件 依赖项 编译规则 目标文件
        package.xml 
        #属性信息 包名 作者 依赖项（build_depend run_depend） 版本
        /action #动作
            *.action
        /config
            *.yaml
        /images
        /include
            *.h
        /launch
            *.launch
        /msg
            *.msg
        /src
            *.cpp
            #也可以放py文件
        /srv
            *.srv
        /scripts
            *.py
            *.sh
```

## 4.ROS编程基本步骤
1. 进入catkin工作空间的目录 如cd ~/tutorial_ws  
2.  执行编译操作 catkin_make  
3. source工作工作空间的bash/zsh文件 source ~/tutorial_ws/devel/setup.zsh  
4. rospack profile  
5. 运行 程序 roslaunch   

>说明：我用的shell是zsh 如果使用的是默认bash，则source的时候应该把所有zsh替换为bash

## 5.创建工作空间和包
#### 创建一个工作空间

注意:需要创建src文件夹

```
mkdir -p catkin_ws/src
cd catkin_ws
catkin_make
```  

#### 创建一个包
```
cd src
catkin_create_pkg test1 roscpp rospy std_msgs nav_msgs
```


## 6.ROS的几种通信方式以及命令行控制
- master 节点管理器

roscore启动了以下内容  
```	
master节点管理器
rosout日志输出 
parameter server参数服务器 
``` 
node就是ROS的进程
#####node相关指令
```bash
rosrun 包名 节点名
rosnode list查看运行的node
rosnode info [nodename节点名]
rosnode kill 节点名
roslaunch [pkgname] [filename.launch]
```

### ROS的通信方式如下：
- Topic　话题
- Service　服务
- parameter Service 参数服务器
- Actionlib 动作库

关于rostopic的命令
```bash
rostopic list列出topic
rostopic info /topic_name # 显示某个topic的属性信息
rostopic echo /topic_name # 显示内容
rostopic pub /tpoicname # 向topic发布内容

rosmsg list
rosmsg show /msg_name
```
service的相关指令
```bash
rosservice list
rosservice info [/service_name]
rosservice call  [/service_name] [TAB]
rossrv list
rossrv show [/srv_name]
```
parameter Service
```bash
rosparam set param_key param_value	 #设置参数
rosparam get param_key	#显示参数
rosparam load file_name	#从文件加载参数
rosparam dump file_name	#保存参数到文件
rosparam delete	 #删除参数
rosparam list	 #列出参数名称
rosparam dump test.yaml
```
 
## 7.ROS TopicDemo（C++）[官网](http://docs.ros.org/api/roscpp/html/index.html)
### Topic 定义
>Topic异步通信方式，定义一个共同的话题，publish（可以有多个）-subscribe（可以有多个）  

**Topic的内容数据类型 Message**

Message 定义在/pkg/msg/message.msg文件中  
```cpp
bool int8 int16 int32 int64 uint
float32 float64 string
time duration header
可变长度数组array[] 固定长度数组array[C]
```
### Client Library C++
#### ros::init()
- void ros::init(); //解析ROS参数 为node命名

#### ros::NodeHandle Class类
常见成员函数
```cpp
//创建话题的publisher
ros::Publisher advertise(const string &topic,uint32_t queue_size)
//创建话题的subscriber
ros::Subscriber subscribe(const string &topic,uint32_t queue_size, void(*)(M));
//创建服务的server
ros::ServiceServer advertiseService(const string &service,bool (*srv_func)(Mreq &,Mres &))
//创建服务的client
ros::ServiceClient serviceClient(const string &service,bool persistent = false)
//查询某个参数的值
bool getParam(const string &key,void &val);
//给参数赋值
bool setParam(const string &key,void val);
```

### 开始编写C++Topic
1. 创建一个pkg (test_topic_roscpp)
```bash
catkin_create_pkg test_topic_roscpp roscpp std_msgs message_generation
```
2. mkdir msg && cd msg创建一个msg(mymsg.msg)
```c++
int32 id
float32 value
string str
``` 

接下来修改CMakeList文件，把mymsg.msg添加进去 
 ```cmake
 49 ## Generate messages in the 'msg' folder
 50  add_message_files(                                                        
 51    FILES
 52    mymsg.msg
 53 #   Message2.msg
 54  )

 70 ## Generate added messages and services with any dependencies listed here
 71  generate_messages(                                                        
 72    DEPENDENCIES
 73    std_msgs
 74  )
 ```

```xml
去掉下面2行的注释
 <!--   <build_depend>message_generation</build_depend> --> 
 <!--   <exec_depend>message_runtime</exec_depend> -->  
```
最后：  
  `catkin_make`   编译一下 生成.h文件


3. 编写recv代码
- 到src目录下 创建 `recv.cpp`  
```cpp
#include <ros/ros.h>
#include <test_topic_roscpp/mymsg.h>

void callbackfun(const test_topic_roscpp::mymsg::ConstPtr &msg)
{
	ROS_INFO("Recv id:%d,value:%f,str:%s",msg->id,msg->value,msg->str.c_str());
}

int main(int argc,char **argv)
{
	ros::init(argc,argv,"recv");

	ros::NodeHandle handle;

	//subscribe第一个参数：订阅的话题
	//第二个参数 
	ros::Subscriber receiver = handle.subscribe("tangyuan",1,callbackfun);

	//进入等待 不返回 类似于while(1);
	ros::spin();

	return 0;
}
```


4. 编写send代码
- 到src目录下 创建 `send.cpp`  
```cpp
#include <ros/ros.h>
#include <test_topic_roscpp/mymsg.h>

int main(int argc, char** argv)
{
	ros::init(argc,argv,"send");
	
	ros::NodeHandle handle;
	
	ros::Publisher sender = handle.advertise<test_topic_roscpp::mymsg>("tangyuan",1);

	ros::Rate loop_rate(1.0);//频率为1Hz

	test_topic_roscpp::mymsg msg;
	msg.id=1;
	msg.value=1.0;
	msg.str="tangyuan";
	while(ros::ok())
	{
		msg.id++;
		msg.value *=1.66;
		sender.publish(msg);//发送
		ROS_INFO("send msg: cnt = %d , value = %f",msg.id,msg.value);
		//休眠
		loop_rate.sleep();
	}
	return 0;
}
```

5. 修改CMakelist
Ctrl+G Ctrl+A
添加下面内容
```cmake
add_executable(send src/send.cpp)
target_link_libraries(send ${catkin_LIBRARIES})
add_dependencies(send beginner_tutorials_generate_messages_cpp)

add_executable(recv src/recv.cpp)
target_link_libraries(recv ${catkin_LIBRARIES})
add_dependencies(recv beginner_tutorials_generate_messages_cpp)
```
然后 `catkin_make`  

6. 运行
source setup.sh文件
```bash
roscore
rosrun test_topic_roscpp recv
rosrun test_topic_roscpp send
```
> 至此，ROSCPP的Topic通信完成


## 8.ROS ServiceDemo（C++）
1. 创建一个pkg (test_service_roscpp)
```bash
catkin_create_pkg test_service_roscpp roscpp std_msgs message_generation
```
2. mkdir srv && cd srv(vi mysrv.srv)
```c++
string name
int32 age
---
string feedback

``` 

接下来修改CMakeList文件，把mysrv.srv添加进去 
 ```cmake
 56 ## Generate services in the 'srv' folder
 57  add_service_files(
 58    FILES
 59    mysrv.srv                                                                
 60 #   Service2.srv
 61  )

70 ## Generate added messages and services with any dependencies listed here
 71  generate_messages(                                                        
 72    DEPENDENCIES
 73    std_msgs
 74  )
 ```

```xml
去掉下面2行的注释
 <!--   <build_depend>message_generation</build_depend> --> 
 <!--   <exec_depend>message_runtime</exec_depend> -->  
```
最后：  
  `catkin_make`   编译一下 生成.h文件


### Server
```cpp
#include <ros/ros.h>
#include <test_service_roscpp/mysrv.h>

bool handle_function(test_service_roscpp::mysrv::Request &req, test_service_roscpp::mysrv::Response &res)
{
 ROS_INFO("Request from %s with age %d", req.name.c_str(), req.age);
 //处理请求,结果写入response
 res.feedback = "Hi " + req.name + ". I'm server!";
 //返回true,正确处理了请求
 return true;
}

int main(int argc, char** argv)
{
 ros::init(argc, argv, "server");  //解析参数,命名节点server
 ros::NodeHandle handle;        //创建句柄,实例化node
 ros::ServiceServer service = handle.advertiseService("tangyuaner", handle_function);  
 //写明服务的处理函数
 ros::spin();
 return 0;
}
```

### Client
```cpp
# include "ros/ros.h"
# include "test_service_roscpp/mysrv.h"
int main(int argc, char **argv)
{
    ros::init(argc, argv, "client");// 初始化,节点命名为"client"
    ros::NodeHandle handle;
    ros::ServiceClient client = handle.serviceClient<test_service_roscpp::mysrv>("tangyuaner");
    // 定义service客户端,service名字为"mysrv",service类型为test_service_roscpp
    // 实例化srv,设置其request消息的内容,这里request包含两个变量,name和age,见Greeting.srv
    test_service_roscpp::mysrv srv;
    srv.request.name = "tangyuan";
    srv.request.age = 20;
    if (client.call(srv))
    {
        // 注意我们的response部分中的内容只包含一个变量response,另,注意将其转变成字符串
        ROS_INFO("Response from server: %s", srv.response.feedback.c_str());
    }
    else
    {
        ROS_ERROR("Failed to call service Service_demo");
        return 1;
    }
    return 0;
}
```

### 修改CMakelist
Ctrl+G Ctrl+A
添加下面内容
```cmake
add_executable(server src/server.cpp)
target_link_libraries(server ${catkin_LIBRARIES})

add_executable(client src/client.cpp)
target_link_libraries(client ${catkin_LIBRARIES})
```
然后 `catkin_make`  

### 运行
source setup.sh文件
```bash
roscore
rosrun test_service_roscpp server
rosrun test_service_roscpp client
```


## 9.ROS TopicDemo（Python）


### rospy
- Node  
```python
无返回 init_node(name) #注册和初始化node
MasterProxy get_master()#获取master的句柄
bool is_shutdown() #是否关闭
on_shutdown(fn) #在node关闭时调用
str get_node_uri()#返回节点uri
str get_name()#返回节点全名
str get_namespace()#返回本节点名字空间
```
- Topic  
```py
[[str,str]] get published_topics()#返回正在被发布的所有topic的名称和类型
Message wait_for_message(topic,topic_type,time_out=None)#只等待一个！等待指定topic的一个message
spin() #阻塞

publisher类:
__init__(self,name,data_class,queue_size=None)
publish(self,msg)#成员函数 发布消息
unregister(self)停止发布

Subscriber类：
__init__(self,name,data_class,call_back=None,queue_size=None)#构造函数
unregister(self)#停止订阅
```
- Service  API
```py
函数：
wait_for_service(service,timeout=None)#阻塞至服务可用
#没有返回值

service类：#server
__init__(self,name,service_class,handler)
"""
def handler(req)#传入请求
	...
	...
	return res#返回结果
"""
shutdown(self)#关闭服务

ServiceProxy类：#client
__init(self,name,service_class)
Response call(self,*args,**kwds)#client.call(req)
Response __call__(self,*args,**kwds)#resp=client(req)
close()
```

- Param  都是函数
```py
XmlRpcLegalValue get_param(param_name,default=_unspecified) #获取参数的值
[str] get_param_names() #获取参数的名称
set_param(param_name,param_value) 设#置参数的值
delete_param(param_name) #删除参数
bool has_param(param_name) #参数是否存在于参数服务器上
str search_param() #搜索参数
```
- Time  时刻  Duration 一段时间
```py
init(self,	secs=0,	nsecs=0) #构造函数
Time now() #静态方法	返回当前时刻的Time对象
rospy.Time.now()
Time get_rostime()#=上面的
float get_time #返回当前时间 float 单位秒
sleep(duration)#挂起
```

Rate类
rate = rospy.Rate(5)
rate.sleep()

### Topic实例
1. package(test_topic_rospy)
```bash
catkin_create_pkg test_topic_rospy rospy std_msgs message_generation
```

2. msg
mkdir msg && cd msg创建一个msg(mymsg.msg)
```c++
int32 id
float32 value
string str
``` 

接下来修改CMakeList文件，把mymsg.msg添加进去 
 ```cmake
 49 ## Generate messages in the 'msg' folder
 50  add_message_files(                                                        
 51    FILES
 52    mymsg.msg
 53 #   Message2.msg
 54  )

 70 ## Generate added messages and services with any dependencies listed here
 71  generate_messages(                                                        
 72    DEPENDENCIES
 73    std_msgs
 74  )
 ```

```xml
去掉下面2行的注释
 <!--   <build_depend>message_generation</build_depend> --> 
 <!--   <exec_depend>message_runtime</exec_depend> -->  
```  

3. pysend.py   

mkdir scripts && cd scripts

```python
#!/usr/bin/env python
#coding=utf-8
import rospy
#倒入自定义的数据类型
from test_topic_rospy.msg import mymsg

def talker():
    #Publisher 函数第一个参数是话题名称，第二个参数 数据类型，现在就是我们定义的msg 最后一个是缓冲区的大小
    #queue_size: None（不建议）  #这将设置为阻塞式同步收发模式！
    #queue_size: 0（不建议）#这将设置为无限缓冲区模式，很危险！
    #queue_size: 10 or more  #一般情况下，设为10 。queue_size太大了会导致数据延迟不同步。
    pub = rospy.Publisher('tangyuan', mymsg , queue_size=10)
    rospy.init_node('pysend', anonymous=True)
    #更新频率是1hz
    rate = rospy.Rate(1) 
    id=0
    value=1.0
    str='tangyuan'
    while not rospy.is_shutdown():
        #计算距离
        rospy.loginfo('send msg:id=%d ,value=%f',id,value)
        pub.publish(mymsg(id,value,str))
        value*=1.02
        id=id+1
        rate.sleep()

if __name__ == '__main__':
    talker()
 
```

4. pyrecv.py  

```python
#!/usr/bin/env python
#coding=utf-8
import rospy

#导入mgs到pkg中
from test_topic_rospy.msg import mymsg

#回调函数输入的应该是msg
def callback(mymsg):
    rospy.loginfo('receive from %s: id=%d, value=%f',mymsg.str,mymsg.id,mymsg.value)

def listener():
    rospy.init_node('pyrecv', anonymous=True)
    #Subscriber函数第一个参数是topic的名称，第二个参数是接受的数据类型 第三个参数是回调函数的名称
    rospy.Subscriber('tangyuan', mymsg, callback)
    rospy.spin()

if __name__ == '__main__':
    listener()

```

5. Cmakelist&package.xml  

### 运行方法

> python文件不需要编译 但是必须加执行权限 否则提示无法执行  
chmod +x pysend.py pyrecv.py

启动发布者   
```
$ roscore
```
```sh
$ rosrun test_topic_rospy pysend.py   #Python
``` 

启动接收者

```sh
$ rosrun test_topic_rospy pyrecv.py   #Python
``` 

## 10.ROS ServiceDemo（Python）


1. package(test_service_rospy)
```bash
catkin_create_pkg test_service_rospy rospy std_msgs message_generation
```

2. srv
mkdir srv && cd srv 创建一个srv(mysrv.srv)
```c++
string name
int32 age
---
string feedback

``` 

接下来修改CMakeList文件，把mysrv.srv添加进去 
 ```cmake
 56 ## Generate services in the 'srv' folder
 57  add_service_files(
 58    FILES
 59    mysrv.srv                                                                
 60 #   Service2.srv
 61  )

70 ## Generate added messages and services with any dependencies listed here
 71  generate_messages(                                                        
 72    DEPENDENCIES
 73    std_msgs
 74  )
 ```

```xml
去掉下面2行的注释
 <!--   <build_depend>message_generation</build_depend> --> 
 <!--   <exec_depend>message_runtime</exec_depend> -->  
```

3. pyserver.py 

```python
#!/usr/bin/env python
# coding:utf-8

# service模块的加载方式，from 包名.srv import *
import rospy
from test_service_rospy.srv import *

def server_srv():
    # 初始化节点，命名为 "pyserver"
    rospy.init_node("pyserver")
    # 定义service的server端，service名称为"tangyuaner"， service类型为mysrv
    # 收到的request请求信息将作为参数传递给handle_function进行处理
    s = rospy.Service("tangyuaner", mysrv, handle_function)
    rospy.loginfo("Ready to handle the request:")
    # 阻塞程序结束
    rospy.spin()

# Define the handle function to handle the request inputs
def handle_function(req):
    # 注意我们是如何调用request请求内容的，与前面client端相似，都是将其认为是一个对象的属性，通过对象调用属性，在我们定义
    # 的test_service_rospy类型的service中，request部分的内容包含两个变量，一个是字符串类型的name，另外一个是整数类型的age
    rospy.loginfo( 'Request from %s with age %d', req.name, req.age)
    # 返回一个Service_demoResponse实例化对象，其实就是返回一个response的对象，其包含的内容为我们再test_service_rospy.srv中定义的
    # response部分的内容，我们定义了一个string类型的变量，因此，此处实例化时传入字符串即可
    return mysrvResponse("Hi %s. I' server!"%req.name)

# 如果单独运行此文件，则将上面定义的server_srv作为主函数运行
if __name__=="__main__":
    server_srv()
```

4. pyclient.py  

```python
#!/usr/bin/env python
# coding:utf-8
import rospy
from test_service_rospy.srv import *

def client_srv():
    rospy.init_node('pyclient')
    # 等待有可用的服务 "tangyuaner"
    rospy.wait_for_service("tangyuaner")
    try:
        # 定义service客户端，service名称为“tangyuaner”，service类型为mysrv
        client = rospy.ServiceProxy("tangyuaner",mysrv)

        # 向server端发送请求
        # 注意，此处发送的request内容与service文件中定义的request部分的属性是一致的
        resp = client.call("tangyuan",20)

        # 打印处理结果，注意调用response的方法，类似于从resp对象中调取response属性
        rospy.loginfo("Message From server:%s"%resp.feedback)
    except rospy.ServiceException, e:
        rospy.logwarn("Service call failed: %s"%e)

# 如果单独运行此文件，则将上面函数client_srv()作为主函数运行
if __name__=="__main__":
    client_srv()
```

5. Cmakelist&package.xml  

### 运行方法

roscore   
chmod +x py*

启动发布者

```sh
$ rosrun test_service_rospy pyserver.py   #Python
``` 

启动接收者

```sh
$ rosrun test_service_rospy pyclient.py   #Python
``` 




## 附录
#### xbot测试
```bash
roslaunch robot_sim_demo  robot_spawn.launch
rosrun robot_sim_demo robot_keyboard_teleop.py
rosrun image_view image_view image:=/camera/rgb/image_raw
```

