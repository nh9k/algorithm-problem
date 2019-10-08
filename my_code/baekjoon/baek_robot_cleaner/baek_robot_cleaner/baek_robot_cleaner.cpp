#include <iostream>
using namespace std;

int n, m, map[50][50];
int dir[4] = { 3,0,1,2 }, dirx[4] = { -1,0,1,0 }, diry[4] = { 0,1,0,-1 }, cross_dir[4] = { 2,3,0,1 };
bool finish;
typedef struct {
	int x, y, dir, cnt;
}position;
position robot;

void dfs(int mem)
{
	if (finish) return;
	//for (int x = 0; x < n; x++)
	//{
	//	for (int y = 0; y < m; y++)
	//	{
	//		cout << map[x][y];
	//	}cout << endl;
	//}cout << endl;
	map[robot.x][robot.y] = 2;// 청소
	robot.dir = dir[robot.dir]; //회전
	if (map[robot.x + dirx[robot.dir]][robot.y + diry[robot.dir]]==0)//벽아니고 청소한곳 아닐때
	{	
		robot.x += dirx[robot.dir], robot.y += diry[robot.dir]; //직진
		robot.cnt++;
		dfs(robot.dir);
	}
	else //벽이거나 청소한 곳일 경우
	{
		if (robot.dir == mem) //한바퀴 모두 검사한 경우
		{
			if (map[robot.x + dirx[cross_dir[robot.dir]]][robot.y + diry[cross_dir[robot.dir]]] == 1)
			{//후진 할 곳이 벽인 경우
				finish = true;
				return;
			}
			else
			{//벽이 아니므로 후진
				robot.x += dirx[cross_dir[robot.dir]], robot.y += diry[cross_dir[robot.dir]];
			}
		}
		dfs(mem);
	}
	return;
}

int main(void)
{
	cin >> n >> m;
	cin >> robot.x >> robot.y >> robot.dir;
	for (int x = 0; x < n; x++)
	{
		for (int y = 0; y < m; y++)
		{
			cin >> map[x][y];
		}
	}
	finish = false;
	dfs(robot.dir);
	cout << robot.cnt+1 << endl;

	return 0;
}