#include <iostream>
#include <queue>
#include <vector>

using namespace std;

queue<int> movex, movey;
vector<vector<int>> map, visit;
int N, M, R, C, L;
int canmove, cnt, posx, posy;

vector<int> mx = { -1,0,1,0 };
vector<int> my = { 0,1,0,-1 };

int check(int tx, int ty, int num)
{
	if (visit[tx][ty] != true)
	{
		if (map[tx][ty] == 0)
			return 0;
		else if (num == 0)
		{
			if (map[tx][ty] == 1 || map[tx][ty] == 2 || map[tx][ty] == 5 || map[tx][ty] == 6)
				return 1;
			return 0;
		}
		else if (num == 1)
		{
			if (map[tx][ty] == 1 || map[tx][ty] == 3 || map[tx][ty] == 6 || map[tx][ty] == 7)
				return 1;
			return 0;
		}
		else if (num == 2)
		{
			if (map[tx][ty] == 1 || map[tx][ty] == 2 || map[tx][ty] == 4 || map[tx][ty] == 7)
				return 1;
			return 0;
		}
		else if (num == 3)
		{
			if (map[tx][ty] == 1 || map[tx][ty] == 3 || map[tx][ty] == 4 || map[tx][ty] == 5)
				return 1;
			return 0;
		}
	}
	return 0;
}

void checkfunc(int X, int Y, int num)
{
	int dx = X + mx[num];
	int dy = Y + my[num];
	if (0 <= dx && dx < N && 0 <= dy && dy < M) //배열 범위 안인지 검사
	{
		if (check(dx, dy, num) == 1)
		{
			movex.push(dx); movey.push(dy); // flag = 1;
		}
	}
	return;
}

void visiting(int X, int Y)
{
	if (0 <= X && X < N && 0 <= Y && Y < M)
	{
		if (visit[X][Y] != true)
		{
			int p = map[X][Y];
			visit[X][Y] = true;
			cnt++;
			//if (p == 0)
			//{
			//	//visit[X][Y] = false;
			//	return;
			//}
			//else
			//{
				//cnt++;
			if (p == 1) //Pipe가 1의 모양일 때 상 우 하 좌 모두 점검
			{
				checkfunc(X, Y, 0);
				checkfunc(X, Y, 1);
				checkfunc(X, Y, 2);
				checkfunc(X, Y, 3);
			}
			else if (p == 2)
			{
				checkfunc(X, Y, 0);
				checkfunc(X, Y, 2);
			}
			else if (p == 3)
			{
				checkfunc(X, Y, 1);
				checkfunc(X, Y, 3);
			}
			else if (p == 4)
			{
				checkfunc(X, Y, 0);
				checkfunc(X, Y, 1);
			}
			else if (p == 5)
			{
				checkfunc(X, Y, 1);
				checkfunc(X, Y, 2);
			}
			else if (p == 6)
			{
				checkfunc(X, Y, 2);
				checkfunc(X, Y, 3);
			}
			else if (p == 7)
			{
				checkfunc(X, Y, 3);
				checkfunc(X, Y, 0);
			}
			//}
		}
	}
}

int bfs(int N, int M, int R, int C, int L)
{
	cnt = 0, canmove = 0;
	posx = R, posy = C;
	movex.push(posx); movey.push(posy);

	for (int i = 0; i < L; i++)
	{
		canmove = movex.size();
		//flag = 0;
		for (int j = 0; j < canmove; j++)
		{
			posx = movex.front();
			posy = movey.front();
			movex.pop(); movey.pop();

			visiting(posx, posy);
		}
		//if (canmove == 0) return cnt;
	}
	
	return cnt;
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	for (int i = 0; i < T; i++)
	{
		scanf("%d %d %d %d %d", &N, &M, &R, &C, &L);
		map.assign(N, vector<int>(M, 0));
		visit.assign(N, vector<int>(M, 0));
		int sizeq = movex.size();
		for (int i = 0; i < sizeq; i++) //이걸 안해줘서 마지막에 queue에 방문할 곳을 push하고 시간이 다 되어서 남게됨!!
		{
			movex.pop();
			movey.pop();
		}

		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < M; k++)
			{
				scanf("%d", &map[j][k]);
			}
		}

		printf("#%d %d\n", i + 1, bfs(N, M, R, C, L));
		//for (int j = 0; j < N; j++)
		//{
		//	for (int k = 0; k < M; k++)
		//	{
		//		printf("%d", visit[j][k]);
		//	}
		//	printf("\n");
		//}
		//printf("\n");
	}
	return 0;
}