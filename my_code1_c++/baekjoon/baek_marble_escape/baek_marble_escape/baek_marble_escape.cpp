#include <iostream>
using namespace std;

int n, m, minimum;
char map[10][10];
int dirx[4] = { -1,0,1,0 }, diry[4] = { 0,1,0,-1 }, nodir[4] = { 2,3,0,1 };

typedef struct {
	int x, y;
}marble;
marble red, blue, hole;

void gored(int godir)
{
	while (map[red.x][red.y] == '.' && (!(red.x == blue.x && red.y == blue.y)))
	{
		red.x += dirx[godir];
		red.y += diry[godir];
	}
	if (map[red.x][red.y] != 'O')
	{
		red.x -= dirx[godir];
		red.y -= diry[godir];
	}
}
void goblue(int godir)
{
	while (map[blue.x][blue.y] == '.' && (!(red.x == blue.x && red.y == blue.y)))
	{
		blue.x += dirx[godir];
		blue.y += diry[godir];
	}
	if (map[blue.x][blue.y] != 'O')
	{
		blue.x -= dirx[godir];
		blue.y -= diry[godir];
	}
}

void firstred(int godir)
{
	gored(godir);
	goblue(godir);
	return;
}
void firstblue(int godir)
{
	goblue(godir);
	gored(godir);
	return;
}

void go(int godir)
{
	if ((red.x == blue.x) && (red.y < blue.y)) //블루가 더 오른쪽
	{
		if (godir == 1) //우방향
		{
			firstblue(godir);
			return;
		}
		else if (godir == 3) //좌방향
		{
			firstred(godir);
			return;
		}
	}
	else if ((red.x == blue.x) && (red.y > blue.y)) //블루가 더 왼쪽
	{
		if (godir == 1) //우방향
		{
			firstred(godir);
			return;
		}
		else if (godir == 3) //좌방향
		{
			firstblue(godir);
			return;
		}
	}
	else if ((red.x < blue.x) && (red.y == blue.y)) //블루가 더 아래쪽
	{
		if (godir == 0) // 상방향
		{
			firstred(godir);
			return;
		}
		else if (godir == 2) //하방향
		{
			firstblue(godir);
			return;
		}
	}
	else if ((red.x > blue.x) && (red.y == blue.y)) //블루가 더 위쪽
	{
		if (godir == 0) // 상방향
		{
			firstblue(godir);
			return;
		}
		else if (godir == 2) //하방향
		{
			firstred(godir);
			return;
		}
	}

	//나머지 경우
	while (map[red.x][red.y] == '.')
	{
		red.x += dirx[godir];
		red.y += diry[godir];
	}
	while (map[blue.x][blue.y] == '.')
	{
		blue.x += dirx[godir];
		blue.y += diry[godir];
	}
	if (map[red.x][red.y] != 'O')
	{
		red.x -= dirx[godir];
		red.y -= diry[godir];
	}
	if (map[blue.x][blue.y] != 'O')
	{
		blue.x -= dirx[godir];
		blue.y -= diry[godir];
	}
	return;
}

void bfs(int cnt, int before_dir)
{
	if ((red.x == hole.x && red.y == hole.y) || (blue.x == hole.x && blue.y == hole.y))
	{
		if (blue.x == hole.x && blue.y == hole.y)
			return;
		else if (minimum > cnt)
			minimum = cnt;
		return;
	}
	if (cnt >= 10)
		return;

	for (int i = 0; i < 4; i++)
	{
		if ((i == nodir[before_dir] || i == before_dir) && cnt != 0) //왔던 방향으로는 안가고, 가던 방향으로도 안가고, 처음은 모두 순회
			continue;

		marble mem_red, mem_blue;
		mem_red.x = red.x, mem_red.y = red.y,
			mem_blue.x = blue.x, mem_blue.y = blue.y;

		go(i);
		if ((red.x == mem_red.x&&red.y == mem_red.y) && (blue.x == mem_blue.x&&blue.y == mem_blue.y)) {
			continue;
		}
		bfs(cnt + 1, i);

		red.x = mem_red.x, red.y = mem_red.y,
			blue.x = mem_blue.x, blue.y = mem_blue.y;
	}
}

int main()
{
	//while (1)
	//{
		//freopen("sample_input.txt", "r", stdin);
			//int tc;
			//cin >> tc;
			//for (int t = 0; t < tc; t++)
			//{
	cin >> n >> m;
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < m; y++)
		{
			cin >> map[x][y];
			if (map[x][y] == 'R')
			{
				red.x = x;
				red.y = y;
				map[x][y] = '.';
			}
			else if (map[x][y] == 'B')
			{
				blue.x = x;
				blue.y = y;
				map[x][y] = '.';
			}
			else if (map[x][y] == 'O')
			{
				hole.x = x;
				hole.y = y;
			}
		}
	}
	minimum = 11;
	bfs(0, 0);
	if (minimum == 11)
		cout << -1 << endl;
	else
		cout << minimum << endl;
	//}
//}

	return 0;
}