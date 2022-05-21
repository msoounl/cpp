/*
使用 cpp socket 完成一个简单的 demo，要求完成两个程序（服务器和客户端），指定端口启动服务器，使用客户端连接服务器并发送两条消息，服务器收到每一条消息都回复 ok。
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("用法：./server 端口号\n例子：./server 6666\n\n");
        return -1;
    }

    // 1 创建服务端的 socket
    int listenfd;
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        return -1;
    }

    // 设置 SO_REUSEADDR 选项
    int opt = 1;
    unsigned int len = sizeof(opt);
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, len);

    // 2 把服务端用于通信的地址和端口绑定到 socket 上
    struct sockaddr_in servaddr; // 用于保存服务端地址信息的结构体
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;                // 协议族，在 socket 编程中只能是 AF_INET
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // 任意 ip 地址
    //servaddr.sin_addr.s_addr = inet_addr("192.168.1.100"); // 指定 ip 地址
    servaddr.sin_port = htons(atoi(argv[1])); // 指定通信端口
    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
    {
        perror("bind");
        close(listenfd);
        return -1;
    }

    // 3 把 socket 设置为监听模式
    if (listen(listenfd, 5) != 0)
    {
        perror("listen");
        close(listenfd);
        return -1;
    }

    // 4 接受客户端的连接
    int clientfd;                             // 客户端的 socket
    int socklen = sizeof(struct sockaddr_in); // struct sockaddr_in 的大小
    struct sockaddr_in clientaddr;            // 客户端的地址信息
    clientfd = accept(listenfd, (struct sockaddr *)&clientaddr, (socklen_t *)&socklen);
    printf("客户端（%s）已连接。\n", inet_ntoa(clientaddr.sin_addr));

    // 5 与客户端通信，接收客户端发过来的报文后，回复 ok
    char buffer[1024];
    while (1)
    {
        int iret;
        memset(buffer, 0, sizeof(buffer));
        if ((iret = recv(clientfd, buffer, sizeof(buffer), 0)) <= 0) // 接收客户端的请求报文
        {
            printf("iret = %d\n", iret);
            break;
        }
        printf("接收：%s\n", buffer);

        strcpy(buffer, "ok");
        if ((iret = send(clientfd, buffer, strlen(buffer), 0)) <= 0) // 向客户端发送响应结果
        {
            perror("send");
            break;
        }
        printf("发送：%s\n", buffer);
    }

    // 6 关闭 socket，释放资源
    close(listenfd);
    close(clientfd);

    return 0;
}