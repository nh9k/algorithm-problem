#include <iostream>
#include <vector>
using namespace std;

int energy, dx[4] = { 0,0,-1,1 }, dy[4] = {1,-1,0,0};
int visit[4001][4001];
typedef struct {
	int x, y, dir, k;
	bool live;
}ATOM;
vector <ATOM> a;

void simulation()
{
	while (!a.empty())
	{
		for (int v = 0; v < a.size(); ++v)
		{
			a[v].x += dx[a[v].dir], a[v].y += dy[a[v].dir];
			if (a[v].x < 0 || a[v].y < 0 || a[v].x >= 4001 || a[v].y >= 4001)
			{//범위 밖
				a[v].live = false;
			}
			else if (visit[a[v].x][a[v].y])
			{//원자 충돌
				a[v].live = false;
				a[visit[a[v].x][a[v].y] - 1].live = false;
			}
			else
			{
				visit[a[v].x][a[v].y] = v + 1;
			}
		}

		for (auto v = a.begin(); v != a.end();)
		{
			if ((*v).live == false)
			{
				if (!((*v).x < 0 || (*v).y < 0 || (*v).x >= 4001 || (*v).y >= 4001))
				{//범위 밖이 아니면
					visit[(*v).x][(*v).y] = 0;
					energy += (*v).k;
				}
				v = a.erase(v);
			}
			else
			{
				visit[(*v).x][(*v).y] = 0;
				++v;
			}
		}
	}
	return;
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	int t;
	cin >> t;
	for (int ti = 0; ti < t; ++ti)
	{
		int atom, temp_x, temp_y, temp_dir, temp_k;
		cin >> atom;
		for (int ai = 0; ai < atom; ++ai)
		{
			cin >> temp_x >> temp_y >> temp_dir >> temp_k;
			a.push_back({ (temp_x+1000)*2, (temp_y +1000)*2, temp_dir, temp_k });
			a[ai].live = true;
		}
		energy = 0;
		simulation();
		cout << "#" << ti + 1 << " " << energy << endl;
	}
	return 0;
}
