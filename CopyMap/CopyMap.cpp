#include <iostream>
#include <map>
using namespace std;
class TestMap
{
public:
	void setMap(map<int, int> newMap);
	map<int, int> getMap();
private:
	map<int, int> m_map;
};

void TestMap::setMap(map<int, int> newMap)
{
	//m_map.clear();
	m_map = newMap;
}

map<int, int> TestMap::getMap()
{
	return m_map;
}

int main()
{
	TestMap testMap;
	map<int, int> myMap;
	myMap.insert(std::make_pair(2, 4));
	myMap.insert(std::make_pair(6, 8));
	testMap.setMap(myMap);
	myMap.clear();
	myMap.insert(std::make_pair(1, 3));
	myMap.insert(std::make_pair(5, 7));
	testMap.setMap(myMap);
	myMap.clear();
	testMap.getMap();
	system("pause");
	return 0;
}