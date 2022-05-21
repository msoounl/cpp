#include <iostream>
using namespace std;

class Node
{
    friend bool operator==(Node &node1, Node &node2);
    friend bool operator!=(Node &node1, Node &node2);
    friend bool operator<(Node &node1, Node &node2);
    friend bool operator>(Node &node1, Node &node2);
    friend bool operator<=(Node &node1, Node &node2);
    friend bool operator>=(Node &node1, Node &node2);

private:
    int val;

public:
    Node() {};

    Node(int val) {
        this->val = val;
    }

    ~Node() {};
};

bool operator==(Node &node1, Node &node2) {
    return node1.val == node2.val;
}

bool operator!=(Node &node1, Node &node2) {
    return node1.val != node2.val;
}

bool operator<(Node &node1, Node &node2) {
    return node1.val < node2.val;
}

bool operator>(Node &node1, Node &node2) {
    return node1.val > node2.val;
}

bool operator<=(Node &node1, Node &node2) {
    return node1.val <= node2.val;
}

bool operator>=(Node &node1, Node &node2) {
    return node1.val >= node2.val;
}

int main() {
    Node node1(1);
    Node node2(2);

    cout << (node1 == node2) << endl;
    cout << (node1 != node2) << endl;
    cout << (node1 < node2) << endl;
    cout << (node1 > node2) << endl;
    cout << (node1 <= node2) << endl;
    cout << (node1 >= node2) << endl;

    return 0;
}