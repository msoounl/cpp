/*
信号是由操作系统传给进程的中断，会提早终止一个程序。在 UNIX、LINUX、Mac OS X 或 Windows 系统上，可以通过按 Ctrl+C 产生中断。
有些信号不能被程序捕获，但是下表所列信号可以在程序中捕获，并可以基于信号采取适当的动作。这些信号是定义在 C++ 头文件 <csignal> 中。
 信号   | 描述                                         
 ------ | ------
SIGABRT | 程序的异常终止，如调用 abort。               
SIGFPE  | 错误的算术运算，比如除以零或导致溢出的操作。 
SIGILL  | 检测非法指令。                               
SIGINT  | 程序终止（interrupt）信号。                  
SIGSEGV | 非法访问内存。                               
SIGTERM | 发送到程序的终止请求。                       
*/
#include <iostream>
#include <csignal>
#include <unistd.h>
using namespace std;

void func(int sig);

int main() {
    /*
    SIGINT 信号可以被捕获，通过 signal 函数调用 func 回调函数执行捕获到 SIGINT 信号后的行为。
    */
    signal(SIGINT, func);

    while (true) {
        cout << "while 执行中..." << endl;
        sleep(5); // sleep() 函数定义在头文件 <unistd.h> 中。
    }
    
    return 0;
}

void func(int sig) {
    cout << "收到了信号 " << sig << endl;
}