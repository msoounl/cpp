// 快速排序 不稳定
// 待排序数组：6 2 1 4 5 9 7 3 8
#include <iostream>
#include <vector>
using namespace std;

void QuickSort(vector<int>& array, int left, int right);
int Partition(vector<int>& array, int left, int right);
void Swap(vector<int>& array, int x, int y);

int main(void)
{
    vector<int> array = {6, 2, 1, 4, 5, 9, 7, 3, 8};

    QuickSort(array, 0, array.size() - 1);

    for (auto x : array)
    {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}

void QuickSort(vector<int>& array, int left, int right)
{
    if (left >= right)
    {
        return;
    }

    int mid = Partition(array, left, right);
    QuickSort(array, left, mid - 1);
    QuickSort(array, mid + 1, right);
}

int Partition(vector<int>& array, int left, int right)
{
    int pivot = array[left];
    int l = left + 1;
    int r = right;

    while (l <= r)
    {
        while (l <= r && array[r] >= pivot) // 必须得是 l <= r，不然如果所有值都大于或等于 pivot，r 会固定在 left + 1，错误交换
        {
            r--;
        }
        while (l <= r && array[l] < pivot)
        {
            l++;
        }
        if (l <= r)
        {
            Swap(array, l, r);
        }
    }
    Swap(array, r, left); // 取 r 是因为，r 最终固定的位置的值一定是小于或等于 pivot 的
    return r;
}

void Swap(vector<int>& array, int x, int y)
{
    int temp = array[x];
    array[x] = array[y];
    array[y] = temp;
}