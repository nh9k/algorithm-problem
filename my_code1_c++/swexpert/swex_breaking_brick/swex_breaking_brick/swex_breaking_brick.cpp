#include<iostream>
#include<stack>

using namespace std;
int n, w, h; //4 12 15: w�� ����, h�� ����
int map[15][12];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int minimum;

int result() //map�� ó������ ������ ���鼭 0�� �ƴ� ���� ������ ��ȯ
{
	int cnt = 0;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (map[i][j] != 0) cnt++;
		}
	}
	return cnt;
}

void arrange() //�μ��Ⱑ �� ���� ������ stack�� �ְ� ������ �����ϴ� �Լ�
{
	stack <int> brickarr;
	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			if (map[j][i] == 0)continue;

			brickarr.push(map[j][i]);
			map[j][i] = 0;
		}
		int j = h - 1;
		while (!brickarr.empty())
		{
			map[j][i] = brickarr.top();
			brickarr.pop();
			j--;
		}
	}
}

void breaking(int x, int y) //������� ���鼭 ������ �����ϴ� �Լ�
{
	if (x < 0 || x >= h || y < 0 || y >= w) return;
	if (map[x][y] == 0) return;
	if (map[x][y] == 1)
	{
		map[x][y] = 0; return;
	}
	else
	{
		int range = map[x][y];
		map[x][y] = 0;
		for (int i = 1; i < range; i++)
			for (int j = 0; j < 4; j++)
				breaking(x + (dx[j] * i), y + (dy[j] * i));
	}
	return;
}

void dfs(int cnt) //0���� w���� ���鼭 ������ ������ ����
{
	if (minimum == 0) return;
	if (cnt == n) {
		int check = result();
		if (check < minimum)
		{
			minimum = check;
		}
		return;
	}

	for (int j = 0; j < w; j++) //w(����) ��ġ�� �̵��ϸ� ������ ����
	{
		int here = 0;
		for (int i = 0; i < h; i++) //������ ����߷�����
		{
			if (map[i][j] == 0) continue;
			here = i; break; //���� ó�� ������ ����
		}
		int copy[15][12] = { 0, };
		for (int i = 0; i < h; i++) //15
			for (int j = 0; j < w; j++) //12
				copy[i][j] = map[i][j];

		breaking(here, j);
		arrange();
		dfs(cnt + 1);

		for (int i = 0; i < h; i++) //15
			for (int j = 0; j < w; j++) //12
				map[i][j] = copy[i][j];
	}
	return;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("sample_input.txt", "r", stdin);
	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case)
	{
		scanf("%d %d %d", &n, &w, &h);

		for (int i = 0; i < h; i++) //15
			for (int j = 0; j < w; j++) //12
				scanf("%d", &map[i][j]);

		minimum = 987654321;
		dfs(0);
		printf("#%d %d\n", test_case, minimum);
	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}