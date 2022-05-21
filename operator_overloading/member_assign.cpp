#include <iostream>
using namespace std;

class Node
{
private:
    int *val;

public:
    Node() {};

    Node(int val) {
        this->val = new int(val);
    }

    ~Node() {
        if (val != nullptr) {
            delete val;
        }
    };

    int* getVal() {
        return this->val;
    }

    void setVal(int *val) {
        this->val = val;
    }

    /*
    如果重载赋值运算符的函数没有返回自身类型的引用，无法实现链式赋值运算。
    如果没有重载赋值运算符实现深拷贝，使用编译器提供的浅拷贝，会导致堆区内存重复释放的错误和内存泄露。
    */
    Node& operator=(Node &node) {
        // 编译器提供的浅拷贝
        // this->val = node.val;

        // 重载赋值运算符实现深拷贝
        if (val != nullptr) {
            delete val;
        }
        val = new int(*(node.val));

        return *this;
    }
};

int main() {
    Node node1(1);
    Node node2(2);
    Node node3(3);

    node3 = node2 = node1;
    cout << *(node1.getVal()) << endl;
    cout << *(node2.getVal()) << endl;
    cout << *(node3.getVal()) << endl;

    return 0;
}