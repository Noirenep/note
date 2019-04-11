# linux C语言编程


## 7.进程间通信
### 无名管道
>头文件:#include <unistd.h>  
函数原型:int pipe(int pipe[2])  
函数作用:创建无名管道  
参数:参数是长度为2的int型数组,pipe[0]是读端的描述符,pipe[1]是写端的文件描述符  
返回值:成功0 , 失败-1  


子程序写 父程序读的一个例子
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

> TODO

