#include "Integer.h"
Integer::Integer() :m_i(0)
{

}

Integer::Integer(int i) :m_i(i)
{

}

Integer::~Integer()
{
    cout << "destruction object,the value is" << m_i << endl;
}

int Integer::getValue()
{
    return m_i;
}

int Integer::getValue() const
{
    return m_i;
}

void Integer::setValue(int i)
{
    m_i = i;
}

istream& operator>>(istream& ins, Integer& i)
{
    ins >> i.m_i;
    return ins;
}

ostream& operator<<(ostream& os, const Integer&i)
{
    os << i.m_i;
    return os;
}