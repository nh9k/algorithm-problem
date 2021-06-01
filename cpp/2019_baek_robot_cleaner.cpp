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
	map[robot.x][robot.y] = 2;// û��
	robot.dir = dir[robot.dir]; //ȸ��
	if (map[robot.x + dirx[robot.dir]][robot.y + diry[robot.dir]]==0)//���ƴϰ� û���Ѱ� �ƴҶ�
	{	
		robot.x += dirx[robot.dir], robot.y += diry[robot.dir]; //����
		robot.cnt++;
		dfs(robot.dir);
	}
	else //���̰ų� û���� ���� ���
	{
		if (robot.dir == mem) //�ѹ��� ��� �˻��� ���
		{
			if (map[robot.x + dirx[cross_dir[robot.dir]]][robot.y + diry[cross_dir[robot.dir]]] == 1)
			{//���� �� ���� ���� ���
				finish = true;
				return;
			}
			else
			{//���� �ƴϹǷ� ����
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