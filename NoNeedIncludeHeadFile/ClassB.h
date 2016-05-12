#pragma once
class ClassA;
class ClassB
{
public:
    ClassB();
    ClassB(int i);
    ~ClassB();
    ClassA* getClassA() const { return m_pClassA; }
    void setClassA(ClassA* val) { m_pClassA = val; }
private:
    ClassA* m_pClassA;
};
