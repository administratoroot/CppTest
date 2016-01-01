#include <iostream>
using namespace std;
struct MyStruct
{
    int i : 2;
    int j : 3;
};

struct MyStruct1
{
    int i : 1;
    int j : 2;
};
int main()
{
    MyStruct my;
    my.i = 1;//0x00000001
    my.j = 3;//0x00000011
    MyStruct1 my1;
    my1.i = 1;//0x00000001
    my1.j = 7;//0x00000101
    system("pause");
    return 0;
}