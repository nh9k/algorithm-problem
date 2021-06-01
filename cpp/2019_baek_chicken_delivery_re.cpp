#include <iostream>
#include <vector>
using namespace std;

int n, m, result;
vector <pair<int, int>> chicken, house;
vector <int> select_c;

void dfs(int idx, int cnt)
{
	if (cnt == m)
	{
		int temp_result = 0;
		for (int hi = 0; hi < house.size(); ++hi)
		{
			int dist = 250;
			for (int si = 0; si < select_c.size(); ++si)
			{
				if (dist > abs(house[hi].first - chicken[select_c[si]].first) + abs(house[hi].second - chicken[select_c[si]].second))
				{
					dist = abs(house[hi].first - chicken[select_c[si]].first) + abs(house[hi].second - chicken[select_c[si]].second);
				}
			}
			temp_result += dist;
		}
		if (temp_result < result)
			result = temp_result;
		return;
	}
	for (int i = idx; i < chicken.size(); ++i)
	{
		select_c.push_back(i);
		dfs(i + 1, cnt + 1);
		select_c.pop_back();
	}
}

int main()
{
	cin >> n >> m;
	for (int ni = 0; ni < n; ++ni)
	{
		for (int nj = 0; nj < n; ++nj)
		{
			int temp;
			cin >> temp;
			if (temp == 1)
			{//Áý
				house.push_back({ ni,nj });
			}
			else if (temp == 2)
			{//Ä¡Å²
				chicken.push_back({ ni,nj });
			}
		}
	}

	result = 1e9;
	dfs(0, 0);
	cout << result;
}