//https://swjeong.tistory.com/77
//http://blog.naver.com/PostView.nhn?blogId=withham1&logNo=221365222338&parentCategoryNo=&categoryNo=&viewDate=&isShowPopularPosts=false&from=postView
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

bool cmp(pair<int, int> &a, pair<int, int> &b)
{
	return a.second < b.second;
}

int solution(vector<int> food_times, long long k) {
	vector <pair<int, int>> food;
	for (int i = 0; i < food_times.size(); i++)
		food.push_back({ food_times[i], i + 1 });

	sort(food.begin(), food.end()); //음식값 기준 정렬
	int vsz = food.size();
	int mem = 0;
	for (auto iter = food.begin(); iter != food.end(); iter++, vsz--)
	{
		long long min_value = (long long)((*iter).first - mem)*vsz;
		if ((*iter).first == mem)
			continue;

		if (min_value <= k)//=인거 조심!
		{
			k -= min_value;
			mem = (*iter).first;
		}
		else //남은 것 중에 답이 있다
		{
			k %= vsz;
			sort(iter, food.end(), cmp);
			return (*(iter + k)).second;
		}
	}
	return -1;
}

int main()
{
	//cout << solution({ 3,1,2 }, 5) << endl;
	cout << solution({ 4,3,2 }, 5) << endl;
	//cout << solution({ 2,3 }, 9) << endl;
}