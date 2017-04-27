#include "SortUtil.h"
#include <iostream>
#include <time.h> 
#include <assert.h>
using namespace std;

SortUtil::SortUtil(ISortOpr* pOpr) :m_pOpr(pOpr)
{

}


SortUtil::~SortUtil()
{

}

void SortUtil::print(int* arr, int low, int high)
{
    for (int i = low; i < high; ++i)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void SortUtil::doSort(int* arr, int low, int high)
{
    m_pOpr->doSort(arr, low, high);
}

int QuickSort::patition(int* arr, int low, int high)
{
    assert(high > low);
    srand((unsigned)time(NULL));
    int nPivotPos = rand() % (high - low) + low;
    //int nPivotPos = low;
    int nPivotVal = arr[nPivotPos];
    //低位小于高位才排序
    while (low < high)
    {
        while (arr[high] > nPivotVal)
        {
            --high;
        }
        swap(arr[nPivotPos], arr[high]);
        nPivotPos = high;
        while (arr[low] < nPivotVal)
        {
            ++low;
        }
        swap(arr[nPivotPos], arr[low]);
        nPivotPos = low;
    }
    return nPivotPos;
}

void QuickSort::doSort(int* arr, int low, int high)
{
    if (low < high)
    {
        int nPivotPos = patition(arr, low, high);
        doSort(arr, low, nPivotPos - 1);
        doSort(arr, nPivotPos + 1, high);
    }
}
