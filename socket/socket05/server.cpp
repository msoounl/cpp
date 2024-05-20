#include "server.h"

// 将 10000 个位置都设为 false, sock_arr[i] = false 表示套接字描述符 i 未打开(因此不能关闭)
vector<bool> server::sock_arr(10000, false);
unordered_map<string, int> server::name_sock_map;
mutex server::mtx;

// 构造函数
server::server(int port, string ip) : server_port(port), server_ip(ip) {}

// 析构函数
server::~server()
{
    for (int i = 0; i < sock_arr.size(); i++)
    {
        if (sock_arr[i])
            close(i);
    }

    close(server_sockfd);
}

// 服务器开始服务
void server::run()
{
    // 定义 sockfd
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // 定义 sockaddr_in
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;                           // TCP/IP协议族
    server_sockaddr.sin_port = htons(server_port);                  // 端口号
    server_sockaddr.sin_addr.s_addr = inet_addr(server_ip.c_str()); // ip 地址, 127.0.0.1 是回环地址, 相当于本机 ip

    // bind, 成功返回 0, 出错返回 -1
    if (bind(server_sockfd, (struct sockaddr *)&server_sockaddr, sizeof(server_sockaddr)) == -1)
    {
        perror("bind"); // 输出错误原因
        exit(1);        // 结束程序
    }

    // listen, 成功返回 0, 出错返回 -1
    if (listen(server_sockfd, 20) == -1)
    {
        perror("listen"); // 输出错误原因
        exit(1);          // 结束程序
    }

    // 客户端套接字
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);

    // 不断取出新连接并创建子线程为其服务
    while (1)
    {
        int conn = accept(server_sockfd, (struct sockaddr *)&client_addr, &length);
        if (conn < 0)
        {
            perror("connect"); // 输出错误原因
            exit(1);           // 结束程序
        }
        cout << "文件描述符为" << conn << "的客户端成功连接\n";

        sock_arr[conn] = true; // 此处需修改!!!

        thread t(server::RecvMsg, conn); // 创建线程
        t.detach();                      // 置为分离状态, 不能用 join, join 会导致主线程阻塞
    }
}

// 子线程工作的静态函数
// 注意, 前面不用加 static, 否则会编译报错
void server::RecvMsg(int conn)
{
    // 元组类型, 四个成员分别为 if_login login_name target_name target_conn
    tuple<bool, string, string, int> info;
    // bool if_login;      // 记录当前服务对象是否成功登录
    // string login_name;  // 记录当前服务对象的名字
    // string target_name; // 记录目标对象的名字
    // int target_conn;    // 目标对象的套接字描述符

    get<0>(info) = false; // 把if_login置为false
    get<3>(info) = -1;    // target_conn置为-1

    // 接收缓冲区
    char buffer[1000];

    // 不断接收数据
    while (1)
    {
        memset(buffer, 0, sizeof(buffer));
        int len = recv(conn, buffer, sizeof(buffer), 0);

        // 客户端发送 exit 或者异常结束时, 退出
        if (strcmp(buffer, "exit") == 0 || len <= 0)
        {
            close(conn);
            sock_arr[conn] = false;
            break;
        }

        cout << "收到套接字描述符为" << conn << "发来的信息:" << buffer << endl;

        string str(buffer);
        HandleRequest(conn, str, info);
    }
}

