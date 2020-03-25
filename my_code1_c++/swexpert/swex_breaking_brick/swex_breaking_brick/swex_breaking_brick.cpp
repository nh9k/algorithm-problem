#include<iostream>
#include<stack>

using namespace std;
int n, w, h; //4 12 15: w가 가로, h가 세로
int map[15][12];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int minimum;

int result() //map을 처음부터 끝까지 돌면서 0이 아닌 벽돌 개수를 반환
{
	int cnt = 0;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (map[i][j] != 0) cnt++;
		}
	}
	return cnt;
}

void arrange() //부수기가 한 차례 끝나면 stack에 넣고 벽돌을 정리하는 함수
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

void breaking(int x, int y) //상우하좌 돌면서 벽돌을 제거하는 함수
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

void dfs(int cnt) //0부터 w까지 돌면서 제거할 벽돌을 선택
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

	for (int j = 0; j < w; j++) //w(가로) 위치를 이동하며 구슬을 떨굼
	{
		int here = 0;
		for (int i = 0; i < h; i++) //구슬을 떨어뜨렸을때
		{
			if (map[i][j] == 0) continue;
			here = i; break; //가장 처음 만나는 벽돌
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
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}