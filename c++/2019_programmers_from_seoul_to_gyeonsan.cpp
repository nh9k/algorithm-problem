#include <string>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;
typedef struct {
	int time, money;
}T;

int solution(int K, vector<vector<int>> travel) {
	queue <T>  trav;
	trav.push({ travel[0][0],travel[0][1] });
	trav.push({ travel[0][2],travel[0][3] });
	int answer = 0;

	for (int sz = 1; sz < travel.size(); ++sz)
	{
		int qsz = trav.size();
		for (int i = 0; i < qsz; ++i)
		{
			for (int case_ = 0; case_ < 3; case_ += 2) {
				if (trav.front().time + travel[sz][case_] <= K) {
					trav.push({ trav.front().time + travel[sz][case_], trav.front().money + travel[sz][case_ + 1] });
					answer = max(answer, trav.front().money + travel[sz][case_ + 1]);
				}
					
			}
			trav.pop();
		}
	}

	//
	//while (!trav.empty())
	//{
	//	if (answer < trav.front().money)
	//		answer = trav.front().money;
	//	trav.pop();
	//}

	return answer;
}


int main()
{
	cout << solution(1650, { {500, 200, 200, 100},{800, 370, 300, 120},{700, 250, 300, 90} });
}
