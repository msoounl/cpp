// 插入排序 稳定
// 待排序数组：6 2 1 4 5 9 7 3 8
#include <iostream>
#include <vector>
using namespace std;

void InsertSort(vector<int>& array);
void Swap(vector<int>& array, int x, int y);

int main(void)
{
    vector<int> array = {6, 2, 1, 4, 5, 9, 7, 3, 8};

    InsertSort(array);

    for (auto x : array)
    {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}

void InsertSort(vector<int>& array)
{
    for (int i = 1; i < array.size(); i++)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            if (array[j] > array[j+1])
            {
                Swap(array, j, j + 1);
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