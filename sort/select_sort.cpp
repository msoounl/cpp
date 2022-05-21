// 选择排序 不稳定
// 待排序数组：6 2 1 4 5 9 7 3 8
#include <iostream>
#include <vector>
using namespace std;

void SelectSort(vector<int>& array);
void Swap(vector<int>& array, int x, int y);

int main(void)
{
    vector<int> array = {6, 2, 1, 4, 5, 9, 7, 3, 8};

    SelectSort(array);

    for (auto x : array)
    {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}

void SelectSort(vector<int>& array)
{
    for (int i = 0; i < array.size(); i++)
    {
        int min = array[i];
        int minIndex = i;
        for (int j = i + 1; j < array.size(); j++)
        {
            if (array[j] < min)
            {
                min = array[j];
                minIndex = j;
            }
        }
        Swap(array, i, minIndex);
    }
}

void Swap(vector<int>& array, int x, int y)
{
    int temp = array[x];
    array[x] = array[y];
    array[y] = temp;
}