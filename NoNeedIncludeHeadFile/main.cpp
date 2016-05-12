#include <iostream>
#include "ClassB.h"
#include "ClassA.h"
int main()
{
    ClassB* pB = new ClassB(1000);
    ClassA* pA = pB->getClassA();
    std::cout << pA->getA() << std::endl;
    system("pause");
    return 0;
}