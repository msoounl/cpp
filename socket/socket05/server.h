#ifndef __SERVER_H__
#define __SERVER_H__

#include "global.h"

class server
{
private:
    int server_port;
    int server_sockfd;
    string server_ip;
    static vector<bool> sock_arr;                    // 改为了静态成员变量, 且类型变为 vector<bool>
    static unordered_map<string, int> name_sock_map; // 用户名 sockid
    static mutex mtx;                                // 互斥锁 锁住需要修改 name_sock_map 的临界区

public:
    server(int port, string ip);
    ~server();
    void run();
    static void RecvMsg(int conn);
    static void HandleRequest(int conn, string str, tuple<bool, string, string, int> &info);
};

#endif
