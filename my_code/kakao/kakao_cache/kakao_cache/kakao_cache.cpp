#include <string>
#include <vector>
#include <queue>
//#include <algorithm>
#include <cstring>
//#include <iostream>
using namespace std;

#define MISS 5
#define HIT 1

//bool comp(pair<int, string> a, pair<int, string> b)
//{ //https://hsdevelopment.tistory.com/151
//	return a.first < b.first; //오름차순
//}

int solution(int cacheSize, vector<string> cities) {
	int extime = 0;
	int vsz = cities.size();
	//vector <pair<int, string>> pv;
	vector <string> pv;
	if (cacheSize == 0)
	{
		return MISS * cities.size();
	}
	for (int i = 0; i < vsz; i++)
	{
		for (int leng = 0; leng < cities[i].size(); leng++)
			cities[i][leng] = toupper(cities[i][leng]);

		if (pv.empty()) { //처음 삽입
			//pv.push_back({ 1, cities[i] });
			pv.push_back({ cities[i] });
			extime += MISS;
		}
		else //두번째이상 삽입
		{
			bool ismiss = false;
			int temp = 0;
			for (int j = 0; j < pv.size(); j++)
			{
				if (ismiss == true) break;
				if (!(pv[j].compare(cities[i]))) //같은 이름을 찾으면(대소문자 무시)
				{
					ismiss = true;
					//temp = pv[j].first;
					pv.erase(pv.begin()+j);
					extime += HIT;
					break;
				}
			}
			if (!ismiss) //같은 이름을 찾지 못한 경우
			{
				if (pv.size() >= cacheSize) pv.erase(pv.begin()); //캐시사이즈보다 크면 가장 적은 것 삭제
				//pv.push_back({ 1, cities[i] });
				pv.push_back({ cities[i] });
				extime += MISS;
			}
			else
			{
				pv.push_back({ cities[i] });
				//pv.push_back({ temp + 1,cities[i] });
				//	sort(pv.begin(), pv.end(), comp);
			}
			
		}
	}
	//int answer = 0;
	return extime;
}
int main()
{
	cout << solution(3, { "Jeju", "Pangyo", "NewYork", "newyork" ,"newyork"}) <<endl;
	cout << solution(2, { "Jeju", "Pangyo", "Seoul", "Jeju", "Pangyo", "Seoul", "Jeju", "Pangyo", "Seoul" }) << endl;
	return 0;
}