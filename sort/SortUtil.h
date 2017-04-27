#pragma once
class ISortOpr
{
public:
    virtual void doSort(int* arr, int low, int high) = 0;
};

class QuickSort :public ISortOpr
{
public:
    virtual void doSort(int* arr, int low, int high);
private:
    //��arr��low��high֮��ԭַ����
    int patition(int* arr, int low, int high);
};

class SortUtil
{
public:
    SortUtil(ISortOpr* pOpr);
    ~SortUtil();
    void doSort(int* arr, int low, int high);
    void print(int* arr, int low, int high);
private:
    ISortOpr* m_pOpr;
};

