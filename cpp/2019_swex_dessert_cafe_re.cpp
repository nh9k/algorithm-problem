#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, map[20][20], dx[4] = { 1,1,-1,-1 }, dy[4] = { 1,-1,-1,1 }, candir[4] = {1,2,3,3}, firstx, firsty, max_result;
bool visit[20][20];
vector <int> dessert;

void dfs(int dir, int x, int y)
{
	if (x == firstx && y == firsty && dessert.size() > 1)
	{
		int vsz = dessert.size();
		max_result = max(max_result, vsz);
		return;
	}
	for (int m = dir; m <= candir[dir]; ++m)
	{
		int mx = x + dx[m], my = y + dy[m];
		if (mx < 0 || mx >= n || my < 0 || my >= n) continue;
		//else if (visit[mx][my]) continue;
		else if (mx == firstx && my == firsty)
		{
			dfs(m, mx, my);
		}
		else
		{
			bool chk = true;
			for (int d = 0; d < dessert.size(); ++d) //µµÂøÁ¡ Á¦¿Ü
			{
				if (map[mx][my] == dessert[d]) {
					chk = false;
					break;
				}
			}
			if (chk == false) continue;

			//visit[mx][my] = true;
			dessert.push_back(map[mx][my]);
			dfs(m, mx, my);
			//visit[mx][my] = false;
			dessert.pop_back();
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
			}
		}

		max_result = 0;
		for (int ni = 0; ni < n - 2; ++ni)
		{
			for (int nj = 1; nj < n - 1; ++nj)
			{
				firstx = ni, firsty = nj;
				dessert.push_back(map[ni][nj]);
				dfs(0, ni, nj);
				dessert.clear();
			}
		}
		if (max_result == 0)
			cout << "#" << ti + 1 << " " << -1 << endl;
		else
			cout << "#" << ti + 1 << " " << max_result << endl;
	}
	return 0;
}