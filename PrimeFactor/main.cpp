#include <iostream>
#include <vector>
#include "gtest/gtest.h"
using namespace std;
#if 1
int deCompose(int n, vector<int>& vecPrimer)
{
    for (int i = 2; i < n; ++i)
    {
        if ((n % i) == 0)
        {
            if (!vecPrimer.empty())
            {
                vecPrimer.pop_back();
            }
            vecPrimer.push_back(i);
            vecPrimer.push_back(n / i);
            return deCompose(n / i, vecPrimer);
        }
    } 
    if (vecPrimer.empty() && n > 1)
    {
        vecPrimer.push_back(n);
    }
}

vector<int> PrimerFactor(int n)
{
    vector<int> vecPrimer;
    deCompose(n, vecPrimer);
    return vecPrimer;
}

//int main()
//{
//    int n;
//    cin >> n;
//    vector<int> vecPrimer;
//    deCompose(n, vecPrimer);
//    for (auto it = vecPrimer.begin(); it != vecPrimer.end(); ++it)
//    {
//        cout << *it << " ";
//    }
//    system("pause");
//    return 0;
//}
#else
vector<int> PrimerFactor(int n)
{
    vector<int> vecRet;
    int nFactor = 2;
    if (n % nFactor == 0)
    {
        vecRet.push_back(nFactor);
        while (n > 2)
        {
            n = n / nFactor;
            if (n % nFactor == 0)
            {
                vecRet.push_back(nFactor);
            }
            else
            {
                if (n >= 2)
                {
                    vecRet.push_back(n);
                }
            }
        }
    }
    else
    {
        return vector<int>{n};
    }

    return vecRet;
}
#endif

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    system("pause");
    return 0;
}

TEST(primeFactor, i2r2)
{
    vector<int> ret{ 2 };
    EXPECT_EQ(ret, PrimerFactor(2));
}
TEST(primeFactor, i3r3)
{
    vector<int> ret{ 3 };
    EXPECT_EQ(ret, PrimerFactor(3));
}
TEST(primeFactor, i4r2_2)
{
    vector<int> ret{ 2, 2 };
    EXPECT_EQ(ret, PrimerFactor(4));
}
TEST(primeFactor, i6r2_3)
{
    vector<int> ret{ 2, 3 };
    EXPECT_EQ(ret, PrimerFactor(6));
}
TEST(primeFactor, i8r2_2_2)
{
    vector<int> ret{ 2, 2, 2 };
    EXPECT_EQ(ret, PrimerFactor(8));
}
TEST(primeFactor, i16r2_2_2_2)
{
    vector<int> ret{ 2, 2, 2,2 };
    EXPECT_EQ(ret, PrimerFactor(16));
}

TEST(primeFactor, i9r3_3)
{
    vector<int> ret{ 3, 3};
    EXPECT_EQ(ret, PrimerFactor(9));
}