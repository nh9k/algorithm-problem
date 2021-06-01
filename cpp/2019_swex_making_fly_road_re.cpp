#include <iostream>
using namespace std;
int n, x, map[20][20], cnt_result, visit[20];

bool can_visit(int first_, int second_)
{
	for (int idx = first_; idx <= second_; ++idx)
		if (visit[idx]) return false;
	return true;
}

void is_visit(int first_, int second_)
{
	for (int idx = first_; idx <= second_; ++idx)
	{
		visit[idx] = true;
	}
}

bool can_road(int first_, int second_, int height_, bool row_col, int chk_idx)
{
	if (first_ < 0 || first_ >= n || second_ < 0 || second_ >= n) return false;
	if (row_col)
	{ //가로 검사
		for (int idx = first_; idx <= second_; ++idx)
		{
			if (map[chk_idx][idx]!= height_)
				return false;
		}
	}
	else
	{ //세로 검사
		for (int idx = first_; idx <= second_; ++idx)
		{
			if (map[idx][chk_idx] != height_)
				return false;
		}
	}
	return true;
}

void chk_road()
{
	//가로 검사
	for (int ni = 0; ni < n; ++ni)
	{
		int mem_h = map[ni][0];
		bool pass = true;
		for (int nj = 1; nj < n; ++nj)
		{
			if (mem_h != map[ni][nj])
			{
				if (mem_h < map[ni][nj]) //가다가 높아지는 경우
				{
					if (mem_h + 1 == map[ni][nj])
					{
						if (!can_road(nj - x, nj - 1, map[ni][nj - 1], 1, ni))
						{
							pass = false; break;
						}
						else if (!can_visit(nj - x, nj - 1))
						{
							pass = false; break;
						}
					}
					else
					{
						pass = false; break;
					}	
				}
				else //가다가 낮아지는 경우
				{
					if (mem_h - 1 == map[ni][nj])
					{
						if (!can_road(nj, nj + x - 1, map[ni][nj], 1, ni))
						{
							pass = false; break;
						}
						else
						{
							is_visit(nj, nj + x - 1); //방문
						}
					}
					else
					{
						pass = false; break;
					}
				}
				mem_h = map[ni][nj];
			}
		}
		if (pass) cnt_result++;
		for (int idx = 0; idx < n; ++idx) visit[idx] = 0;
	}

	//세로 검사
	for (int nj = 0; nj < n; ++nj)
	{
		int mem_h = map[0][nj];
		bool pass = true;
		for (int ni = 1; ni < n; ++ni)
		{
			if (mem_h != map[ni][nj])
			{
				if (mem_h < map[ni][nj]) //가다가 높아지는 경우
				{
					if (mem_h + 1 == map[ni][nj])
					{
						if (!can_road(ni - x, ni - 1, map[ni - 1][nj], 0, nj))
						{
							pass = false; break;
						}
						else if (!can_visit(ni - x, ni - 1))
						{
							pass = false; break;
						}
					}
					else
					{
						pass = false; break;
					}
				}
				else //가다가 낮아지는 경우
				{
					if (mem_h - 1 == map[ni][nj])
					{
						if (!can_road(ni, ni + x - 1, map[ni][nj], 0, nj))
						{
							pass = false; break;
						}
						else
						{
							is_visit(ni, ni + x - 1); //방문
						}
					}
					else
					{
						pass = false; break;
					}
				}
				mem_h = map[ni][nj];
			}
		}
		if (pass) cnt_result++;
		for (int idx = 0; idx < n; ++idx) visit[idx] = 0;
	}
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	int t;
	cin >> t;
	for (int ti = 0; ti < t; ++ti)
	{
		cin >> n >> x;
		for (int ni = 0; ni < n; ++ni)
		{
			for (int nj = 0; nj < n; ++nj)
			{
				cin >> map[ni][nj];
			}
		}
		cnt_result = 0;
		chk_road();
		cout << "#" << ti + 1 << " " << cnt_result << endl;
	}
	return 0;
}