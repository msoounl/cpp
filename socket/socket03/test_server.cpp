#include "server.h"

int main()
{
    server serv(8023, "127.0.0.1"); // 创建实例, 传入 ip 和端口号作为构造函数参数
    serv.run();                     // 启动服务

    return 0;
}
