#include <iostream>
#include <vector>
using namespace std;

int map[20][20], n, max_result;

void moving_dir(int dir)
{
	if (dir == 0)
	{//up
		for (int nj = 0; nj < n; ++nj)
		{
			vector <pair<int, int>> line;
			for (int ni = 0; ni < n; ++ni)
			{
				if (map[ni][nj]==0) continue;
				if (!line.empty())
				{
					if (line.back().first == map[ni][nj] && line.back().second == 0)
					{
						line.back().first += map[ni][nj];
						line.back().second = 1;
					}	
					else
						line.push_back({ map[ni][nj],0 });
				}
				else
					line.push_back({ map[ni][nj],0 });
				map[ni][nj] = 0;
			}
			for (int ni = 0; ni < line.size(); ++ni)
			{
				map[ni][nj] = line[ni].first;
			}
		}
	}
	else if(dir == 1)
	{//down
		for (int nj = 0; nj < n; ++nj)
		{
			vector <pair<int, int>> line;
			for (int ni = n-1; ni >= 0; --ni)
			{
				if (map[ni][nj]==0) continue;
				if (!line.empty())
				{
					if (line.back().first == map[ni][nj] && line.back().second == 0)
					{
						line.back().first += map[ni][nj];
						line.back().second = 1;
					}
					else
						line.push_back({ map[ni][nj],0 });
				}
				else
					line.push_back({ map[ni][nj],0 });
				map[ni][nj] = 0;
			}
			for (int ni = 0; ni <line.size(); ++ni)
			{
				map[n-1-ni][nj] = line[ni].first;
			}
		}
	}
	else if (dir == 2)
	{//left
		for (int ni = 0; ni < n; ++ni)
		{
			vector <pair<int, int>> line;
			for (int nj = 0; nj < n; ++nj)
			{
				if (map[ni][nj]==0) continue;
				if (!line.empty())
				{
					if (line.back().first == map[ni][nj] && line.back().second == 0)
					{
						line.back().first += map[ni][nj];
						line.back().second = 1;
					}
					else
						line.push_back({ map[ni][nj],0 });
				}
				else
					line.push_back({ map[ni][nj],0 });
				map[ni][nj] = 0;
			}
			for (int nj = 0; nj < line.size(); ++nj)
			{
				map[ni][nj] = line[nj].first;
			}
		}
	}
	else
	{//right
		for (int ni = 0; ni < n; ++ni)
		{
			vector <pair<int, int>> line;
			for (int nj = n-1; nj >= 0; --nj)
			{
				if (map[ni][nj]==0) continue;
				if (!line.empty())
				{
					if (line.back().first == map[ni][nj] && line.back().second == 0)
					{
						line.back().first += map[ni][nj];
						line.back().second = 1;
					}
					else
						line.push_back({ map[ni][nj],0 });
				}
				else
					line.push_back({ map[ni][nj],0 });
				map[ni][nj] = 0;
			}
			for (int nj = 0; nj <line.size(); ++nj)
			{
				map[ni][n-1-nj] = line[nj].first;
			}
		}
	}
}

void dfs(int cnt, int no)
{
	if (cnt == 5)
	{
		for (int ni = 0; ni < n; ++ni)
		{
			for (int nj = 0; nj < n; ++nj)
			{
				if (max_result < map[ni][nj])
					max_result = map[ni][nj];
			}
		}
		return;
	}
	for (int m = 0; m < 4; ++m)
	{
		if (no == m) continue;

		int cpy[20][20];
		for (int ni = 0; ni < n; ++ni)
			for (int nj = 0; nj < n; ++nj)
				cpy[ni][nj] = map[ni][nj];

		moving_dir(m);
		dfs(cnt + 1, m);

		for (int ni = 0; ni < n; ++ni)
			for (int nj = 0; nj < n; ++nj)
				map[ni][nj] = cpy[ni][nj];
	}
}

int main()
{
	cin >> n;
	for (int ni = 0; ni < n; ++ni)
	{
		for (int nj = 0; nj < n; ++nj)
		{
			cin >> map[ni][nj];
		}
	}
  	dfs(0,4);
	cout << max_result;
}