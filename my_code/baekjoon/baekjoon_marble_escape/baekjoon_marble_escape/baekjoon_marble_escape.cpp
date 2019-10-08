#include <iostream>
#include <vector>
using namespace std;

int n, m, minroll, memroll;
int dx[4] = { -1,0,1,0 }; //상우하좌
int dy[4] = { 0,1,0,-1 };
int check_dir[4] = { 2,3,0,1 };
bool nopass;
vector <vector<char>> map;
typedef struct
{
	int x, y;
}position;
position red, blue;

void go(int dir, int roll)
{
	int step = 0;
	while (1)
	{
		red.x += dx[dir];
		red.y += dy[dir];
		step++;
		if (map[red.x][red.y] == 'O')
		{
			if (minroll > roll + 1) {
				memroll = minroll;
				minroll = roll + 1;
			}
			break;
		}
		else if (red.x == blue.x&&red.y == blue.y)
		{
			red.x -= dx[dir];
			red.y -= dy[dir];
			break;
		}
		else if (map[red.x][red.y] == '#')
		{
			red.x -= dx[dir];
			red.y -= dy[dir];
			break;
		}

	}
	if (step == 1 && minroll == memroll) {
		nopass = true;
		return;
	}
	while (1)
	{
		blue.x += dx[dir];
		blue.y += dy[dir];
		if (map[blue.x][blue.y] == 'O')
		{
			nopass = true;
			break;
		}
		else if (red.x == blue.x&&red.y == blue.y)
		{
			blue.x -= dx[dir];
			blue.y -= dy[dir];
			break;
		}
		else if (map[blue.x][blue.y] == '#')
		{
			blue.x -= dx[dir];
			blue.y -= dy[dir];
			break;
		}
	}
}

void dfs(int dir, int roll)
{
	if (nopass == true) //파란 공이 통과한 경우 or 갈수없는 길인 경우
	{
		if (memroll != minroll) minroll = memroll;
		nopass = false;
		return;
	}
	if (minroll != 100 && memroll != minroll) //빨간 공이 통과한 경우
	{
		memroll = minroll;
		return;
	}
	if (roll > minroll)
	{
		return;
	}
	if (roll >= 10) //10번 이상 기울인 경우
	{
		return;
	}

	for (int di = 0; di < 4; di++)
	{
		if ((check_dir[dir] == di || dir == di) && roll != 0) continue; //갔던 곳은 되돌아가지 않음 //원래 가던 방향도 가지 않음
		int rx = red.x, ry = red.y, bx = blue.x, by = blue.y;
		go(di, roll);
		dfs(di, roll + 1);
		red.x = rx, red.y = ry, blue.x = bx, blue.y = by;
	}
}

int main()
{
	/*freopen("sample_input.txt", "r", stdin);
	int tc;
	scanf("%d", &tc);
	for (int t = 0; t < tc; t++)
	{*/
	cin >> n >> m;

	map.assign(n, vector<char>(m, 0));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> map[i][j];
			if (map[i][j] == 'R') {
				red.x = i, red.y = j;
				map[i][j] = '.';
			}
			else if (map[i][j] == 'B') {
				blue.x = i, blue.y = j;
				map[i][j] = '.';
			}
		}
	}

	minroll = 100;
	memroll = 100;
	nopass = false;
	dfs(0, 0);

	//cout << '#' << t + 1 << " ";
	if (minroll != 100) cout << minroll << endl;
	else cout << -1 << endl;
	//}

	return 0;
}