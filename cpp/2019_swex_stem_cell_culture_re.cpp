#include <iostream>
#include <queue>
using namespace std;

int map[353][353], k, dx[4] = { -1,0,1,0 }, dy[4] = { 0,1,0,-1 };
typedef struct {
	int strong, x, y;
	bool die;
}STEM;
vector <STEM> c;

int simulation()
{
	int t = 0;
	while (t <= k)
	{
		//for (int ni = 140; ni < 160; ++ni)
		//{
		//	for (int nj = 140; nj < 160; ++nj)
		//	{
		//		cout << map[ni][nj] <<  " ";
		//	}cout << endl;
		//}cout << endl; cout << endl;
		int vsz = c.size();
		for (int i = 0; i < vsz; ++i)
		{
			if (c[i].strong <= map[c[i].x][c[i].y] && c[i].strong * 2 > map[c[i].x][c[i].y])
			{//번식
				for (int m = 0; m < 4; ++m)
				{
					if (map[c[i].x + dx[m]][c[i].y + dy[m]] >= 0) continue;
					map[c[i].x + dx[m]][c[i].y + dy[m]] = 0;
					c.push_back({ c[i].strong, c[i].x + dx[m], c[i].y + dy[m] });
				}
			}
			map[c[i].x][c[i].y]++; //카운트
			if (c[i].strong * 2 <= map[c[i].x][c[i].y])
			{//죽음
				c[i].die = true;
			}
		}
		for (auto i = c.begin(); i != c.end();)
		{
			if ((*i).die)
			{
				i = c.erase(i);
			}
			else ++i;
		}
		++t;
	}
	return c.size();
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	int t, n, m, temp;
	cin >> t;
	for (int ti = 0; ti < t; ++ti)
	{
		for (int ni = 0; ni < 353; ++ni)
			for (int nj = 0; nj < 353; ++nj)
				map[ni][nj] = -1;

		cin >> n >> m >> k;
		for (int ni = 0; ni < n; ++ni)
		{
			for (int nj = 0; nj < m; ++nj)
			{
				cin >> temp;
				if (temp != 0)
					c.push_back({ temp, ni + 151, nj + 151 });
			}
		}

		cout << "#" << ti + 1 << " " << simulation() << endl;
		c.clear();
	}
	return 0;
}