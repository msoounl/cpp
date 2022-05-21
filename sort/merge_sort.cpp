// 归并排序 稳定
// 待排序数组：6 2 1 4 5 9 7 3 8
#include <iostream>
#include <vector>
using namespace std;

void MergeSort(vector<int>& array);
void MergeSort(vector<int>& array, int left, int right, vector<int>& temp);
void Merge(vector<int>& array, int left, int mid, int right, vector<int>& temp);

int main(void)
{
    vector<int> array = {6, 2, 1, 4, 5, 9, 7, 3, 8};

    MergeSort(array);

    for (auto x : array)
    {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}

void MergeSort(vector<int>& array)
{
    vector<int> temp = array;
    MergeSort(array, 0, array.size() - 1, temp);
}

void MergeSort(vector<int>& array, int left, int right, vector<int>& temp)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        MergeSort(array, left, mid, temp);
        MergeSort(array, mid + 1, right, temp);
        Merge(array, left, mid, right, temp);
    }
}

void Merge(vector<int>& array, int left, int mid, int right, vector<int>& temp)
{
    int i = left;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= right)
    {
        if (array[i] <= array[j])
        {
            temp[k++] = array[i++];
        }
        else
        {
            temp[k++] = array[j++];
        }
    }

    while (i <= mid)
    {
        temp[k++] = array[i++];
    }

    while (j <= right)
    {
        temp[k++] = array[j++];
    }

    k = 0;
    while (left <= right)
    {
        array[left++] = temp[k++];
    }
}