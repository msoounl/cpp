#include <iostream>
using namespace std;

class Node
{
    friend ostream& operator<<(ostream &out, Node &node);
    friend istream& operator>>(istream &in, Node &node);

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
};

/*
左移右移运算符重载函数的返回类型必须是输出流或输入流的引用，否则无法实现链式输出和链式输入。
*/

ostream& operator<<(ostream &out, Node &node) {
    out << node.val;
    return out;
}

istream& operator>>(istream &in, Node &node) {
    in >> node.val;
    return in;
}

int main() {
    Node node1(0);
    Node node2(0);

    cin >> node1 >> node2;
    cout << node1 << " " << node2 << endl;

    return 0;
}