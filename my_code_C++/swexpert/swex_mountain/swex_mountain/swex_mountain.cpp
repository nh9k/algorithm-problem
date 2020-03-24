#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

vector<vector<int>> mountain; //지형
vector<vector<int>> visit;    //방문 체크
int N, K, maximum, xy, ans;    //최대 깎을 수 있는 높이, 최대 지형의 높이, 최대 지형 개수
vector<int> mx;    //최대 지형 높이의 x좌표
vector<int> my;    //최대 지형 높이의 y좌표
vector<int> diry = { 0,1,0,-1 };
vector<int> dirx = { -1,0,1,0 };

void dfs(int x, int y, int cnt, int flag)
{

	if (ans < cnt) ans = cnt;

	for (int i = 0; i < 4; i++) //처음에는 이중 for문을 돌려서 각 for(int &i:dirx) for(int &y: diry)를 돌려 시간 초과!!!
	{
		if (x + dirx[i] < 0 || x + dirx[i] >= N || y + diry[i] < 0 || y + diry[i] >= N) continue;
		else if (visit[x + dirx[i]][y + diry[i]]) continue; //방문한 것도 체크 해야함!!!
		else if (mountain[x][y] > mountain[x + dirx[i]][y + diry[i]])
		{
			visit[x][y] = true;
			dfs(x + dirx[i], y + diry[i], cnt + 1, flag);
			visit[x][y] = false;
		}
		else if (flag == false)
		{
			for (int k = 1; k <= K; k++)
			{
				if (mountain[x][y] > mountain[x + dirx[i]][y + diry[i]] - k)
				{
					visit[x][y] = true;
					flag = true;
					mountain[x + dirx[i]][y + diry[i]] -= k; //이것도 까먹지 말기!!!

					dfs(x + dirx[i], y + diry[i], cnt + 1, flag);

					mountain[x + dirx[i]][y + diry[i]] += k;
					visit[x][y] = false;
					flag = false;
				}
			}
		}

	}
	return;
}
int main()
{
	time_t start, end;
	int t;
	scanf("%d", &t);
	for (int T = 1; T <= t; T++)
	{
		ans = 0; //answer
		scanf("%d %d", &N, &K);

		mountain.assign(N, vector<int>(N, 0));
		visit.assign(N, vector<int>(N, 0));
		maximum = 0, xy = 0;
		mx.clear();
		my.clear();
		start = time(NULL); // 시간 측정 시작

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				scanf("%d", &mountain[i][j]);
				if (maximum <= mountain[i][j])
				{
					//if (maximum < mountain[i][j] && xy != 0) //얻은 위치가 최대 지형의 위치가 아니였다면
					//{
					//	mx.clear();
					//	my.clear();
					//	xy = 0; //초기화 해주는 것 조심하기 !!!
					//	maximum = mountain[i][j];
					//}
					//else if (xy == 0)
					//	maximum = mountain[i][j];
					//mx.push_back(i);
					//my.push_back(j);
					//xy++;
					maximum = mountain[i][j];
				}
			}
		}

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (maximum == mountain[i][j])
				{
					mx.push_back(i);
					my.push_back(j);
					xy++;
				}
			}
		}

		end = time(NULL); // 시간 측정 끝
		printf("%f\n", (double)(end - start)); //결과 출력

		for (int i = 0; i < xy; i++)
		{
			//printf("%d %d\n", mx[i], my[i]);
			dfs(mx[i], my[i], 0, 0);
		}

		printf("#%d %d\n", T, ans + 1);
	}
	return 0;
}