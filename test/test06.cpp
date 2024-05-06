#include <iostream>
#include <thread>

void myFunction()
{
    // 线程执行的函数
    for (int i = 0; i < 5; ++i)
    {
        std::cout << "Thread executing..." << std::endl;
    }
}

int main()
{
    std::thread myThread(myFunction); // 创建线程并执行 myFunction

    // 其他操作...

    if (myThread.joinable())
    {
        std::cout << "joinable:" << (myThread.joinable() ? "true" : "false") << std::endl;

        myThread.join();

        std::cout << "joinable:" << (myThread.joinable() ? "true" : "false") << std::endl;
    }

    std::cout << "Main thread continues..." << std::endl;

    return 0;
}