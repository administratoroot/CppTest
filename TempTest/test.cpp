#include <iostream>
#include <vector>
#include <map>
using namespace std;
#define DMAXVALUE 10.5
#define DEFAULTRPN 0.5//默认风险系数
struct ACard;
static std::map<int, ACard> mapCardValue;//牌号 牌
static std::vector<double> vecMyCards;
struct ACard
{
    ACard() :m_dValue(0.0), m_bInHeap(false){};
    ACard(double dValue, bool bInHeap) :m_dValue(dValue), m_bInHeap(bInHeap){};

    double m_dValue;//面值
    bool m_bInHeap;//是否在堆里面
};

//获取数学期望
double getCurExpInHeap()
{
    int nCount = 0;
    double dTotal = 0.0;
    double dRet = 0.0;
    for each(auto card in mapCardValue)
    {
        ACard curCard = card.second;
        if (curCard.m_bInHeap)
        {
            ++nCount;
            dTotal += curCard.m_dValue;
        }
    }
    dRet = dTotal / (double)nCount;
    return dRet;
}

//获取标准差
double getCurSTDInHeap()
{
    //S=[ (x1-x)^2+(x2-x)^2+(x3-x)^2+……+(xn-x)^2] 
    double dExp = getCurExpInHeap();
    double dTotal = 0.0;
    int nCount = 0;
    for each(auto card in mapCardValue)
    {
        ACard curCard = card.second;
        if (curCard.m_bInHeap)
        {
            ++nCount;
            double dValue = curCard.m_dValue;
            dTotal += pow(dValue - dExp, 2);
        }
    }
    double dVar = sqrt(dTotal / (double)nCount);
    return dVar;
}

void initCardValueMap(std::map<int, ACard>& mapCardValue)
{
    mapCardValue.clear();
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
            int nCardIndex = playerStatus[i*cLen + j];
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

double getMyTotal()
{
    double dTotal = 0.0;
    for each(double dValue in vecMyCards)
    {
        dTotal += dValue;
    }
    return dTotal;
}


//静态生存概率算法
double getSurviveMathExp(double dTotal)
{
    double dRet = 0.0;
    int nEnableCount = getEnableCount(mapCardValue);//获取可用的牌数
    int nCanLiveCount = 0;//抓牌是否可以存活
    //double dCurMyTotal = getMyTotal();
    for each(auto card in mapCardValue)
    {
        ACard curCard = card.second;
        if ((dTotal + curCard.m_dValue) <= DMAXVALUE)
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


int getEstimateSurvivePlayerCount(int pCount, int cLen, int* playerStatus, const int& cIdx)
{
    int nCount = 0;

    for (int i = 0; i < pCount; i++)
    {
        double dPlayerTotal = 0.0;
        if (cIdx == i)
        {
            //自己的不按照这算
            dPlayerTotal = getMyTotal();
            if (dPlayerTotal <= DMAXVALUE)
            {
                ++nCount;
            }
            continue;
        }
        else
        {
            for (int j = 0; j < cLen; j++)
            {
                int nCardIndex = playerStatus[i*cLen + j];

                if (nCardIndex != 0)
                {
                    dPlayerTotal += mapCardValue[nCardIndex].m_dValue;
                }
            }
            //取置信区间在2σ范围内，概率P=95.4%
            //double dCurExp = getCurExpInHeap();
            //double dSTD = getCurSTDInHeap();
            //采用较保守的估计法
            //dCurExp += (dSTD * 2);
            double dSurviveExp = getSurviveMathExp(dPlayerTotal);
            //采用保守的估计法,生存概率>0.4视为存活
            if (dSurviveExp > 0.4)
            {
                ++nCount;
            }
        }
    }
    return nCount;
}

//动态基准风险系数调节算法
double getDynamicRPN(int pCount, int cLen, int* playerStatus, double dSurviveExp, int cIdx)
{
    //存活的玩家越少，越应该采取保守策略
    double dRpn = DEFAULTRPN;
    int nSurvivePlayers = getEstimateSurvivePlayerCount(pCount, cLen, playerStatus, cIdx);
    //死亡比例系数
    double dDeadK = 1.0 - (double(nSurvivePlayers) / double(pCount));
    //0.5值是经验值
    dRpn += (dDeadK * 0.5);

    //两个人单挑的时候,静态生存概率小于0.7我才抓牌，否则我宁可不取牌，来换取自身的安全
    if (nSurvivePlayers < 3)
    {
        if (dSurviveExp < 0.7)
        {
            dRpn = 1.0;
        }
    }
    return dRpn;
}

const char* getName()
{
    return "zhangx-y";
}

void notifyGameStart()
{
    initCardValueMap(mapCardValue);//每局开始时候需要初始化
}

bool wannaCall(int pCount, int cLen, int cIdx, int* playerStatus)
{
    recalcCardValueMap(playerStatus, pCount, cLen, mapCardValue);

    bool bRet = false;
    //我的总共面值
    double dMyTotal = getMyTotal();
    //当前抓牌我能存活的数学期望
    double dSurviveExp = getSurviveMathExp(dMyTotal);

    //根据玩家数动态调节风险系数
    double dRpn = getDynamicRPN(pCount, cLen, playerStatus, dSurviveExp, cIdx);
    //剩的玩家越少，越应该保守
    //int nRemainplayers = getEstimateSurvivePlayerCount(pCount, cLen, playerStatus, cIdx);

    if ((dSurviveExp > dRpn))
    {
        bRet = true;
    }
    return bRet;
}

void deal(int card)
{
    //Nothing to do.
    mapCardValue[card].m_bInHeap = false;
    vecMyCards.push_back(mapCardValue[card].m_dValue);
}

int main()
{
    initCardValueMap(mapCardValue);//每局开始时候需要初始化
//    
//#define PLAYERCOUNT 5
//#define VISIABLECARDSCOUNT 4
//    int playerStatus[PLAYERCOUNT][VISIABLECARDSCOUNT] =
//    {
//        {2,1,4,0},
//        {34,15,0,0},
//        {9,10,0,0},
//        {5,32,0,0},
//        {33,42,0,0}
//    };
//    deal(34);
//    deal(15);
//    recalcCardValueMap(playerStatus[0], PLAYERCOUNT, VISIABLECARDSCOUNT, mapCardValue);
//    bool bNeed = wannaCall(PLAYERCOUNT, VISIABLECARDSCOUNT, 1, playerStatus[0]);
    return 0;
}


