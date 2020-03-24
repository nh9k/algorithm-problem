#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

//vector<vector<int>> map, visit; //지도
//vector<int> check;
int map[20][20] = { 0, };
int visit[20][20] = { 0, };
int check[400] = { 0, };
int n, chk; //지도 크기, 이때까지 같은 종류의 디저트가 있었는지 확인하는 index, direction
int maxcnt;
int mx[4] = { 1,1,-1,-1 };
int my[4] = { 1,-1,-1,1 };

bool checkfunc(int x, int y) //배열 범위 안인지 검사, 종류수 검사
{
	if (x < 0 || x >= n || y < 0 || y >= n) //배열 범위 밖이면
		return false;
	if (visit[x][y] == 2) //도착 완료
		return true;

	for (int q = 0; q < chk; q++) //종류수가 같은게 있는지 검사
	{
		if (map[x][y] == check[q])
			return false; //실패하면 false
	}
	return true;
}

void dfs(int x, int y, int dir)
{
	//if (flag == 1) return;

	if (checkfunc(x, y) == false)
		return;

	if (visit[x][y] == 2) //도착 완료
	{
		if (maxcnt < chk)
			maxcnt = chk;
		//flag = 1;
		return;
	}

	if (visit[x][y] == true) //visit 인지 검사
		return;

	else
	{
		int diri = dir + 2;
		if (diri > 3) diri = 4;
		visit[x][y] = true;
		check[chk] = map[x][y];
		chk++;
		for (int i = dir; i < diri; i++)
			dfs(x + mx[i], y + my[i], i);
		visit[x][y] = false;
		chk--;
	}
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
	{
		scanf("%d", &n);

		//map.assign(n, vector<int>(n, 0));
		for (int k = 0; k < n; k++)
			memset(map, 0, sizeof(map));

		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				scanf("%d", &map[j][k]);

		maxcnt = -1;
		for (int i = 0; i < n-2; i++)
		{
			for (int j = 1; j < n-1; j++)
			{
				//if (i == n - 2 || i == n - 1 || j == 0 || j == n - 1) continue;
				for (int k = 0; k < n; k++)
					memset(visit, 0, sizeof(visit));
				memset(check, 0, sizeof(check));
				//visit.assign(n, vector<int>(n, 0)); //방문 초기화
				//check.assign(n*n, 0); //방문한 곳의 map 정보 저장

				visit[i][j] = 2; //시작점은 2
				check[0] = map[i][j];
				chk = 1; //flag = 0;
				dfs(i + mx[0], j + my[0], 0);
			}
		}
		printf("#%d %d\n", i + 1, maxcnt);
	}
	return 0;
}