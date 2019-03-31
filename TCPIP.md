# TCP/IP 网络编程

## 网络编程和套接字
### TCP/IP协议族
- 应用层 HTTP FTP DNS NFS
- 传输层 TCP UDP
- 网络层 IP ARP RARP ICMP
- 链路层 Ethernet

### UDP
>格式：8B UDP报头，0~65527B 数据  
头部格式：源端口，目标端口，长度，校验和（各2B）
### TCP
>格式：头部（20~60B），数据（0-35535B）
>头部格式：源端口，目标端口，序号，确认号，等等。。。。

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
## Windows下的项目配置
- 导入头文件 winsock2.h
- 链接ws2_32.lib库

> 属性-> 链接器 -> 输入 ->附加依赖项 -> ws2_32.lib

### hello_server_win.c
```c
//TODO
```

### hello_client_win.c
```c
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define BUF_SIZE 1024
void ErrorHandling(const char *message);

int main(int argc, char *argv[])
{
	WSADATA wsaData;
	SOCKET hSocket;
	char message[BUF_SIZE];
	int strLen;
	SOCKADDR_IN servAdr;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
		ErrorHandling("socket() error");

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = inet_addr("118.24.137.128");
	servAdr.sin_port = htons(atoi("16666"));

	if (connect(hSocket, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandling("connect() error!");
	else
		puts("Connected...........");

	while (1)
	{
		fputs("Input message(Q to quit): ", stdout);
		fgets(message, BUF_SIZE, stdin);

		if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
			break;

		send(hSocket, message, strlen(message), 0);
		strLen = recv(hSocket, message, BUF_SIZE - 1, 0);
		message[strLen] = 0;
		printf("Message from server: %s", message);
	}

	closesocket(hSocket);
	WSACleanup();
	return 0;
}

void ErrorHandling(const char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
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
char * serv_ip = "118.24.137.128";//ip
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

TCP服务端在accept后返回客户端的socket  
客户端在connect后分配随机的端口  

> TODO echo的例子

## UDP的服务端与客户端
>UDP的客户端和服务器均只需要一个套接字   

基于UDP的数据IO函数
```c
#include <sys/socket.h>

ssize_t sendto(
    int sock, //用于传输数据的UDP套接字描述符
    void *buff, //待传输数据的地址
    size_t nbytes,//待传输数据的长度 字节为单位
    int flags,//可选参数 没有传递0
    struct sockaddr *to,//目标地址 sockaddr结构体 的地址
    socklen_t addrlen//结构体变量长度
);
//成功返回传输的字节数 失败返回-1

ssize_t recvfrom(
    int socket, //用于接收数据的UDP套接字描述符
    void *buff, //保存接收数据缓冲的地址
    size_t nbytes, //可接收的最大字节数
    int flags,  //可选参数 没有传入0
    struct sockaddr *from, //存有发送端地址的的sockaddr的地址
    socklen_t *addrlen // 保存参数from结构体变量长度的地址
);
//成功返回接收的字节数 失败返回-1
```
## UDP echo
### server
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>

#define BUF_SIZE 30

void error_handling(char *message);

int main(int argc, char *argv[])
{
    int serv_sock;
    char message[BUF_SIZE];
    int str_len;
    socklen_t clnt_adr_sz;

    struct sockaddr_in serv_adr, clnt_adr;
    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (serv_sock == -1)
    {
        error_handling("UDP socket creating error");
    }

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) == -1)
    {
        error_handling("bind err");
    }

    while(1)
    {
        clnt_adr_sz = sizeof(clnt_adr);
        str_len=recvfrom(serv_sock,message,BUF_SIZE,0,(struct sockaddr*)&clnt_adr,&clnt_adr_sz);
        message[str_len]=0;
        printf("Message from client: %s",message);
        sendto(serv_sock,message,str_len,0,(struct sockaddr*)&clnt_adr,clnt_adr_sz);

    }
    close(serv_sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
```

### client
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <string.h>

#define BUF_SIZE 30

void error_handling(char *message);

int main(int argc, char *argv[])
{
    int sock;
    char message[BUF_SIZE];
    int str_len;
    socklen_t adr_sz;

    struct sockaddr_in serv_adr, from_adr;
    if (argc != 3)
    {
        printf("Usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock == -1)
    {
        error_handling("socket() error");
    }

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));


    while(1)
    {
        fputs("Insert message(q to quit):",stdout);
        fgets(message, sizeof(message), stdin);
        if (!strcmp(message, "q\n"))
        {
            break;
        }

        sendto(sock,message,strlen(message),0,(struct sockaddr*)&serv_adr, sizeof(serv_adr));
        adr_sz = sizeof(from_adr);
        str_len = recvfrom(sock, message, BUF_SIZE, 0, (struct sockaddr*)&from_adr, &adr_sz);
        message[str_len]=0;
        printf("Message from server %s",message);
    }
    close(sock);

    return 0;
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
```


### UDP数据报存在边界






## Python 取本机MAC地址

```py
import uuid
node = uuid.uuid1()
print('node=',node)
hex=node.hex
mac_addr=hex[-12:]
print('mac_addr=',mac_addr)
```
