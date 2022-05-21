// 堆排序 不稳定
// 待排序数组：6 2 1 4 5 9 7 3 8
#include <iostream>
#include <vector>
using namespace std;

void HeapSort(vector<int>& array);
void UpdateBigRootHeap(vector<int>& array, int size);
void Swap(vector<int>& array, int x, int y);

int main(void)
{
    vector<int> array = {6, 2, 1, 4, 5, 9, 7, 3, 8};

    HeapSort(array);

    for (auto x : array)
    {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}

void HeapSort(vector<int>& array)
{
    for (int i = array.size(); i > 1; i--)
    {
        UpdateBigRootHeap(array, i);
        Swap(array, 0, i - 1);
    }
}

void UpdateBigRootHeap(vector<int>& array, int size)
{
    for (int i = size / 2 - 1; i >= 0; i--)
    {
        int temp = array[i];
        int k = i;
        for (int j = i * 2 + 1; j <= size - 1; j = j * 2 + 1)
        {
            if (j < size - 1 && array[j] < array[j+1])
            {
                j = j + 1;
            }

            if (array[j] <= temp)
            {
                break;
            }
            else
            {
                array[k] = array[j];
                k = j;
            }
        }
        array[k] = temp;
    }
}

void Swap(vector<int>& array, int x, int y)
{
    int temp = array[x];
    array[x] = array[y];
    array[y] = temp;
}