#include<iostream>
using namespace std;

int n, wh, point; //�� ũ��, ��Ȧ ����, ����
int map[100][100];
typedef struct p
{
	int x, y;
}p;
p ball, start; //�ɺ�, ������
typedef struct w
{
	int x, y, wp;
}w;
w whall[10]; //��Ȧ
int dx[4] = { -1,0,1,0 }, dy[4] = { 0,1,0,-1 };
int wall[4] = { 2,3,0,1 }; //���̶� �ݴ� �������� �̵��ؾ��ϴ� ���
void go(int px, int py, int dir)
{
	bool end = false;
	point = 0;

	while (!end)
	{		
		px += dx[dir]; //�̵�
		py += dy[dir];

		if (px < 0 || px >= n || py < 0 || py >= n) //�迭 ��(��)���� �˻�
		{
			point++;
			dir = wall[dir]; //���� turn
			continue;
		}
		if (map[px][py] < 5 && map[px][py] > 0) //�ﰢ���� ���� ���
		{
			int check = map[px][py];
			point++;
			if (check - 1 == dir || check == dir || ((check == 4) && (dir == 0))) //���� ����
			{
				dir = wall[dir]; //���� turn
			}
			else //�ﰢ�� ����
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
		else if (map[px][py] == 5) //�׸��� ���� ���
		{
			point++;
			dir = wall[dir]; //���� turn
			continue;
		}
		else if (map[px][py] >= 6) //��Ȧ: ����, ������ �״��
		{
			for (int i = 0; i < wh; i++)
			{
				if (((whall[i].x != px) || (whall[i].y != py)) && (map[px][py] == whall[i].wp))
				{ //��ġ�� �ٸ��� ���ڴ� ���� ���� ��Ȧ�� ã�Ƽ�
					px = whall[i].x; py = whall[i].y; // �ٸ� �� ��Ȧ ��ġ�� �־���
					break;
				}
			}
			continue;
		}
		else if (map[px][py] == -1 || (px == start.x && py == start.y)) //��Ȧ�̰ų� ������ �����ϸ� ��
		{
			end = true;
		}
	}
}

int qfs() //�迭 ��ü�� ���� �������� go()�� �Ѱ��ִ� �Լ�
{
	int maxpoint = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (map[i][j] == 0) //�� �����̸� ball�� �����ϴ� ��
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
	return maxpoint; //������ �ִ��� �Ѱ���
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
				if (map[i][j] >= 6) { //��Ȧ ���� ����
					whall[wh].x = i; whall[wh].y = j; whall[wh].wp = map[i][j];
					wh++;
				}
			}
		}

		printf("#%d %d\n", test_case, qfs());
	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}