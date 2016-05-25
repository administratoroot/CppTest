#include <iostream>
#include <vector>
#include <map>
using namespace std;
#define DMAXVALUE 10.5
#define DEFAULTRPN 0.5//Ĭ�Ϸ���ϵ��
struct ACard;

std::map<int, ACard> mapCardValue;

/*
* ѯ���Ƿ�Ҫ�ơ�
* pCount����������
* cLen: ����Ҫ���������ƣ�Ĭ��Ϊ4
* cIdx����ǰ�����ߵ�����
* playerStatus����ǰ�ƾֵľ��棬��һ����ά���� playerStatus[pCount][cLen],����ֵΪ�ƺţ�
*   �ƺ�ֵΪ[1..54],����
*     �ݻ� club A~K �� 1 ~ 13
*     ���� diamond A~K �� 14 ~ 26
*     ���� hearts A ~ K �� 27 ~ 39
*     ���� spade A ~ K �� 40 ~ 52
*     С��53
*     ��� 54
*   0 ռλ������ʾ��û��Ҫ��
*/
//bool wannaCall(int pCount, int cLen, int cIdx, int[][] playerStatus) {
//    return false;
//}

/*
* ����Ϸ�߷���ʱ��������ӿڡ�
* card: �����ƺţ��ƺŹ��򣬲μ� wannaCall ����˵����
*/
//void deal(int card) 
//{
//
//}

enum Color
{
    P_CLUB = 0,//÷��
    P_DIAMOND = 1,//����
    P_HEARTS = 2,//����
    P_SPADE = 3//����
};

struct ACard
{
    ACard() :m_dValue(0.0), m_bInHeap(false){};
    ACard(double dValue, bool bInHeap) :m_dValue(dValue), m_bInHeap(bInHeap){};

    double m_dValue;
    bool m_bInHeap;
};

void initCardValueMap(std::map<int, ACard>& mapCardValue)
{
    for (int i = 1; i <= 54; ++i)//����Ĺ��������ʼ
    {
        if (i <= 10)
        {
            mapCardValue[i] = ACard(i, true);
        }
        else if (i <= 13)
        {
            mapCardValue[i] = ACard(0.5, true);
        }
        else if (i <= 23)
        {
            mapCardValue[i] = ACard(i - 13, true);
        }
        else if (i <= 26)
        {
            mapCardValue[i] = ACard(0.5, true);
        }
        else if (i <= 36)
        {
            mapCardValue[i] = ACard(i - 26, true);
        }
        else if (i <= 39)
        {
            mapCardValue[i] = ACard(0.5, true);
        }
        else if (i <= 49)
        {
            mapCardValue[i] = ACard(i - 39, true);
        }
        else if (i <= 52)
        {
            mapCardValue[i] = ACard(0.5, true);
        }
        else if (i > 52)
        {
            mapCardValue[i] = ACard(0.5, true);
        }
    }
}

//���¼�����������
void recalcCardValueMap(int* playerStatus, const int& pCount, const int& cLen, std::map<int, ACard>& mapCardValue)
{
    for (int i = 0; i < pCount; i++)
    {
        for (int j = 0; j < cLen; j++)
        {
            int nCardIndex = playerStatus[i*pCount + j];
            if (nCardIndex != 0)
            {
                mapCardValue[nCardIndex].m_bInHeap = false;
            }
        }
    }
}

int getEnableCount(std::map<int, ACard>& mapCardValue)
{
    int nCount = 0;
    for each(auto card in mapCardValue)
    {
        ACard curCard = card.second;
        if (curCard.m_bInHeap)
        {
            ++nCount;
        }
    }
    return nCount;
}