void server::HandleRequest(int conn, string str, tuple<bool, string, string, int> &info)
{
    char buffer[1000];
    string name, pass;
    bool if_login = get<0>(info);      // 记录当前服务对象是否成功登录
    string login_name = get<1>(info);  // 记录当前服务对象的名字
    string target_name = get<2>(info); // 记录目标对象的名字
    int target_conn = get<3>(info);    // 目标对象的套接字描述符
    // int group_num; // 记录群号

    // 连接 MYSQL 数据库
    MYSQL *con = mysql_init(NULL);
    mysql_real_connect(con, "127.0.0.1", "root", "wc211314", "ChatProject", 3306, NULL, CLIENT_MULTI_STATEMENTS);

    // 注册
    if (str.find("name:") != str.npos)
    {
        int p1 = str.find("name:"), p2 = str.find("pass:");
        name = str.substr(p1 + 5, p2 - 5);
        pass = str.substr(p2 + 5, str.length() - p2 - 5);

        string search = "INSERT INTO T_USER VALUES (\"" + name + "\",\"" + pass + "\");";
        cout << "sql 语句: " << search << "\n";

        mysql_query(con, search.c_str());
    }
    // 登录
    else if (str.find("login:") != str.npos)
    {
        int p1 = str.find("login:"), p2 = str.find("pass:");
        name = str.substr(p1 + 6, p2 - 6);
        pass = str.substr(p2 + 5, str.length() - p2 - 5);

        string search = "SELECT * FROM T_USER WHERE NAME=\"" + name + "\";";
        cout << "sql语句: " << search << endl;

        auto search_res = mysql_query(con, search.c_str());
        auto result = mysql_store_result(con);
        int col = mysql_num_fields(result); // 获取列数
        int row = mysql_num_rows(result);   // 获取行数

        // 查询到用户名
        if (search_res == 0 && row != 0)
        {
            cout << "查询成功\n";

            auto info = mysql_fetch_row(result); // 获取一行的信息
            cout << "查询到用户名: " << info[0] << " 密码: " << info[1] << endl;

            // 密码正确
            if (info[1] == pass)
            {
                cout << "登录密码正确\n\n";

                if_login = true;
                login_name = name; // 记录下当前登录的用户名

                mtx.lock();
                name_sock_map[login_name] = conn; // 记录下用户名和 sockid 的对应关系
                mtx.unlock();

                string str1 = "ok";
                send(conn, str1.c_str(), str1.length() + 1, 0);
            }
            // 密码错误
            else
            {
                cout << "登录密码错误\n\n";

                char str1[100] = "wrong";
                send(conn, str1, strlen(str1), 0);
            }
        }
        // 没找到用户名
        else
        {
            cout << "查询失败\n\n";

            char str1[100] = "wrong";
            send(conn, str1, strlen(str1), 0);
        }
    }
    // 设定目标的文件描述符
    else if (str.find("target:") != str.npos)
    {
        int pos1 = str.find("from");
        string target = str.substr(7, pos1 - 7), from = str.substr(pos1 + 5);
        target_name = target;
        cout << "from: " << from << endl;

        // 找不到这个目标
        if (name_sock_map.find(target) == name_sock_map.end())
            cout << "源用户为" << login_name << ",目标用户" << target_name << "仍未登录, 无法发起私聊\n ";
        // 找到了目标
        else
        {
            cout << "源用户 " << login_name << " 向目标用户 " << target_name << " 发起的私聊即将建立, 目标用户的套接字描述符为 " << name_sock_map[target] << endl;
            target_conn = name_sock_map[target];
        }
    }
    // 接收到消息,转发
    else if (str.find("content:") != str.npos)
    {
        if (target_conn == -1)
        {
            cout << "找不到目标用户 " << target_name << " 的套接字, 将尝试重新寻找目标用户的套接字\n ";

            if (name_sock_map.find(target_name) != name_sock_map.end())
            {
                target_conn = name_sock_map[target_name];
                cout << "重新查找目标用户套接字成功\n";
            }
            else
            {
                cout << "查找仍然失败,转发失败!\n";
            }
        }

        string recv_str(str);
        string send_str = recv_str.substr(8);
        cout << "用户 " << login_name << " 向 " << target_name << " 发送: " << send_str << endl;
        send_str = "[" + login_name + "]:" + send_str;
        send(target_conn, send_str.c_str(), send_str.length(), 0);
    }

    // 更新实参
    get<0>(info) = if_login;    // 记录当前服务对象是否成功登录
    get<1>(info) = login_name;  // 记录当前服务对象的名字
    get<2>(info) = target_name; // 记录目标对象的名字
    get<3>(info) = target_conn; // 目标对象的套接字描述符
}
