#include <iostream>
#include <vector>
using namespace std;

int n, min_wire, max_core, dx[4] = { -1,0,1,0 }, dy[4] = { 0,1,0,-1 };
bool map[12][12];
vector <pair<int, int>> core;

int set_wire(int x, int y, int dir) //연결 불가능: 0 , 연결 가능: 상수
{
	int mx = x, my = y, cnt = 0;
	while (1)
	{
		mx += dx[dir], my += dy[dir];
		if (mx < 0 || mx >= n || my < 0 || my >= n) return cnt; //범위 밖 == 도착
		else if (map[mx][my]) //이미 방문 == 실패
		{
			while (1)
			{
				mx -= dx[dir], my -= dy[dir];
				if (mx == x && my == y) return 0;
				map[mx][my] = false;
			}
		}
		else //계속 시도
		{
			++cnt;
			map[mx][my] = true;
		}
	}
}

void reset_wire(int x, int y, int dir)
{
	int mx = x, my = y;
	while (1)
	{
		mx += dx[dir], my += dy[dir];
		if (mx < 0 || mx >= n || my < 0 || my >= n) return;
		map[mx][my] = false;
	}
}

void dfs(int idx, int core_cnt, int wire_cnt)
{
	if (core_cnt + (core.size() - idx) < max_core) return;
	if (idx == core.size())
	{
		if (core_cnt >= max_core)
		{
			if (core_cnt == max_core)
			{
				if (min_wire > wire_cnt)
					min_wire = wire_cnt;
			}
			else
			{
				max_core = core_cnt;
				min_wire = wire_cnt;
			}
		}
		return;
	}
	for (int m = 0; m < 5; ++m)
	{
		if (m == 4) 
		{
			dfs(idx + 1, core_cnt, wire_cnt);
		}
		else
		{
			int temp = set_wire(core[idx].first, core[idx].second, m);
			if (temp)
			{
				dfs(idx + 1, core_cnt + 1, wire_cnt + temp);
				reset_wire(core[idx].first, core[idx].second, m);
			}
			else //이 방향 연결 불가
			{
				continue;
			}
		}
	}
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	int t;
	cin >> t;
	for (int ti = 0; ti < t; ++ti)
	{
		cin >> n;
		for (int ni = 0; ni < n; ++ni)
		{
			for (int nj = 0; nj < n; ++nj)
			{
				cin >> map[ni][nj];
				if (map[ni][nj] == 1 && !(ni == 0 || ni == n - 1 || nj == 0 || nj == n - 1))
				{
					core.push_back({ ni,nj });
				}
			}
		}
		max_core = 0, min_wire = 200;
		dfs(0, 0, 0);
		cout << "#" << ti + 1 << " " << min_wire << endl;
		core.clear();
	}
	return 0;
}