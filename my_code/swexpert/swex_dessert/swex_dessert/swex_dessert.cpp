#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> map, visit; //����
vector<int> sum, cnt, check, dire;
int n, idx, chk, x, y, dir, flag; //���� ũ��, sum�� cnt�� index, �̶����� ���� ������ ����Ʈ�� �־����� Ȯ���ϴ� index
int mx[4] = { 1,1,-1,-1 };
int my[4] = { 1,-1,-1,1 };

int checkfunc(int x1, int y1) //�迭 ���� ������ �˻�, visit���� �˻�, ������ �˻�
{
	if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= n) //�迭 ���� ���̸�
		return false;
	if (visit[x1][y1] == 2)
		return true;

	if (visit[x1][y1] == true) //visit ���� �˻�
	{
		dir--; flag = 1;
		chk--;
		return false;
	}

	for (int q = 0; q < chk; q++) //�������� ������ �ִ��� �˻�
	{
		if (map[x1][y1] == check[q])
			return false; //�����ϸ� false
	}

	return true;
}
int rotation()
{
	if (flag == 1)
	{
		x += mx[dir]; y += my[dir];
		flag = 0; return true;
	}

	x -= mx[dir]; y -= my[dir]; //���ư���
	dir++;
	if (dir >= 4) return false;
	x += mx[dir]; y += my[dir];
	return true;
}
void traversal(int x1, int y1)
{
	chk = 0; check.assign(n*n, 0); //�湮�� �� ���� ������
	dire.assign(n*n, 0);
	check[chk] = map[x1][y1];
	chk++;

	x = x1 + mx[0]; y = y1 + my[0];

	flag = 0;
	if (x >= 0 && x < n && y >= 0 && y < n) //ù��° �湮 �ٷ� ������ ���� üũ��
	{
		while (1)
		{
			int r = true;
			while (checkfunc(x, y) != true && r == true)
			{
				r = rotation();
			}
			if (visit[x][y] == 2)
				break;
			if (r == false) //dir�� 4���� ���ų� ū ���
			{
				//if (chk >= 4)
				//{
					/*int mem = dir;
					chk -= 2;
					if (chk < 3) return;
					for (int i = 0; i < n; i++)
					{
						for (int j = 0; j < n; j++)
						{
							if (visit[i][j] == true)
							{
								if (check[chk] == map[i][j])
								{
									x = i; y = j; dir -= 2; break;
								}
							}
						}
						if (dir != mem) break;
					}
				}
				else
				{*/
					return;
					//}
				//}
			}
			//if (dir >= 4 && dir < 0) break;
			visit[x][y] = true;
			check[chk] = map[x][y];
			dire[chk] = dir;
			chk++;
			x += mx[dir]; y += my[dir]; //����

		}
	}
	else //ù��° �湮 �ٷ� �������� ���� �Ұ���
		return;

	if (visit[x][y] == 2) //���� �Ϸ�
	{
		for (int q = 0; q < chk; q++)
		{
			sum[idx] += check[q];
			cnt[idx] += 1;
		}
		if (cnt[idx] < 4)
		{
			sum[idx] = 0;
			cnt[idx] = 0;
			return;
		}
		idx++;
	}
	else return;
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
	{
		scanf("%d", &n);

		map.assign(n, vector<int>(n, 0));

		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				scanf("%d", &map[j][k]);

		sum.assign((n - 2)*(n - 2), 0);
		cnt.assign((n - 2)*(n - 2), 0);
		idx = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (i == n - 2 || i == n - 1 || j == 0 || j == n - 1) continue;
				visit.assign(n, vector<int>(n, 0)); //�湮 �ʱ�ȭ
				dir = 0;
				visit[i][j] = 2; //�������� 2
				traversal(i, j);
			}
		}

		int maxsum = 0, maxcnt = -1;
		for (int i = 0; i < idx; i++)
		{
			if (maxsum < sum[i])
			{
				maxsum = sum[i];
				maxcnt = cnt[i];
			}
		}
		printf("#%d %d\n", i + 1, maxcnt);
	}
	return 0;
}