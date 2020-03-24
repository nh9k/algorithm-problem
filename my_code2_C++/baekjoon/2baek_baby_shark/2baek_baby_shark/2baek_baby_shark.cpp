#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int n, map[20][20], dx[4] = { -1,0,1,0 }, dy[4] = {0,1,0,-1}, visit[20][20];;
typedef struct {
	int x, y;
}F;
typedef struct {
	int x, y, cnt, age;
}S;
S s;
vector <F> f;


int bfs()
{
	queue <pair<int, int>> p;
	p.push({ s.x, s.y });
	visit[s.x][s.y] = true;

	int result = 0;
	while (!p.empty())
	{
		int t = 1;
		while (!p.empty())
		{
			int psz = p.size();
			for (int q = 0; q < psz; ++q)
			{
				for (int m = 0; m < 4; ++m)
				{
					int mx = p.front().first + dx[m], my = p.front().second + dy[m];
					if (mx < 0 || my < 0 || mx >= n || my >= n || visit[mx][my] || map[mx][my] > s.age) continue;

					p.push({ mx,my });
					visit[mx][my] = t;
					if (map[mx][my] < s.age && map[mx][my] != 0) //���̺��� �۰� ��ĭ�� �ƴϿ�����
					{
						f.push_back({ mx, my });
					}
				}
				p.pop();
			}
			if (!f.empty()) break;
			t++;
		}


		if (!f.empty())
		{
			int min_x = 20, min_xy = 20, min_idx;
			for (int fi = 0; fi < f.size(); ++fi)
			{
				if (min_x >= f[fi].x)
				{			
					if (min_x > f[fi].x)
					{
						min_x = f[fi].x;
						min_xy = f[fi].y;
						min_idx = fi;
					}
					else if (min_xy > f[fi].y)
					{
						min_x = f[fi].x;
						min_xy = f[fi].y;
						min_idx = fi;
					}
				}
			}

			s.cnt++;
			if (s.cnt == s.age)
			{
				s.age++; //��� ���� ����
				s.cnt = 0;
			}
			s.x = f[min_idx].x, s.y = f[min_idx].y; //��� ��ġ ����
			map[f[min_idx].x][f[min_idx].y] = 0; //����� ���� �� map ����
			result += visit[f[min_idx].x][f[min_idx].y]; //�ð� �߰�
			f.clear(); //���� �� �ִ� ����� ����Ʈ Ŭ����
			for (int ni = 0; ni < n; ++ni)
				for (int nj = 0; nj < n; ++nj)
					visit[ni][nj] = 0; //�湮�� visit �ٽ� Ŭ����

			while (!p.empty())
				p.pop(); //�� �� �ִ� position Ŭ����

			p.push({ s.x, s.y }); //���� ��� ��ġ ����
		}

	}
	return result;
}

int main()
{
	cin >> n;
	for (int ni = 0; ni < n; ++ni)
	{
		for (int nj = 0; nj < n; ++nj)
		{
			cin >> map[ni][nj];
			if (map[ni][nj] == 9)
			{
				map[ni][nj] = 0;
				s.x = ni, s.y = nj, s.age = 2;
			}
		}
	}
	cout << bfs();
}