#include <iostream>
#include <queue>
using namespace std;

int n, m, map[8][8], zero_sz, max_safe_zone, vi_sz, mx[4] = { -1,0,1,0 }, my[4] = {0,1,0,-1};
bool visit[8][8];
typedef struct {
	int x, y;
}VIRUS;
VIRUS v_first[10];

void spread()
{
	queue <VIRUS> v;

	for(int vi=0; vi<vi_sz; ++vi)
		v.push({ v_first[vi].x,v_first[vi].y });

	int cnt = zero_sz - 3;

	while (!v.empty())
	{
		for (int mov = 0; mov < 4; ++mov)
		{
			int dx = v.front().x + mx[mov], dy = v.front().y + my[mov];

			if (dx < 0 || dx >= n || dy < 0 || dy >= m) continue; //범위 밖
			else if (visit[dx][dy]) continue; //이미 방문
			else if (map[dx][dy]==1  || map[dx][dy]==2) continue; //벽이거나 바이러스

			v.push({ dx,dy });
			visit[dx][dy] = true;
			cnt--;
		}
		if (cnt < max_safe_zone) //이미 더 많이 퍼진 경우
			return;
		v.pop();
	}
	//for (int ni = 0; ni < n; ++ni)
	//{
	//	for (int mi = 0; mi < m; ++mi)
	//	{
	//		cout << visit[ni][mi];
	//	}cout << endl;
	//}cout << endl;
	//cout << cnt << endl;
	if (cnt > max_safe_zone)
		max_safe_zone = cnt;

	return;
}

void dfs(int n_idx, int m_idx, int cnt)
{
	if (cnt == 3)
	{
		/*for (int ni = 0; ni < n; ++ni)
		{
			for (int mi = 0; mi < m; ++mi)
			{
				cout << map[ni][mi];
			}cout << endl;
		}cout << endl;*/
		spread();

		for (int ni = 0; ni < n; ++ni)
			for (int mi = 0; mi < m; ++mi)
				visit[ni][mi] = false;
	
		return;
	}
	for (int ni = n_idx; ni < n; ++ni)
	{
		for (int mi = m_idx; mi < m; ++mi)
		{
			if (map[ni][mi] == 1 || map[ni][mi] == 2) continue; //벽이거나 바이러스
			map[ni][mi] = 1;
			dfs(ni, mi + 1, cnt + 1);
			map[ni][mi] = 0;
		}
		m_idx = 0;
	}
}

int main()
{
	cin >> n >> m;
	zero_sz = 0;
	vi_sz = 0;
	for (int ni = 0; ni < n; ++ni)
	{
		for (int mi = 0; mi < m; ++mi)
		{
			cin >> map[ni][mi];
			if (map[ni][mi] == 2) {
				v_first[vi_sz].x = ni, v_first[vi_sz].y = mi;
				vi_sz++;
			}
			else if (map[ni][mi] == 0) zero_sz++;
		}
	}

	max_safe_zone = 0;
	dfs(0, 0, 0);
	cout << max_safe_zone;
	return 0;
}