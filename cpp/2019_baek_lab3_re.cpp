#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, m, map[50][50], zero_cnt, min_time, dx[4] = { -1,0,1,0 }, dy[4] = { 0,1,0,-1 };
bool visit[50][50];
vector <pair<int, int>> virus;
vector <int> vidx;

int simulation()
{
	queue <pair<int, int>> simul;
	for (int i = 0; i < vidx.size(); ++i)
	{
		simul.push({ virus[vidx[i]].first,virus[vidx[i]].second });
	}

	int mx, my, zcnt = 0, t = 0;
	while (1)
	{
		if (!simul.empty())
		{
			int qsz = simul.size();
			for (int i = 0; i < qsz; ++i)
			{
				if (visit[simul.front().first][simul.front().second]) {
					simul.pop();
					continue;
				}
				else if (map[simul.front().first][simul.front().second] == 0) ++zcnt;
				if (zcnt == zero_cnt) return t;
				visit[simul.front().first][simul.front().second] = true;

				for (int m = 0; m < 4; ++m)
				{
					mx = simul.front().first + dx[m], my = simul.front().second + dy[m];
					if (mx < 0 || my < 0 || mx >= n || my >= n) continue;
					else if (map[mx][my] == 1) continue;
					
					simul.push({ mx, my });
				}
				simul.pop();
			}
			++t;
		}
		else break;	
		if (t > min_time) break;
	}
	
	return min_time;
}

void dfs(int idx)
{
	if (vidx.size() == m)
	{
		int temp = simulation();
		if (temp < min_time)
			min_time = temp;

		for (int ni = 0; ni < n; ++ni)
		{
			for (int nj = 0; nj < n; ++nj)
			{
				visit[ni][nj] = false;
			}
		}
		return;
	}
	for (int i = idx; i < virus.size(); ++i)
	{
		vidx.push_back(i);
		dfs(i + 1);
		vidx.pop_back();
	}
}

int main()
{
	cin >> n >> m;
	for (int ni = 0; ni < n; ++ni)
	{
		for (int nj = 0; nj < n; ++nj)
		{
			cin >> map[ni][nj];
			if (map[ni][nj] == 0)
			{
				++zero_cnt;
			}
			else if (map[ni][nj] == 2)
			{
				virus.push_back({ ni,nj });
			}
		}
	}
	min_time = 1e9;
	dfs(0);
	if(min_time == 1e9) cout << -1;
	else cout << min_time;
}