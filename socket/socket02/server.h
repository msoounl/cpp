#ifndef __SERVER_H__
#define __SERVER_H__

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
// #include <sys/types.h>
// #include <fcntl.h>
// #include <sys/shm.h>

using namespace std;

class server
{
private:
    string server_ip;     // 服务器 ip
    int server_port;      // 服务器端口号
    int server_sockfd;    // 设为 listen 状态的套接字描述符
    vector<int> sock_arr; // 保存所有套接字描述符
public:
    server(string ip, int port);   // 构造函数
    ~server();                     // 析构函数
    void run();                    // 服务器开始服务
    static void RecvMsg(int conn); // 子线程工作的静态函数
};

#endif
