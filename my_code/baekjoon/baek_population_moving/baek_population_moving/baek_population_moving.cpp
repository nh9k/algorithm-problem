#include <iostream> 
#include <vector>
#include <algorithm>
using namespace std;

int n, L, R, map[51][51], next_, visit[51][51];
int dx[4] = { -1,0,1,0 }, dy[4] = { 0,1,0,-1 };
typedef struct {
	int sum = 0, cnt = 0;
	vector <int> x, y;
}P;
vector <P> p;

//void search_visit()
//{
//	for (int num = 1; num < next_; ++num)
//	{
//		P p;
//		for (int ni = 0; ni < n; ++ni)
//		{
//			for (int nj = 0; nj < n; ++nj)
//			{
//				if (visit[ni][nj] == num)
//				{
//					p.sum += map[ni][nj];
//					p.cnt++;
//				}
//			}
//		}
//		if (p.cnt == 0) break;
//		else if (p.cnt == 1) continue;
//
//		int moving_result = p.sum / p.cnt;
//		for (int ni = 0; ni < n; ++ni)
//		{
//			for (int nj = 0; nj < n; ++nj)
//			{
//				if (visit[ni][nj] == num)
//				{
//					map[ni][nj] = moving_result;
//				}
//			}
//		}
//	}
//}

void search_vector()
{
	for (int vsz1 = 1; vsz1 < next_; ++vsz1)
	{
		if (p[vsz1].cnt == 0 ) continue;
		while(!p[vsz1].x.empty())
		{
			map[p[vsz1].x.back()][p[vsz1].y.back()] = p[vsz1].sum / p[vsz1].cnt;
			p[vsz1].x.pop_back(), p[vsz1].y.pop_back();
		}
		p[vsz1].sum = 0;
		p[vsz1].cnt = 0;
	}
}

void bfs(int x, int y, int objnum, int prenum)
{
	if (x < 0 || x >= n || y < 0 || y >= n) return;
	if (visit[x][y] != prenum) return;
	visit[x][y] = objnum;
	for (int i = 0; i < 4; ++i)
	{
		bfs(x + dx[i], y + dy[i], objnum, prenum);
	}
}

void move_vector(int objnum,int prenum)
{
	p[objnum].sum += p[prenum].sum;
	p[objnum].cnt += p[prenum].x.size();
	for (int vsz = 0; vsz < p[prenum].x.size(); ++vsz)
	{
		p[objnum].x.push_back(p[prenum].x[vsz]);
		p[objnum].y.push_back(p[prenum].y[vsz]);
	}
	p[prenum].sum = 0;
	p[prenum].cnt = 0;
	p[prenum].x.clear();
	p[prenum].y.clear();
}

bool abs_left(int ni, int nj)
{
	return (abs(map[ni][nj] - map[ni][nj - 1]) >= L && abs(map[ni][nj] - map[ni][nj - 1]) <= R);
}

bool abs_up(int ni, int nj)
{
	return (abs(map[ni][nj] - map[ni - 1][nj]) >= L && abs(map[ni][nj] - map[ni - 1][nj]) <= R);
}

void search_map()
{
	next_ = 1;
	for (int ni = 0; ni < n; ++ni)
	{
		for (int nj = 0; nj < n; ++nj)
		{
			if (ni == 0 && nj == 0) 
			{ //처음
				visit[ni][nj] = next_; 
				++next_;
			}
			else if (ni == 0)
			{ //왼쪽만 검사
				if (abs_left(ni, nj))
				{
					visit[ni][nj] = visit[ni][nj - 1];
				}
				else
				{
					visit[ni][nj] = next_;
					++next_;
				}
			}
			else if (nj == 0)
			{ //위쪽만 검사
				if (abs_up(ni, nj))
				{
					visit[ni][nj] = visit[ni - 1][nj];
				}
				else
				{
					visit[ni][nj] = next_;
					++next_;
				}
			}
			else
			{ //둘다 검사
				if (abs_left(ni, nj) && abs_up(ni, nj)) //둘다 참
				{
					if (visit[ni][nj - 1] == visit[ni - 1][nj]) visit[ni][nj] = visit[ni - 1][nj];
					else
					{
						visit[ni][nj] = min(visit[ni][nj - 1], visit[ni - 1][nj]);
						visit[ni][nj - 1] < visit[ni - 1][nj] ? move_vector(visit[ni][nj - 1], visit[ni - 1][nj]) : move_vector(visit[ni - 1][nj], visit[ni][nj - 1]);
						visit[ni][nj - 1] < visit[ni - 1][nj] ? bfs(ni - 1, nj, visit[ni][nj - 1], visit[ni - 1][nj]) : bfs(ni, nj - 1, visit[ni - 1][nj], visit[ni][nj - 1]);
					}
				}
				else if (abs_left(ni, nj)) //왼쪽만 참
				{
					visit[ni][nj] = visit[ni][nj - 1];
				}
				else if (abs_up(ni, nj)) //위쪽만 참
				{
					visit[ni][nj] = visit[ni - 1][nj];
				}
				else // 둘다 경계임
				{
					visit[ni][nj] = next_;
					++next_;
				}
			}
			p[visit[ni][nj]].sum += map[ni][nj];
			p[visit[ni][nj]].cnt++;
			p[visit[ni][nj]].x.push_back(ni);
			p[visit[ni][nj]].y.push_back(nj);
		}
	}
}

int main()
{
	cin >> n >> L >> R;
	for (int ni = 0; ni < n; ++ni)
	{
		for (int nj = 0; nj < n; ++nj)
		{
			cin >> map[ni][nj];
		}
	}

	int cnt = 0;
	p.assign(n*n+1, { 0,0 });
	while (1)
	{
		search_map();

	/*	for (int ni = 0; ni < n; ++ni)
		{
			for (int nj = 0; nj < n; ++nj)
			{
				cout << visit[ni][nj];
			}cout << endl;
		}cout << endl;*/

		if (next_-1 == n*n) break;
		//search_visit();
		search_vector();
		//for (int ni = 0; ni < n; ++ni)
		//{
		//	for (int nj = 0; nj < n; ++nj)
		//	{
		//		cout << map[ni][nj];
		//	}cout << endl;
		//}cout << endl;

		cnt++;
	}

	cout << cnt;
	return 0;

}