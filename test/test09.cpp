#include <iostream>
#include <string>
#include <mysql/mysql.h>

using namespace std;

int main()
{
    string str = "name:msooupass:123456";

    int p1 = str.find("name:");
    cout << "p1: " << p1 << endl;
    int p2 = str.find("pass:");
    cout << "p2: " << p2 << endl;

    string name = str.substr(p1 + 5, p2 - 5);
    string pass = str.substr(p2 + 5, str.length() - p2 - 5);
    cout << "name: " << name << endl;
    cout << "pass: " << pass << endl;

    MYSQL *con = mysql_init(NULL);
    mysql_real_connect(con, "127.0.0.1", "root", "wc211314", "ChatProject", 3306, NULL, CLIENT_MULTI_STATEMENTS);

    string search = "INSERT INTO T_USER VALUES (\"" + name + "\",\"" + pass + "\");";
    cout << "sql 语句: " << search << "\n";

    mysql_query(con, search.c_str());

    return 0;
}