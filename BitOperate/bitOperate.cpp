#include <iostream>
using namespace std;
int main()
{
	int i = 5;//101
	int j = 2;//010
	int k = 6;//110
	cout << "(i&j)" << (i & j) << endl;//0
	cout << "(i|j)" << (i | j) << endl;//111
	cout << "(i^j)" << (i ^ j) << endl;//111
	cout << "(i^k)" << (i ^ k) << endl;//011
	cout << "(~i)" << (~i) << endl;//

    cout << hex << i << endl;
    cout << hex << ~i + 1 << " " << -i << endl;
	system("pause");
	return 0;
}