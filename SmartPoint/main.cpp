#include <iostream>
#include "RefPtr.h"
#include "Integer.h"
using namespace ggp;
using namespace std;
typedef CRefPtr<Integer> IntPtr;

void test1(Integer* i)
{
    IntPtr p1 = i;
}

int main()
{
    Integer *i = new Integer(8); 
    IntPtr p1 = i;
    test1(p1.get());
    cout << *i << endl;
    
    system("pause");
    return 0;
}