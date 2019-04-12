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
```c
int //成功返回共享内存段标识别符　失败返回-1
shmget(
    key_t key,//共享内存键值，可以通过它访问同一个内存，IPC_PRIVATE创建当前进程私有的共享内存
    int size,//共享内存的大小
    int shmflg///同open()的权限位,也可以用8进制标示
)
```

- shmat用法
```c
char* //成功返回映射的短地址 失败返回-1
shmat(
    int shmid, //标识符
    const void *shmaddr,//将共享内存映射到指定地址(若为0表示系统自动分配)
    int shmflg//默认0:共享内存可读写,SHM_RDONLY:只读
)
```

- shmdt用法
```c
int //成功0 出错-1
shmdt(
    const void* shmaddr//被映射的共享内存段地址
)
```

- shmctl用法
```c
int //成功0 出错-1
shmctl(
    int shmid,//共享内存标识符
    int cmd,//共享内存的属性执行的相关指令
        //IPC_STAT 得到共享内存的状态,把shmid_ds复制到buf中
        //IPC_SET 改变内存状态 把buf中shmid_ds中uid gid mode复制到共享内存的shmid_ds结构中
        //IPC_RMID 删除该共享内存
    struct shmid_ds *buf //共享内存管理结构体
)
```
　
#### 共享内存实例
编写一段程序，使其用共享存储区来实现父子进程之间的进程通信。父进程创建一个长度为512 字节的共享内存空间，显示写入该共享内存的数据；子进程将共享内存也附加到自己的地址空间，并向共享内存中写入数据。
```c
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <wait.h>

int main()
{
    int shmid;//共享内存段标识符

    char *shmaddr;
    char buf[512]={0};
    int shmstatus;
    int pid;
    int status;

    shmid =shmget(IPC_PRIVATE,512,IPC_CREAT|0600);
    if(shmid <0)
    {
        perror("shmget error");
        return -1;
    }

    pid = fork();

    if(pid == 0)
    {
        //子进程
        shmaddr = (char *) shmat(shmid, NULL, 0);
        if((int)shmaddr == -1)
        {
            perror("shmat error");
            return -2;
        }
        strcpy(shmaddr,"Hello world \n");
        shmdt(shmaddr);
        return 0;
    }
    if (pid > 0)
    {
        wait(&status);
        //父进程
        shmaddr = (char *) shmat(shmid, NULL, 0);
        if((int)shmaddr == -1)
        {
            perror("shmat error");
            return -2;
        }
        strcpy(buf,shmaddr);
        printf("got from shared memory:%s",buf);
        shmdt(shmaddr);
        shmctl(shmid, IPC_RMID, NULL);

    }

    return 0;
}
```






