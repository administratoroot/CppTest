#include <iostream>
#include "SortUtil.h"
using namespace std;
int main()
{
    int arr[10] = { 2, 8, 5, 1, 6, 4, 9, 0, 7, 3 };
    ISortOpr * p = new QuickSort;
    SortUtil su(p);
    su.print(arr, 0, 9);
    su.doSort(arr, 0, 9);
    su.print(arr, 0, 9);
    delete p;
    system("pause");
    return 0;
}
