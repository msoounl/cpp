#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "global.h"

class client
{
private:
    int server_port;  // 服务器端口
    string server_ip; // 服务器 ip
    int sock;         // 与服务器建立连接的套接字描述符
public:
    client(int port, string ip);
    ~client();
    void run();                    // 启动客户端服务
    static void SendMsg(int conn); // 发送线程
    static void RecvMsg(int conn); // 接收线程
};

#endif
