#include <iostream>
#include <queue>
using namespace std;

int n, m, t, map[50][50], cnt, dx[4] = { -1,0,1,0 }, dy[4] = { 0,1,0,-1 }, cross[4] = {2,3,0,1};
bool visit[50][50], tunnel[8][4] = { { 0,0,0,0}, {1,1,1,1},{1,0,1,0},{0,1,0,1}
									,{1,1,0,0},{0,1,1,0},{0,0,1,1},{1,0,0,1} };
queue <pair<int, int>> pos;

void search_map()
{
	for (int ti = 1; ti < t; ++ti)
	{
		int qsz = pos.size();
		for (int sz = 0; sz < qsz; ++sz)
		{
			for (int mi = 0; mi < 4; ++mi)
			{
				if (tunnel[map[pos.front().first][pos.front().second]][mi] == false) continue;

				int mx = pos.front().first + dx[mi], my = pos.front().second + dy[mi];
				if (mx < 0 || mx >= n || my < 0 || my >= m) continue;
				else if (visit[mx][my] || map[mx][my] == 0) continue;
				else if (tunnel[map[mx][my]][cross[mi]] == false) continue;
				
				pos.push({ mx,my });
				visit[mx][my] = true;
				cnt++;
			}
			pos.pop();
		}
	}
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	int T;
	cin >> T;
	for (int ti = 0; ti < T; ++ti)
	{
		int r, c;
		cin >> n >> m >> r >> c >> t;
		for (int ni = 0; ni < n; ++ni)
		{
			for (int mi = 0; mi < m; ++mi)
			{
				cin >> map[ni][mi];
			}
		}
		//if (t == 1)
		//{
		//	cnt = 1;
		//	cout << "#" << ti + 1 << " " << cnt << endl;
		//	return 0; //리턴 제로하면 안되고 if else문으로 처리해야 함.
		//}
		for (int ni = 0; ni < n; ++ni)
			for (int mi = 0; mi < m; ++mi)
				visit[ni][mi] = 0;

		while (!pos.empty())
			pos.pop();

		pos.push({ r,c });
		cnt = 0;

		search_map();
		if(cnt==0)//이걸 t==1로 미리 검사하면 조금더 시간 빨라짐
			cout << "#" << ti + 1 << " " << 1 << endl;
		else
			cout << "#" << ti + 1 << " " << cnt << endl;
	}
	return 0;
}