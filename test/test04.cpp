#include <iostream>

using namespace std;

int main()
{
    cout << sizeof(short) << sizeof(int) << sizeof(long) << sizeof(long long) << endl; // 2 4 8 8
    cout << sizeof(short *) << sizeof(int *) << sizeof(long *) << sizeof(long long *) << endl;

    return 0;
}