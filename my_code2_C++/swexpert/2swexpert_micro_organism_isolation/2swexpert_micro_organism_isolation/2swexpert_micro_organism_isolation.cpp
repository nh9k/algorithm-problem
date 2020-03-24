#include <iostream>
#include <vector>
using namespace std;
int n, m, k, map[100][100], dx[4] = { -1,1,0,0 }, dy[4] = { 0,0,-1,1 }, cross[4] = {1,0,3,2};
typedef struct {
	int x, y, o_num, dir;
	bool live;
}GUNZIP;
vector <GUNZIP> g;

void simulation()
{
	for (int mi = 0; mi < m; ++mi) //m은 시간 
	{
		for (int sz = 0; sz < g.size(); ++sz)
		{
			g[sz].x += dx[g[sz].dir], g[sz].y += dy[g[sz].dir];

			if (g[sz].x == 0 || g[sz].x == n - 1 || g[sz].y == 0 || g[sz].y == n - 1) //약품 :: 방향 턴 + 절반
			{ 
				g[sz].dir = cross[g[sz].dir];
				g[sz].o_num /= 2;
			}
			else if (map[g[sz].x][g[sz].y] != 0)
			{
				if (g[map[g[sz].x][g[sz].y]-1].o_num < g[sz].o_num) {
					g[map[g[sz].x][g[sz].y]-1].live = false; //죽음
					map[g[sz].x][g[sz].y] = sz + 1; //미생물수 더많은 애의 인덱스 저장
				}
				else
				{
					g[sz].live = false;
				}
			}
			else
			{// visit
				map[g[sz].x][g[sz].y] = sz + 1;
			}
		}

		for (int sz = 0; sz < g.size(); ++sz)
		{
			if (g[sz].live == false)
			{
				g[map[g[sz].x][g[sz].y] - 1].o_num += g[sz].o_num;
			}
		}

		for (auto sz = g.begin(); sz != g.end();)
		{
			if ((*sz).live == false)
				sz = g.erase(sz);
			else
			{
				map[(*sz).x][(*sz).y] = 0;
				sz++;
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
		cin >> n >> m >> k;
		for (int ki = 0; ki < k; ++ki)
		{
			int temp_x, temp_y, temp_num, temp_dir;
			cin >> temp_x >> temp_y >> temp_num >> temp_dir;
			g.push_back({ temp_x, temp_y, temp_num, temp_dir - 1 });
			g[ki].live = true;
		}

		simulation();

		int result = 0;
		for (auto sz = g.begin(); sz != g.end(); ++sz)
		{
			result += (*sz).o_num;			
		}
		cout << "#" << ti + 1 << " " << result << endl;

		//for (int ni = 0; ni < n; ++ni)
		//	for (int nj = 0; nj < n; ++nj)
		//		map[ni][nj] = 0;

		g.clear();
	}
	return 0;
}