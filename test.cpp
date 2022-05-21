#include <iostream>
#include <vector>
using namespace std;

vector<int> getNext(vector<char> &arr, int length);

int main()
{
    vector<char> arr = {' ', 'A', 'A', 'B', 'A', 'A', 'F'};
    vector<int> next = getNext(arr, arr.size());

    for (auto x : next) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}

vector<int> getNext(vector<char> &arr, int length) { // arr: A A B A A F next: 0 0 1 2 1 2 3
    vector<int> next(length);
    next[1] = 0;
    int i = 1;
    int j = 0;

    while (i <= length) {
        if (j == 0 || arr[i] == arr[j]) {
            next[++i] = ++j;
        } else {
            j = next[j];
        }
    }

    return next;
}