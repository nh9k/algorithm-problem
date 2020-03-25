#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

bool cmp(const pair<float, int>& a,const pair<float, int>& b)
{
	if (a.first == b.first)
		return a.second < b.second;
	return a.first > b.first;
}

vector<int> solution(int N, vector<int> stages) {
	int p[501] = { 0, };
	int person_num = stages.size();
	for (int i = 0; i < person_num; i++)
		p[stages[i]]++;

	float fail = 0;
	int no = 0;
	vector <pair<float, int>> sorting;
	for (int i = 1; i < N+1; i++)
	{
		if (person_num - no == 0) fail = 0;
		else fail = (float)p[i] / (float)(person_num - no);
		no += p[i];

		sorting.push_back({ fail, i });
		//if (i == 1) {
		//	sorting.push_back({ fail, i });
		//	continue;
		//}

		//for (auto j = sorting.begin(); j != sorting.end(); j++)
		//{
		//	if ((*j).first < fail)
		//	{
		//		//sorting.push_back({fail[i], i});
		//		//break;
		//		sorting.insert(j, { fail, i });
		//		break;
		//	}
		//	else if ((*j).first == fail)
		//	{
		//		if ((*j).second > i) {
		//			sorting.insert(j, { fail, i });
		//			break;
		//		}
		//		else if (j == sorting.end() - 1) {
		//			sorting.insert(j + 1, { fail, i });
		//			break;
		//		}
		//		else
		//			continue;

		//	}
		//	else
		//	{
		//		if (j == sorting.end() - 1) {
		//			sorting.insert(j + 1, { fail, i });
		//			break;
		//		}
		//		else
		//			continue;
		//	}
		//}

	}
	sort(sorting.begin(), sorting.end(), cmp);

	vector<int> answer;
	for (auto i = sorting.begin(); i != sorting.end(); i++) {
		answer.push_back((*i).second);
		cout << (*i).second << endl;
	}
	return answer;
}

int main()
{
	solution(5, { 2,1,2,6,2,4,3,3 });
	solution(4, { 4,4,4,4,4 });
}