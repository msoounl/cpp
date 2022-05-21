#include <iostream>
using namespace std;

class MyClass
{
public:
    MyClass() {};

    ~MyClass() {};

    void operator()(char ch) {
        cout << ch << endl;;
    }
};

int main() {
    MyClass myClass;
    myClass('a');

    MyClass()('b');

    return 0;
}