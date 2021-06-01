#include <iostream>
//#include <vector>
//using namespace std;

int map[350][350], visit[350][350];
//vector<vector<int>> map, visit;
int n, m, k;
int dx[4] = { -1,0,1,0 }; //상우하좌
int dy[4] = { 0,1,0,-1 };


void pluscell(int i, int j)
{
	for (int h = 0; h < 4; h++)
	{	
		if (visit[i + dx[h]][j + dy[h]] != -1) 
			continue; //이전에 이미 배양된 곳이면,
		if (map[i][j] <= map[i + dx[h]][j + dy[h]] && visit[i + dx[h]][j + dy[h]] == -1) 
			continue; //이미 더 큰 세포가 배양되어있는데 방금 배양한 거면 
		
		map[i + dx[h]][j + dy[h]] = map[i][j];
	}		
}

void check() //증가 + 검사후 map과 같으면 배양시키는 함수
{
	for (int i = 0; i < n + k; i++) //증가
	{
		for (int j = 0; j < m + k; j++)
		{
			if (map[i][j] == 0) continue; // 배양 안된곳
			if (visit[i][j] > 2*map[i][j]) continue; //이미 죽은 세포

			visit[i][j] += 1;
		}
	}
	for (int i = 0; i < n + k; i++) //검사
	{
		for (int j = 0; j < m + k; j++)
		{
			if (map[i][j] == 0) continue; // 배양 안된곳
			if (visit[i][j] > map[i][j]) continue; //이미 배양 끝난 세포

			if (map[i][j] == visit[i][j])//증가할 시간
				pluscell(i, j); //주변에 증가
		}
	}
}

int result() //전체 map을 돌면서 배양한 전체 줄기 세포의 개수를 세는 함수
{
	int cnt = 0;
	for (int i = 0; i < n + k; i++)
	{
		for (int j = 0; j < m + k; j++)
		{
			if (2*map[i][j]-1 > visit[i][j] && map[i][j]!= 0 )
			{
				cnt++;
			}
		}
	}
	return cnt;
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	int testcase;
	scanf("%d", &testcase);
	for (int i = 0; i < testcase; i++)
	{
		scanf("%d %d %d", &n, &m, &k);

		//map.assign(n + k, vector<int>(m + k, 0));
		//visit.assign(n + k, vector<int>(m + k, -1));
		for (int j = 0; j < k + n; j++)
		{
			for (int h = 0; h < k + m; h++)
			{
				map[j][h] = 0;
				visit[j][h] = -1;
			}
		}

		for (int j = 0; j < n; j++)
			for (int h = 0; h < m; h++)
				scanf("%d", &map[k / 2 + j][k / 2 + h]);

		for (int j = 0; j < k; j++)
			check();

		printf("#%d %d\n", i + 1, result());
	}
	return 0;
}