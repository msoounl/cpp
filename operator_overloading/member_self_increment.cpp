#include <iostream>
using namespace std;

class Node
{
private:
    int val;

public:
    Node() {};

    Node(int val) {
        this->val = val;
    }

    ~Node() {};

    int getVal() {
        return this->val;
    }

    void setVal(int val) {
        this->val = val;
    }

    /*
    实现前置自增运算符重载的函数的返回类型必须为自身类型的引用，否则无法实现链式前置自增运算。
    */
    Node& operator++() {
        ++(this->val);
        return *this;
    }
    
    /*
    实现后置自增运算符重载的函数的返回类型不能为自身类型的引用，否则返回了局部对象的引用，非法。
    */
    Node operator++(int) {
        Node temp(this->val);
        (this->val)++;
        return temp;
    }
};

int main() {
    Node node(1);

    cout << (++node).getVal() << endl;
    cout << (++(++node)).getVal() << endl;
    cout << (node++).getVal() << endl;

    return 0;
}