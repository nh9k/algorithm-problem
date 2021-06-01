#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int N, L, R, map[50][50], mx[4] = { -1,0,1,0 }, my[4] = { 0,1,0,-1 }, visit[50][50];
typedef struct {
	int vnum, sum, cnt;
	vector <pair<int, int>> xy;
}UNI;

bool dist_up(int x, int y)
{
	if (abs(map[x][y] - map[x - 1][y]) >= L && abs(map[x][y] - map[x - 1][y]) <= R)
		return true;
	return false;
}

bool dist_left(int x, int y)
{
	if (abs(map[x][y] - map[x][y-1]) >= L && abs(map[x][y] - map[x][y-1]) <= R)
		return true;
	return false;
}

int moving()
{
	int tchk = 0;
	while (1)
	{
		vector <UNI> u;
		int numbering = 0;

		for (int ni = 0; ni < N; ++ni)
		{
			for (int nj = 0; nj < N; ++nj)
			{
				if (ni == 0 && nj == 0)
				{
					visit[ni][nj] = numbering;
					u.push_back({ numbering, map[ni][nj], 1 });
					u.back().xy.push_back({ ni, nj });
					numbering++;
				}
				else if (ni == 0)
				{
					if (dist_left(ni, nj))
					{
						visit[ni][nj] = visit[ni][nj - 1];
						for (int i = 0; i < u.size(); ++i)
						{
							if (u[i].vnum == visit[ni][nj])
							{
								u[i].cnt++;
								u[i].sum += map[ni][nj];
								u[i].xy.push_back({ ni, nj });
								break;
							}
						}					
					}
					else
					{
						visit[ni][nj] = numbering;
						u.push_back({ numbering, map[ni][nj], 1 });
						u.back().xy.push_back({ ni, nj });
						numbering++;
					}
				}
				else if (nj == 0)
				{
					if (dist_up(ni, nj))
					{
						visit[ni][nj] = visit[ni-1][nj];
						for (int i = 0; i < u.size(); ++i)
						{
							if (u[i].vnum == visit[ni][nj])
							{
								u[i].cnt++;
								u[i].sum += map[ni][nj];
								u[i].xy.push_back({ ni, nj });
								break;
							}
						}
					}
					else
					{
						visit[ni][nj] = numbering;
						u.push_back({ numbering, map[ni][nj], 1 });
						u.back().xy.push_back({ ni, nj });
						numbering++;
					}
				}
				else
				{
					if (dist_up(ni, nj) && dist_left(ni, nj))
					{
						if (visit[ni - 1][nj] != visit[ni][nj - 1])
						{
							visit[ni][nj] = min(visit[ni - 1][nj], visit[ni][nj - 1]);
							int min_idx, max_idx;
							bool pass1 = false, pass2 = false;
							for (int i = 0; i < u.size(); ++i)
							{
								if (u[i].vnum == max(visit[ni - 1][nj], visit[ni][nj - 1]))
								{
									max_idx = i;
									pass1 = true;
								}
								else if (u[i].vnum == min(visit[ni - 1][nj], visit[ni][nj - 1]))
								{
									min_idx = i;
									pass2 = true;
								}
								if (pass1 && pass2) break;
							}

							u[min_idx].cnt++;
							u[min_idx].sum += map[ni][nj];
							u[min_idx].xy.push_back({ ni, nj });

							u[min_idx].sum += u[max_idx].sum;
							u[min_idx].cnt += u[max_idx].cnt;
							for (int i = 0; i < u[max_idx].xy.size(); ++i)
							{
								u[min_idx].xy.push_back(u[max_idx].xy[i]);	
								visit[u[max_idx].xy[i].first][u[max_idx].xy[i].second] = visit[ni][nj];
							}
							u.erase(u.begin() + max_idx);
						}
						else
						{
							visit[ni][nj] = visit[ni - 1][nj];
							for (int i = 0; i < u.size(); ++i)
							{
								if (u[i].vnum == visit[ni][nj])
								{
									u[i].cnt++;
									u[i].sum += map[ni][nj];
									u[i].xy.push_back({ ni, nj });
									break;
								}
							}
						}
					}
					else if(dist_up(ni, nj))
					{
						visit[ni][nj] = visit[ni - 1][nj];
						for (int i = 0; i < u.size(); ++i)
						{
							if (u[i].vnum == visit[ni][nj])
							{
								u[i].cnt++;
								u[i].sum += map[ni][nj];
								u[i].xy.push_back({ ni, nj });
								break;
							}
						}
					}
					else if ((dist_left(ni, nj)))
					{
						visit[ni][nj] = visit[ni][nj-1];
						for (int i = 0; i < u.size(); ++i)
						{
							if (u[i].vnum == visit[ni][nj])
							{
								u[i].cnt++;
								u[i].sum += map[ni][nj];
								u[i].xy.push_back({ ni, nj });
								break;
							}
						}
					}
					else
					{
						visit[ni][nj] = numbering;
						u.push_back({ numbering, map[ni][nj], 1 });
						u.back().xy.push_back({ ni, nj });
						numbering++;
					}
				}
			}
		}

		bool pass = true;
		for (int i = 0; i < u.size(); ++i) //인구 이동
		{
			if (u[i].cnt == 1) continue;

			pass = false;
			int sc = u[i].sum / u[i].cnt;
			for (int j = 0; j < u[i].xy.size(); ++j)
			{
				map[u[i].xy[j].first][u[i].xy[j].second] = sc;
			}
		}

		if (pass) break;
		tchk++;
	}
	return tchk;
}

int main()
{
	cin >> N >> L >> R;
	for (int ni = 0; ni < N; ++ni)
	{
		for (int nj = 0; nj < N; ++nj)
		{
			cin >> map[ni][nj];
		}
	}
	cout << moving();
	return 0;
}
