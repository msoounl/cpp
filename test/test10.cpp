#include <iostream>
#include <hiredis/hiredis.h>

using namespace std;

int main()
{
    redisContext *c = redisConnect("127.0.0.1", 6379);
    if (c->err)
    {
        redisFree(c);
        cout << "连接失败" << endl;
        return 1;
    }
    cout << "连接成功" << endl;

    redisReply *r = (redisReply *)redisCommand(c, "PING");
    cout << r->str << endl;

    redisReply *r1 = (redisReply *)redisCommand(c, "set a 123");
    cout << r1->str << endl;

    return 0;
}