double getSurviveMathExp(double dTotal, std::map<int, ACard>& mapCardValue)
{
    double dRet = 0.0;
    int nEnableCount = getEnableCount(mapCardValue);//��ȡ���õ�����
    int nCanLiveCount = 0;
    for each(auto card in mapCardValue)
    {
        ACard curCard = card.second;
        if ((curCard.m_dValue + dTotal) <= DMAXVALUE)
        {
            ++nCanLiveCount;
        }
    }
    if (nEnableCount != 0)
    {
        dRet = double(nCanLiveCount) / double(nEnableCount);
    }
    return dRet;
}

double getMyTotal(int* playerStatus, const int& pCount, const int& cLen, const int& cIdx)
{
    double dTotal = 0.0;
    for (int i = 0; i < cLen; ++i)
    {
        int nCardIndex = playerStatus[cIdx*cLen + i];
        std::map<int, ACard>::iterator it = mapCardValue.find(nCardIndex);
        if (it != mapCardValue.end())
        {
            dTotal += it->second.m_dValue;
        }
    }
    return dTotal;
}

int getSurvivePlayerCount(int pCount, int cLen, int* playerStatus)
{
    int nCount = 0;
    for (int i = 0; i < pCount; i++)
    {
        double dPlayerTotal = 0.0;
        for (int j = 0; j < cLen; j++)
        {
            int nCardIndex = playerStatus[i*pCount + j];
            
            if (nCardIndex != 0)
            {
                dPlayerTotal += mapCardValue[nCardIndex].m_dValue;
            }
        }
        if (dPlayerTotal <= DMAXVALUE)
        {
            ++nCount;
        }
    }
    return nCount;
}

//��̬���ڷ���ϵ���㷨
double getDynamicRPN(int pCount, int cLen, int* playerStatus, double dSurviveExp)
{
    //�������Խ�٣�ԽӦ�ò�ȡ���ز���
    double dRpn = DEFAULTRPN;
    int nSurvivePlayers = getSurvivePlayerCount(pCount, cLen, playerStatus);
    //��������ϵ��
    double dDeadK = 1.0 - (double(nSurvivePlayers) / double(pCount));
    //0.5ֵ�Ǿ���ֵ
    dRpn += (dDeadK * 0.5);

    //�����˵�����ʱ��,��̬�������С��0.7�Ҳ�ץ�ƣ����������ɲ�ȡ�ƣ�����ȡ����İ�ȫ
    if (!nSurvivePlayers < 3)
    {
        if (dSurviveExp < 0.7)
        {
            dRpn = 1.0;
        }
    }
    return dRpn;
}

bool wannaCall(int pCount, int cLen, int cIdx, int* playerStatus) 
{
    bool bRet = false;
    //�ҵ��ܹ���ֵ
    double dMyTotal = getMyTotal(playerStatus, pCount, cLen, cIdx);
    //��ǰץ�����ܴ�����ѧ����
    double dSurviveExp = getSurviveMathExp(dMyTotal, mapCardValue);
    //������������ڷ���ϵ��
    double dRpn = getDynamicRPN(pCount, cLen, playerStatus, dSurviveExp);
    
    //ʣ�����Խ�٣�ԽӦ�ñ���
    int nRemainplayers = getSurvivePlayerCount(pCount, cLen, playerStatus);
    
    
    if ((dSurviveExp > dRpn))
    {
        bRet = true;
    }
    return bRet;
}

int main()
{
    //std::map<int, ACard> mapCardValue;
    initCardValueMap(mapCardValue);//ÿ�ֿ�ʼʱ����Ҫ��ʼ��
#define PLAYERCOUNT 3
#define VISIABLECARDSCOUNT 4
    int playerStatus[PLAYERCOUNT][VISIABLECARDSCOUNT] =
    {
        {2,1,4,0},
        {3,15,0,0},
        {9,10,0,0}
    };
    recalcCardValueMap(playerStatus[0], PLAYERCOUNT, VISIABLECARDSCOUNT, mapCardValue);
    bool bNeed = wannaCall(PLAYERCOUNT, VISIABLECARDSCOUNT, 1, playerStatus[0]);
    return 0;
}


