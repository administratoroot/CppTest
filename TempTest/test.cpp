#include <iostream>
#include <vector>
#include <map>
using namespace std;
#define DMAXVALUE 10.5
#define DEFAULTRPN 0.5//Ĭ�Ϸ���ϵ��
struct ACard;
static std::map<int, ACard> mapCardValue;//�ƺ� ��
static std::vector<double> vecMyCards;
struct ACard
{
    ACard() :m_dValue(0.0), m_bInHeap(false){};
    ACard(double dValue, bool bInHeap) :m_dValue(dValue), m_bInHeap(bInHeap){};

    double m_dValue;//��ֵ
    bool m_bInHeap;//�Ƿ��ڶ�����
};

//��ȡ��ѧ����
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

//��ȡ��׼��
double getCurSTDInHeap()
{
    //S=[ (x1-x)^2+(x2-x)^2+(x3-x)^2+����+(xn-x)^2] 
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


//��̬��������㷨
double getSurviveMathExp(double dTotal)
{
    double dRet = 0.0;
    int nEnableCount = getEnableCount(mapCardValue);//��ȡ���õ�����
    int nCanLiveCount = 0;//ץ���Ƿ���Դ��
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
            //�Լ��Ĳ���������
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
            //ȡ����������2�ҷ�Χ�ڣ�����P=95.4%
            //double dCurExp = getCurExpInHeap();
            //double dSTD = getCurSTDInHeap();
            //���ýϱ��صĹ��Ʒ�
            //dCurExp += (dSTD * 2);
            double dSurviveExp = getSurviveMathExp(dPlayerTotal);
            //���ñ��صĹ��Ʒ�,�������>0.4��Ϊ���
            if (dSurviveExp > 0.4)
            {
                ++nCount;
            }
        }
    }
    return nCount;
}

//��̬��׼����ϵ�������㷨
double getDynamicRPN(int pCount, int cLen, int* playerStatus, double dSurviveExp, int cIdx)
{
    //�������Խ�٣�ԽӦ�ò�ȡ���ز���
    double dRpn = DEFAULTRPN;
    int nSurvivePlayers = getEstimateSurvivePlayerCount(pCount, cLen, playerStatus, cIdx);
    //��������ϵ��
    double dDeadK = 1.0 - (double(nSurvivePlayers) / double(pCount));
    //0.5ֵ�Ǿ���ֵ
    dRpn += (dDeadK * 0.5);

    //�����˵�����ʱ��,��̬�������С��0.7�Ҳ�ץ�ƣ����������ɲ�ȡ�ƣ�����ȡ����İ�ȫ
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
    initCardValueMap(mapCardValue);//ÿ�ֿ�ʼʱ����Ҫ��ʼ��
}

bool wannaCall(int pCount, int cLen, int cIdx, int* playerStatus)
{
    recalcCardValueMap(playerStatus, pCount, cLen, mapCardValue);

    bool bRet = false;
    //�ҵ��ܹ���ֵ
    double dMyTotal = getMyTotal();
    //��ǰץ�����ܴ�����ѧ����
    double dSurviveExp = getSurviveMathExp(dMyTotal);

    //�����������̬���ڷ���ϵ��
    double dRpn = getDynamicRPN(pCount, cLen, playerStatus, dSurviveExp, cIdx);
    //ʣ�����Խ�٣�ԽӦ�ñ���
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
    initCardValueMap(mapCardValue);//ÿ�ֿ�ʼʱ����Ҫ��ʼ��
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


