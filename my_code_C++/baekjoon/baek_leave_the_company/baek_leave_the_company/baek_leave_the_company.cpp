#include <iostream>
using namespace std;

int n, max_sum;
typedef struct {
	int consume, cost;
}CONSULTING;
CONSULTING day[15];
//bool visit[15];

//오히려 함수 인자들을 줄여라!
void dfs(int idx, int temp_sum, int present)
{
	if (idx >= n) {
		if (idx != n) {
			temp_sum -= present;
		}
		if (max_sum < temp_sum)
			max_sum = temp_sum;

		return;
	}
	for (int i = idx; i < n; ++i)
	{
		dfs(i + day[i].consume, temp_sum + day[i].cost, day[i].cost);
	}
}

int main()
{
	cin >> n;
	for (int ni = 0; ni < n; ++ni)
	{
		cin >> day[ni].consume >> day[ni].cost;
	}
	max_sum = 0;
	dfs(0, 0, 0);
	cout << max_sum;
	return 0;
}