# linux C语言编程


## 7.进程间通信
### 无名管道
>头文件:#include <unistd.h>  
函数原型:int pipe(int pipe[2])  
函数作用:创建无名管道  
参数:参数是长度为2的int型数组,pipe[0]是读端的描述符,pipe[1]是写端的文件描述符  
返回值:成功0 , 失败-1  


>子程序写 父程序读的一个例子  

编写一段程序，使其用管道来实现父子进程之间的进程通信。子进程向父进程发送自己的进程标识符，以及字符串“is sending a message to parent ! ”。父进程则通过管道读出子进程发来的消息，将消息显示在屏幕上，然后终止。
```c
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <wait.h>
#include <string.h>

char sendmsg[100]={0};
char recvbuf[100]={0};

int main()
{
    int mypipe[2], pid;
    int status;
    if (pipe(mypipe) < 0)
    {
        perror("pipe failed");
        exit(0);
    }
    if ((pid = fork())<0)
    {
        perror("fork failed");
        exit(0);
    }

    if(pid == 0)
    {
        //子进程部分
        close(mypipe[0]);
        sprintf(sendmsg, "pid:%d %s", getpid(), "is sending a message to parent !");
        write(mypipe[1],sendmsg,sizeof(sendmsg));
        exit(0);
    }
    if (pid >0)
    {
        //父进程部分
        wait(&status);//等待子进程退出
        read(mypipe[0],recvbuf, sizeof(sendmsg));
        printf("%s\n",recvbuf);
    }
    return 0;
}
```

### 共享内存
#### System V 共享内存 主要有以下几个API
> shmget()、获取共享内存区域的ID  
shmat()、把共享内存区域映射到调用进程的地址空间中  
shmdt()、撤销映射  
shmctl() 对共享内存区域的控制操作  

- 所需头文件
```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
```

- shmget用法

- shmat用法

- shmdt用法

- shmctl用法

#### 共享内存实例
编写一段程序，使其用共享存储区来实现父子进程之间的进程通信。父进程创建一个长度为512 字节的共享内存空间，显示写入该共享内存的数据；子进程将共享内存也附加到自己的地址空间，并向共享内存中写入数据。
```c

```






