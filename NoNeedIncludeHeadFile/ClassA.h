#pragma once

class ClassA
{
public:
    ClassA();
    ClassA(int i);
    ~ClassA();
    int getA() const { return m_a; }
    void setA(int val) { m_a = val; }
private:
    int m_a;
};

