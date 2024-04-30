#include <iostream>

using namespace std;

class A {};

class B
{
public:
    char a; // 字节对齐 4
    int b; // 4
};

class C
{
public:
    virtual void fun(){};
};

class D
{
public:
    char b; // 字节对齐 8
    virtual void fun(){}; // 8
    static int c;
    static int d;
    static int f;
};

int main()
{
    cout << sizeof(char) << " " << sizeof(char *) << endl;
    cout << sizeof(A) << " " << sizeof(B) <<  " " << sizeof(C) <<  " " << sizeof(D) << endl; // 1 8 8 16
    return 0;
}