#include <iostream>
using namespace std;
struct BTreeNode
{
    int m_value;
    BTreeNode* lChild;
    BTreeNode* rChild;
    BTreeNode() :m_value(-1), lChild(nullptr), rChild(nullptr){};
};

BTreeNode* constructTree(int* pPreStart, int* pPreEnd, int* pInStart, int* pInEnd)
{

    BTreeNode* root = new BTreeNode();
    //前序遍历的第一个元素是根结点
    root->m_value = *pPreStart;
    if (pPreStart == pPreEnd || pInStart == pInEnd)
    {
        return root;
    }
    int* pCurIndex = pInStart;
    while (((*pCurIndex) != (*pPreStart)) && (pCurIndex < pInEnd))
    {
        ++pCurIndex;
    }


    int nLeftLength = pCurIndex - pInStart;
    int nRightLength = pInEnd - pCurIndex;

    if (nLeftLength > 0)
    {
        int* pPreStart1 = pPreStart + 1;
        int* pPreEnd1 = pPreStart + nLeftLength;
        int* pInStart1 = pInStart;
        int* pInEnd1 = pInStart + nLeftLength - 1;
        root->lChild = constructTree(pPreStart1, pPreEnd1, pInStart1, pInEnd1);
    }

    if (nRightLength > 0)
    {
        int* pPreStart2 = pPreStart + 1 + nLeftLength;
        int* pPreEnd2 = pPreEnd;
        int* pInStart2 = pCurIndex + 1;
        int* pInEnd2 = pInEnd;
        root->rChild = constructTree(pPreStart2, pPreEnd2, pInStart2, pInEnd2);
    }

    return root;
}

BTreeNode* rebuildBTree(int* pPreOrder, int* pInOrder, int nLength)
{
    int* pPreStart = pPreOrder;
    int* pPreEnd = pPreOrder + nLength - 1;
    int* pInStart = pInOrder;
    int* pInEnd = pInOrder + nLength - 1;
    BTreeNode* retroot = constructTree(pPreStart, pPreEnd, pInStart, pInEnd);
    return retroot;
}



int main()
{
    int preOrder[8] = { 1, 2, 4, 7, 3, 5, 6, 8 };
    int inOrder[8] = { 4, 7, 2, 1, 5, 3, 8, 6 };
    rebuildBTree(preOrder, inOrder, 8);
    system("pause");
    return 0;
}