#include <iostream>
using namespace std;

class Node
{
    friend Node operator+(Node &node1, Node &node2);
    friend Node operator-(Node &node1, Node &node2);
    friend Node operator*(Node &node1, Node &node2);
    friend Node operator/(Node &node1, Node &node2);

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

Node operator+(Node &node1, Node &node2) {
    Node temp(0);
    temp.val = node1.val + node2.val;
    return temp;
}

Node operator-(Node &node1, Node &node2) {
    Node temp(0);
    temp.val = node1.val - node2.val;
    return temp;
}

Node operator*(Node &node1, Node &node2) {
    Node temp(0);
    temp.val = node1.val * node2.val;
    return temp;
}

Node operator/(Node &node1, Node &node2) {
    Node temp(0);
    temp.val = node1.val / node2.val;
    return temp;
}

int main() {
    Node node1(4);
    Node node2(2);
    Node node3(0);

    node3 = node1 + node2;
    cout << node3.getVal() << endl;
    node3 = node1 - node2;
    cout << node3.getVal() << endl;
    node3 = node1 * node2;
    cout << node3.getVal() << endl;
    node3 = node1 / node2;
    cout << node3.getVal() << endl;

    return 0;
}