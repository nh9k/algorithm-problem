#include<iostream>
using namespace std;

int n, wh, point; //맵 크기, 웜홀 개수, 점수
int map[100][100];
typedef struct p
{
	int x, y;
}p;
p ball, start; //핀볼, 시작점
typedef struct w
{
	int x, y, wp;
}w;
w whall[10]; //웜홀
int dx[4] = { -1,0,1,0 }, dy[4] = { 0,1,0,-1 };
int wall[4] = { 2,3,0,1 }; //벽이라서 반대 방향으로 이동해야하는 경우
void go(int px, int py, int dir)
{
	bool end = false;
	point = 0;

	while (!end)
	{		
		px += dx[dir]; //이동
		py += dy[dir];

		if (px < 0 || px >= n || py < 0 || py >= n) //배열 밖(벽)인지 검사
		{
			point++;
			dir = wall[dir]; //방향 turn
			continue;
		}
		if (map[px][py] < 5 && map[px][py] > 0) //삼각벽을 만난 경우
		{
			int check = map[px][py];
			point++;
			if (check - 1 == dir || check == dir || ((check == 4) && (dir == 0))) //벽을 만남
			{
				dir = wall[dir]; //방향 turn
			}
			else //삼각을 만남
			{
				if (check == 1)
				{
					if (dir == 2) dir = 1;
					else dir = 0;
				}
				else if (check == 2)
				{
					if (dir == 3) dir = 2;
					else dir = 1;
				}
				else if (check == 3)
				{
					if (dir == 0) dir = 3;
					else dir = 2;
				}
				else if (check == 4)
				{
					if (dir == 1) dir = 0;
					else dir = 3;
				}
			}
			continue;
		}
		else if (map[px][py] == 5) //네모벽을 만난 경우
		{
			point++;
			dir = wall[dir]; //방향 turn
			continue;
		}
		else if (map[px][py] >= 6) //웜홀: 방향, 점수는 그대로
		{
			for (int i = 0; i < wh; i++)
			{
				if (((whall[i].x != px) || (whall[i].y != py)) && (map[px][py] == whall[i].wp))
				{ //위치는 다르고 숫자는 숫자 같은 웜홀을 찾아서
					px = whall[i].x; py = whall[i].y; // 다른 편 웜홀 위치를 넣어줌
					break;
				}
			}
			continue;
		}
		else if (map[px][py] == -1 || (px == start.x && py == start.y)) //블랙홀이거나 시작점 도착하면 끝
		{
			end = true;
		}
	}
}

int qfs() //배열 전체를 돌며 시작점을 go()에 넘겨주는 함수
{
	int maxpoint = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (map[i][j] == 0) //빈 공간이면 ball이 시작하는 곳
			{
				start.x = i;
				start.y = j;
				for (int d = 0; d < 4; d++)
				{
					go(i, j, d);
					if (maxpoint < point) maxpoint = point;
				}
			}
		}
	}
	return maxpoint; //점수의 최댓값을 넘겨줌
}

int main(int argc, char** argv)
{
	int test_case, T;
	freopen("sample_input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		scanf("%d", &n);
		wh = 0;

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				scanf("%d", &map[i][j]);
				if (map[i][j] >= 6) { //웜홀 정보 저장
					whall[wh].x = i; whall[wh].y = j; whall[wh].wp = map[i][j];
					wh++;
				}
			}
		}

		printf("#%d %d\n", test_case, qfs());
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}