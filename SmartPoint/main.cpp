#include <iostream>
#include "RefPtr.h"
#include "Integer.h"
using namespace ggp;
using namespace std;
typedef CRefPtr<Integer> IntPtr;

void test1(Integer* i)
{
    cout << "end test1" << endl;
    return;
}
void test2(Integer* i, Integer* j)
{
    cout << "end test2" << endl;
    return;
}
void test()
{
    IntPtr p1 = new Integer(1);
    IntPtr p2 = new Integer(2);
    return;
}
int main()
{
    test();
    //test1(IntPtr(new Integer(1)).get());
    //test2(IntPtr(new Integer(2)).get(), IntPtr(new Integer(3)).get());
    system("pause");
    return 0;
}