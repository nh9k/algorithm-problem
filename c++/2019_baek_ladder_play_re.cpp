#include <iostream>
using namespace std;

bool map[30][10];
int n, h, m, min_result; //세로개수, 선개수, 가로개수

bool chk_ladder()
{	
	for (int ncnt = 0; ncnt < n; ++ncnt)
	{
		int ni = ncnt;
		for (int mi = 0; mi < m; ++mi)
		{
			if (map[mi][ni]) ni++;
			else if (ni != 0)
			{
				if (map[mi][ni - 1]) ni--;
			}
		}
		if (ni != ncnt) return false;
	}
	return true;
}

void dfs(int m_idx, int n_idx, int cnt)
{
	if (cnt > 3) return;
	else if (min_result < cnt) return;
	else if (chk_ladder())
	{
		if (min_result > cnt)
			min_result = cnt;
		return;
	}


	for (int mi = m_idx; mi < m; ++mi)
	{
		for (int ni = n_idx; ni < n-1; ++ni)
		{
			if (ni == 0)
			{
				if (map[mi][ni] || map[mi][ni + 1]) continue;
			}
			else if (ni == n - 2)
			{
				if (map[mi][ni] || map[mi][ni - 1]) continue;
			}
			else
			{
				if (map[mi][ni] || map[mi][ni - 1] || map[mi][ni + 1]) continue;
			}
			map[mi][ni] = true;
			dfs(mi, ni + 1, cnt + 1);
			map[mi][ni] = false;
		}
		n_idx = 0;
	}
}

int main()
{
	cin >> n >> h >> m;
	int temp_m, temp_n;
	for (int hi = 0; hi < h; ++hi)
	{
		cin >> temp_m >> temp_n;
		map[temp_m - 1][temp_n - 1] = true;
	}

	min_result = 4;
	dfs(0, 0, 0);
	if(min_result == 4) cout << -1;
	else cout << min_result;

	return 0;
} 