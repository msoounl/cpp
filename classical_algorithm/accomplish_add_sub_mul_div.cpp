/*
不使用加减乘除运算符实现加减乘除运算
*/
#include <iostream>
#include <string>
using namespace std;

int add(int x, int y);
int negative(int x);
int subtraction(int x, int y);
int mult(int x, int y);
int divide(int x, int y);

int main() {
    int a = 0, b = 0;
    cin >> a >> b;

    cout << "add: " << add(a, b) << endl;
    cout << "subtraction: " << subtraction(a, b) << endl;
    cout << "mult: " << mult(a, b) << endl;
    try {
        cout << "divide: " << divide(a, b) << endl;
    } catch(string& ex) {
        cout << ex << endl;
    }

    return 0;
}

int add(int x, int y) {
    while (y != 0) {
        int temp = (x & y) << 1;
        x ^= y;
        y = temp;
    }
    return x;
}

int negative(int x) {
    return add(~x, 1);
}

// 此方法太简单了！
// int subtraction(int x, int y) {
//     return add(x, negative(y));
// }

int subtraction(int x, int y) {
    while (y != 0) {
        int temp = x & y;
        x ^= temp;
        y ^= temp;
        x |= y;
        y <<= 1;
    }
    return x;
}

int mult(int x, int y) {
    int xx = x > 0 ? x : negative(x);
    int yy = y > 0 ? y : negative(y);

    int result = 0;
    while (yy != 0) {
        if ((yy & 1) == 1) {
            result = add(result, xx);
        }
        xx <<= 1;
        yy >>= 1;
    }
    return (x ^ y) >= 0 ? result : negative(result);
}

int divide(int x, int y) {
    if (y == 0) {
        throw string("除数不能为零！");
    }

    int xx = x > 0 ? x : negative(x);
    int yy = y > 0 ? y : negative(y);

    int result = 0;
    for (int index = 31; index >= 0; index = subtraction(index, 1)) {
        if ((xx >> index) >= yy) {
            result = add(result, 1 << index);
            xx = subtraction(xx, yy << index);
        }
    }
    return (x ^ y) >= 0 ? result : negative(result);
}