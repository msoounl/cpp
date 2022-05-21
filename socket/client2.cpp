/*
使用 cpp socket 完成一个简单的 demo，要求完成两个程序（服务器和客户端），指定端口启动服务器，使用客户端连接服务器并发送消息，服务器收到每一条消息都回复 “已收到，请发送下一条信息”，直到客户端发送 bye 断开连接。
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("用法：./client IP地址 端口号\n例子：./client 127.0.0.1 6666\n\n");
        return -1;
    }

    // 1 创建客户端的 socket
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        return -1;
    }

    // 2 向服务器发起连接请求
    struct hostent *h;
    if ((h = gethostbyname(argv[1])) == 0) // 指定服务端的 ip 地址。
    {
        printf("gethostbyname 运行失败。\n");
        close(sockfd);
        return -1;
    }
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(argv[2])); // 指定服务端的通信端口
    memcpy(&servaddr.sin_addr, h->h_addr, h->h_length);
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) // 向服务端发起连接清求
    {
        perror("connect");
        close(sockfd);
        return -1;
    }

    // 3 与服务端通信，发送一个报文后等待回复，然后再发下一个报文
    char buffer[1024];

    while (1)
    {
        int iret;
        memset(buffer, 0, sizeof(buffer));
        scanf("%s", buffer);
        if ((iret = send(sockfd, buffer, strlen(buffer), 0)) <= 0) // 向服务端发送请求报文
        {
            perror("send");
            break;
        }
        printf("发送：%s\n", buffer);
        if (strcmp(buffer, "bye") == 0)
        {
            break;
        }

        memset(buffer, 0, sizeof(buffer));
        if ((iret = recv(sockfd, buffer, sizeof(buffer), 0)) <= 0) // 接收服务端的回应报文
        {
            printf("iret = %d\n", iret);
            break;
        }
        printf("接收：%s\n", buffer);
    }

    // 4 关闭 socket，释放资源
    close(sockfd);
}