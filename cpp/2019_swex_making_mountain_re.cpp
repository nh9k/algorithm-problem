#include <iostream>
#include <vector>
using namespace std;

int n, k, map[8][8], visit[8][8], max_leng, dx[4] = { -1,0,1,0 }, dy[4] = {0,1,0,-1};
typedef struct {
	int x, y;
}MOUNTAIN;
vector <MOUNTAIN> m;

void dfs(int leng, bool one_chance, int x, int y)
{
	if (max_leng < leng)
	{
		max_leng = leng;
	}
	for (int d = 0; d < 4; ++d)
	{
		int mx = x + dx[d], my = y + dy[d];

		if (mx < 0 || mx >= n || my < 0 || my >= n) continue; //배열 밖
		else if (visit[mx][my]) continue; //이미 방문한 곳
		else if (map[mx][my] >= map[x][y]) //갈 수 없으니 깎아야함
		{
			if (one_chance) continue; //이미 깎았으면 못감
			for (int ki = 1; ki <= k; ++ki)
			{
				if (map[mx][my] - ki >= map[x][y]) continue; //깎아도 못가는 곳

				map[mx][my] -= ki;
				visit[mx][my] = true;
				dfs(leng + 1, true, mx, my);
				map[mx][my] += ki;
				visit[mx][my] = false;
				break; //한번 깎아서 갈 수 있으면, 그 이상은 깎을 필요없음
			}
			//아무리 깎아도 갈 수 없으면 다음 방향, 깎은 다음 돌아와도 다음 방향 검사.
		}
		else //갈 수 있음
		{
			visit[mx][my] = true;
			dfs(leng + 1, one_chance, mx, my);
			visit[mx][my] = false;
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
		cin >> n >> k;
		int temp_max = 0;
		for (int ni = 0; ni < n; ++ni)
		{
			for (int nj = 0; nj < n; ++nj)
			{
				cin >> map[ni][nj];
				if (map[ni][nj] > temp_max)
					temp_max = map[ni][nj];
			}
		}

		for (int ni = 0; ni < n; ++ni)
			for (int nj = 0; nj < n; ++nj)
				if (map[ni][nj] == temp_max)
					m.push_back({ ni,nj }); //최대 지형 삽입

		max_leng = -1;
		for (auto mi = m.begin(); mi != m.end(); ++mi)
		{
			visit[(*mi).x][(*mi).y] = true;
			dfs(1, false, (*mi).x, (*mi).y);
			visit[(*mi).x][(*mi).y] = false;
		}
		cout << "#" << ti + 1 << " " << max_leng << endl;
		m.clear();
	}

	return 0;
}