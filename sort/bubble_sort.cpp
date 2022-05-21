// 冒泡排序 稳定
// 待排序数组：6 2 1 4 5 9 7 3 8
#include <iostream>
#include <vector>
using namespace std;

void BubbleSort(vector<int>& array);
void Swap(vector<int>& array, int x, int y);

int main(void)
{
    vector<int> array = {6, 2, 1, 4, 5, 9, 7, 3, 8};

    BubbleSort(array);

    for (auto x : array)
    {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}

void BubbleSort(vector<int>& array)
{
    for (int i = 0; i < array.size() - 1; i++)
    {
        for (int j = array.size() - 1; j >= i; j--)
        {
            if (array[j] < array[j-1])
            {
                Swap(array, j - 1, j);
            }
        }
    }
}

void Swap(vector<int>& array, int x, int y)
{
    int temp = array[x];
    array[x] = array[y];
    array[y] = temp;
}