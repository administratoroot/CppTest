#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
bool cmp(int a, int b)
{
	return a < b;
}
int main()
{
	vector<int> vi;
	vi.push_back(2);
	vi.push_back(1);
	vi.push_back(5);
	vi.push_back(3);
	vi.push_back(4);
	sort(vi.begin(), vi.end(), cmp);
	for each(int i in vi)
	{
		cout << i << " ";
	}
	system("pause");
	return 0;
}