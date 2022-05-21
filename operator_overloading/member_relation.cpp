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

    bool operator==(Node &node) {
        return this->val == node.val;
    }

    bool operator!=(Node &node) {
        return this->val != node.val;
    }

    bool operator<(Node &node) {
        return this->val < node.val;
    }

    bool operator>(Node &node) {
        return this->val > node.val;
    }

    bool operator<=(Node &node) {
        return this->val <= node.val;
    }

    bool operator>=(Node &node) {
        return this->val >= node.val;
    }
};

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