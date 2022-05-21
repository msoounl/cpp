#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class ListNode {
public:
    int val;
    ListNode * next;

    ListNode(){}

    ListNode(int val) {
        this->val = val;
        this->next = nullptr;
    }

    ListNode(int val, ListNode *next) {
        this->val = val;
        this->next = next;
    }
};

class cmp {
public:
    bool operator()(ListNode * &a, ListNode * &b) const {
        // return a->val < b->val; // 大根堆
        return a->val > b->val; // 小根堆
    }
};

int main(void) {
    priority_queue<int> pq;
    cout << "pq is empty: " << pq.empty() << endl;
    pq.push(3);
    pq.push(5);
    pq.push(2);
    pq.push(1);
    pq.push(6);
    pq.push(4);

    cout << "pq's top is: " << pq.top() << endl;

    priority_queue<int, vector<int>, less<int> > pq_big;
    pq_big.push(3);
    pq_big.push(5);
    pq_big.push(2);
    pq_big.push(1);
    pq_big.push(6);
    pq_big.push(4);
    cout << "pq_big's top is: " << pq_big.top() << endl;

    priority_queue<int, vector<int>, greater<int> > pq_small;
    pq_small.push(3);
    pq_small.push(5);
    pq_small.push(2);
    pq_small.push(1);
    pq_small.push(6);
    pq_small.push(4);
    cout << "pq_small's top is: " << pq_small.top() << endl;

    priority_queue<ListNode *, vector<ListNode *>, cmp> pq_listnode;
    pq_listnode.push(new ListNode(3));
    pq_listnode.push(new ListNode(5));
    pq_listnode.push(new ListNode(2));
    pq_listnode.push(new ListNode(1));
    pq_listnode.push(new ListNode(6));
    pq_listnode.push(new ListNode(4));
    cout << "pq_listnode's top is: " << pq_listnode.top()->val << endl;

    return 0;
}