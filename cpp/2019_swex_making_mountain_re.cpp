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

		if (mx < 0 || mx >= n || my < 0 || my >= n) continue; //�迭 ��
		else if (visit[mx][my]) continue; //�̹� �湮�� ��
		else if (map[mx][my] >= map[x][y]) //�� �� ������ ��ƾ���
		{
			if (one_chance) continue; //�̹� ������� ����
			for (int ki = 1; ki <= k; ++ki)
			{
				if (map[mx][my] - ki >= map[x][y]) continue; //��Ƶ� ������ ��

				map[mx][my] -= ki;
				visit[mx][my] = true;
				dfs(leng + 1, true, mx, my);
				map[mx][my] += ki;
				visit[mx][my] = false;
				break; //�ѹ� ��Ƽ� �� �� ������, �� �̻��� ���� �ʿ����
			}
			//�ƹ��� ��Ƶ� �� �� ������ ���� ����, ���� ���� ���ƿ͵� ���� ���� �˻�.
		}
		else //�� �� ����
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
					m.push_back({ ni,nj }); //�ִ� ���� ����

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