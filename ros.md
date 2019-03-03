# ROS笔记
> 编辑时间：2019年03月02日22:58:07

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
        package.xml #属性信息 包名 作者 依赖项（编译和运行的依赖项build_depend run_depend） 版本
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
1. 创建一个pkg (topic_roscpp_test)
```bash
catkin_create_pkg topic_roscpp_test roscpp std_msgs message_generation
```
2. mkdir msg && cd msg创建一个msg(ifs.msg)
				int32 cnt
				float32 value
				string status
3. 编写recv代码
		首先 ros::init()
		接下来 拿到handle

4. 编写send代码

5. 修改CMakelist
```cmake
add_executable(send src/send.cpp)
target_link_libraries(send ${catkin_LIBRARIES})
add_dependencies(send beginner_tutorials_generate_messages_cpp)

add_executable(recv src/recv.cpp)
target_link_libraries(recv ${catkin_LIBRARIES})
add_dependencies(recv beginner_tutorials_generate_messages_cpp)
```


## 8.ROS ServiceDemo（C++）

> 待编辑

## 9.ROS TopicDemo（Python）


> 待编辑


## 10.ROS ServiceDemo（Python）


> 待编辑




## 附录
#### xbot测试
```bash
roslaunch robot_sim_demo  robot_spawn.launch
rosrun robot_sim_demo robot_keyboard_teleop.py
rosrun image_view image_view image:=/camera/rgb/image_raw
```

