#include <iostream>
#include "scopeguard.h"
using namespace std;
int main()
{
    for (int i = 0; i < 10; ++i)
    {
		return 0;
        SCOPE_EXIT
        {
            cout << "helloworld!" << endl;
        };
        cout << i<<endl;
    }
    
    system("pause");
    return 0;
}