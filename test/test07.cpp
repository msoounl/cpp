#include <iostream>
#include <thread>

void myFunction1()
{
    for (int i = 0; i < 10; i++)
    {
        std::cout << "Thread 1 executing..." << std::endl;
    }
}

void myFunction2()
{
    for (int i = 0; i < 10; i++)
    {
        std::cout << "Thread 2 executing..." << std::endl;
    }
}

int main()
{
    std::thread thread1(myFunction1); // 创建线程1，并执行 myFunction1
    std::thread thread2(myFunction2); // 创建线程2，并执行 myFunction2

    // 其他操作...
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    thread1.swap(thread2); // 交换两个线程对象的执行内容

    // 其他操作...

    thread1.join(); // 等待线程1执行完成
    thread2.join(); // 等待线程2执行完成

    std::cout << "Main thread continues..." << std::endl;

    return 0;
}