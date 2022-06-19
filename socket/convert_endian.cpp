/*
现代 PC 大多采用小端字节序，因此小端字节序又被称为主机字节序。
数据如果在两台使用不同字节序的主机之间直接传递，会被接收端错误解读。
解决方法：发送端总是把要发送的数据转换为大端字节序数据后发送。这样接收端知道接收到的数据是大端字节序数据，可以根据自身机器字节序决定是否转换字节序。因此大端字节序又被称为网络字节序。
即使是同一台机器上的两个进程通信，也要考虑字节序问题，比如一个进程由 C 编写（采用小端字节序），另一个进程由 JAVA 编写（JAVA 虚拟机采用大端字节序）。
*/

/*
Linux 字节序转换函数
unsigned long int htonl(unsigned long int hostlong);
unsigned long int ntohl(unsigned long int netlong);
unsigned short int htons(unsigned short int hostshort);
unsigned short int ntohs(unsigned short int netshort);
函数含义解释：htonl 表示 “host to net long”，即将长整型的整数由主机字节序数据转换为网络字节序数据。
长整型函数一般用来转换 IP 地址，短整型函数一般用来转换端口号。
*/
#include <iostream>
using namespace std;

int main(void) {
    cout << "学会字节序转换了！" << endl;
    return 0;
}