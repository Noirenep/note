# TCP/IP 网络编程

## 网络编程和套接字

### TCPserver流程
1. socket()
2. bind()
3. listen()
4. accept()

### hello_server.c
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void err_handling(char *message);

int main(int argc,char *argv[])
{
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char message[]="Hello world";

    if(argc!= 2)
    {
        printf("Usage : %s <port>\n ",argv[0]);
        exit(0);
    }
    serv_sock = socket(PF_INET,SOCK_STREAM,0);
    if(serv_sock == -1)
        err_handling("socket() err");

    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    serv_addr.sin_port=htons(atoi(argv[1]));

    if(bind(serv_sock,(struct sockaddr*) &serv_addr,sizeof (serv_addr))==-1)
        err_handling("bind() err");

    if(listen(serv_sock,5) == -1)
        err_handling("listen() err");

    clnt_addr_size=sizeof (clnt_addr);
    clnt_sock= accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);
    if(clnt_sock==-1)
        err_handling("accept() err");

    write(clnt_sock,message,sizeof (message));
    close(clnt_sock);
    close(serv_sock);

    return 0;
}

void err_handling(char *message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);
}

```  
### TCPserver流程
1. socket()
2. connect()

### hello client.c
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void err_handling(char *message);

int main(int argc,char *argv[])
{
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int strlen;

    if(argc!=3)
    {
        printf("Usage : %s <ip> <port>\n",argv[0]);
        exit(1);
    }

    sock = socket(PF_INET,SOCK_STREAM,0);
    if(sock == -1)
    {
        err_handling("socket() error");
    }

    memset(&serv_addr,0,sizeof (serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    serv_addr.sin_port=htons(atoi(argv[2]));

    if(connect(sock,(struct sockaddr*)&serv_addr,sizeof (serv_addr))==-1)
        err_handling("connect() err");

    strlen = read(sock,message,sizeof(message)-1);
    if(strlen==-1)
        err_handling("read() err");
    printf("Message froom server:%s \n",message);
    close(sock);

    return 0;
}

void err_handling(char *message)
{
    fputs(message,stderr);
    fputc('\n',stderr);
    exit(1);

}

```

> Windows实现
### hello_server_win.c
```c
//TODO
```

### hello_client_win.c
```c
//TODO
```

## 套接字类型和协议设置

### 协议族 Protocol Family
PF_INET IPV4互联网协议族  
PF_INET6 IPV6互联网协议族  
PF_LOCAL 本地通信UNIX协议族  

```c
//TCP
int tcp_socket = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);

//UDP
int udp_socket = socket(PF_INET,SOCK_DGRAM.IPPROTO_UDP)
```

## 地址族和数据序列
### 表示ipv4地址的结构体
```c
struct sockaddr_in
{
    sa_family_t     sin_family; //地址族
    uint16_t        sin_port;   //16位TCP/UDP端口号 
    struct in_addr  sin_addr;   //32位ip地址
    char            sin_zero[8];//不使用
};

struct in_addr
{
    In_addr_t   s_addr; //32位ipv4地址
};
```
### 网络字节序与地址变换
> 约定：统一大端序 
- 大端(Big Endian)      高位字节存放到地位地址（像字符串）
- 小端(Little Endian)   高位字节存放到高位地址

0x12345678  
大端：12 34 56 78  
小端：78 56 34 12  

### 字节序转换
```c
unsigned short htons(unsigned short);
unsigned short ntohs(unsigned short);
unsigned long htonl(unsigned long);
unsigned long ntohl(unsigned long);
```
> h代表主机host  n表示网络network s指short l指long  

(Intel AMD常用小端序  ARM常用大端序)

### ip地址的转换
```c
#include <arpa/inet.h>

in_addr_t inet_addr(const char* string);
//成功时返回32位大端序整数值ip 失败返回INADDR_NONE
int inet_aton(const char *string struct in_addr *addr);
// string :含有ip的地址字符串
//adddr 将保存转换结果的in_addr结构体的地址
//成功返回1 失败返回0  更常用

char * inet_ntoa(struct in_addr adr)
//成功返回字符串地址  失败返回-1
```

### 网络地址的初始化
```c
struct sockaddr_in addr;
char * serv_ip = "211.217.168.13";//ip
char * serv_port = "9090";//端口字符串
memset(&addr,0,sizeof (serv_addr));//所有成员初始化为0
addr.sin_family=AF_INET;//指定地址族
addr.sin_addr.s_addr=inet_addr(serv_ip);//基于字符串的IP址初始化
addr.sin_port=htons(atoi(serv_port));//基于字符串的端口号始化
```

### INADDR_ANY
```c
struct sockaddr_in addr;
char * serv_port = "9090";
memset(&addr,0,sizeof (serv_addr));
addr.sin_family=AF_INET;
addr.sin_addr.s_addr=htonl(INADDR_ANY);//☆☆☆☆
addr.sin_port=htons(atoi(serv_port));
```
>服务器常用

## TCP服务器与客户端

//TODO

