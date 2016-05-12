#include "ClassB.h"
#include "ClassA.h"

ClassB::ClassB() :m_pClassA(new ClassA(0))
{

}


ClassB::ClassB(int i) :m_pClassA(new ClassA(i))
{

}

ClassB::~ClassB()
{
}
