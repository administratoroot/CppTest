#include <iostream>
#include <vector>
#include <map>
using namespace std;
#define DMAXVALUE 10.5
#define DEFAULTRPN 0.5//默认风险系数
struct ACard;

std::map<int, ACard> mapCardValue;

/*
* 询问是否要牌。
* pCount：参赛人数
* cLen: 最多可要多少张明牌，默认为4
* cIdx：当前参赛者的索引
* playerStatus：当前牌局的局面，是一个二维数组 playerStatus[pCount][cLen],数组值为牌号，
*   牌号值为[1..54],其中
*     草花 club A~K ： 1 ~ 13
*     方块 diamond A~K ： 14 ~ 26
*     红心 hearts A ~ K ： 27 ~ 39
*     黑桃 spade A ~ K ： 40 ~ 52
*     小鬼：53
*     大鬼： 54
*   0 占位符，表示还没有要牌
*/
//bool wannaCall(int pCount, int cLen, int cIdx, int[][] playerStatus) {
//    return false;
//}

/*
* 像游戏者发牌时调用这个接口。
* card: 发的牌号，牌号规则，参见 wannaCall 参数说明；
*/
//void deal(int card) 
//{
//
//}

enum Color
{
    P_CLUB = 0,//梅花
    P_DIAMOND = 1,//方块
    P_HEARTS = 2,//红桃
    P_SPADE = 3//黑桃
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
    for (int i = 1; i <= 54; ++i)//出题的诡异计数起始
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

//重新计算堆里面的牌
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
    int nEnableCount = getEnableCount(mapCardValue);//获取可用的牌数
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

//动态调节风险系数算法
double getDynamicRPN(int pCount, int cLen, int* playerStatus, double dSurviveExp)
{
    //存活的玩家越少，越应该采取保守策略
    double dRpn = DEFAULTRPN;
    int nSurvivePlayers = getSurvivePlayerCount(pCount, cLen, playerStatus);
    //死亡比例系数
    double dDeadK = 1.0 - (double(nSurvivePlayers) / double(pCount));
    //0.5值是经验值
    dRpn += (dDeadK * 0.5);

    //两个人单挑的时候,静态生存概率小于0.7我才抓牌，否则我宁可不取牌，来换取自身的安全
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
    //我的总共面值
    double dMyTotal = getMyTotal(playerStatus, pCount, cLen, cIdx);
    //当前抓牌我能存活的数学期望
    double dSurviveExp = getSurviveMathExp(dMyTotal, mapCardValue);
    //根据玩家数调节风险系数
    double dRpn = getDynamicRPN(pCount, cLen, playerStatus, dSurviveExp);
    
    //剩的玩家越少，越应该保守
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
    initCardValueMap(mapCardValue);//每局开始时候需要初始化
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


