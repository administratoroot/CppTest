#include <iostream>
#include "VersionUtil.h"
using namespace std;
int main()
{
    GTJCouldVersionUtil::EnResult result = GTJCouldVersionUtil::compareVersion("1.0.0.1", "1.0.0.1");
    cout << result << endl;
    system("pause");
    return 0;
}