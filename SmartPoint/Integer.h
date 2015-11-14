#pragma once
#include "Reference.h"
#include <iostream>
using namespace std;

class Integer :public ggp::CReferenced
{
public:
    Integer();
    Integer(int i);
    ~Integer();
    friend istream& operator>>(istream&, Integer&);
    friend ostream& operator<<(ostream&, const Integer&);

    int getValue();
    int getValue() const;
    void setValue(int i);
private:
    int m_i;
};
