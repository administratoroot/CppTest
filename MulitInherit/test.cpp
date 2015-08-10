#include <iostream>
using namespace std;
class Father
{
public:
    Father(){};
    virtual ~Father(){};
    virtual void println()
    {
        cout << "Father" << endl;
    }
};

class Son1 : public Father
{
public:
    Son1(){};
    ~Son1(){};
    virtual void println()
    {
        cout << "Son1" << endl;
    }
    virtual void println2()
    {
        cout << "Son1print2" << endl;
    }
private:

};

class Son2 : public Father
{
public:
    Son2(){};
    ~Son2(){};
    virtual void println()
    {
        cout << "Son2" << endl;
    }
private:

};

class GrandSon : public Son1,public Son2
{
public:
    GrandSon(){};
    ~GrandSon(){};
    //virtual void println()
    //{
    //    cout << "grandson" << endl;
    //}
private:

};
int main()
{
    Father f;
    f.println();
    Son1 s1;
    s1.println();
    Son2 s2;
    s2.println();
    GrandSon gs;
    gs.println2();
    system("pause");
    return 0;
}