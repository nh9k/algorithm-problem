#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> map, visit; //지도
vector<int> sum, cnt, check, dire;
int n, idx, chk, x, y, dir, flag; //지도 크기, sum과 cnt의 index, 이때까지 같은 종류의 디저트가 있었는지 확인하는 index
int mx[4] = { 1,1,-1,-1 };
int my[4] = { 1,-1,-1,1 };

int checkfunc(int x1, int y1) //배열 범위 안인지 검사, visit인지 검사, 종류수 검사
{
	if (x1 < 0 || x1 >= n || y1 < 0 || y1 >= n) //배열 범위 밖이면
		return false;
	if (visit[x1][y1] == 2)
		return true;

	if (visit[x1][y1] == true) //visit 인지 검사
	{
		dir--; flag = 1;
		chk--;
		return false;
	}

	for (int q = 0; q < chk; q++) //종류수가 같은게 있는지 검사
	{
		if (map[x1][y1] == check[q])
			return false; //실패하면 false
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

	x -= mx[dir]; y -= my[dir]; //돌아가고
	dir++;
	if (dir >= 4) return false;
	x += mx[dir]; y += my[dir];
	return true;
}
void traversal(int x1, int y1)
{
	chk = 0; check.assign(n*n, 0); //방문한 곳 값을 저장함
	dire.assign(n*n, 0);
	check[chk] = map[x1][y1];
	chk++;

	x = x1 + mx[0]; y = y1 + my[0];

	flag = 0;
	if (x >= 0 && x < n && y >= 0 && y < n) //첫번째 방문 바로 다음을 위해 체크함
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
			if (r == false) //dir이 4보다 같거나 큰 경우
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
			x += mx[dir]; y += my[dir]; //진격

		}
	}
	else //첫번째 방문 바로 다음부터 진입 불가시
		return;

	if (visit[x][y] == 2) //도착 완료
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
				visit.assign(n, vector<int>(n, 0)); //방문 초기화
				dir = 0;
				visit[i][j] = 2; //시작점은 2
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