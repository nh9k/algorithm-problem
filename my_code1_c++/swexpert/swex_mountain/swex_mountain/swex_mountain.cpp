#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

vector<vector<int>> mountain; //����
vector<vector<int>> visit;    //�湮 üũ
int N, K, maximum, xy, ans;    //�ִ� ���� �� �ִ� ����, �ִ� ������ ����, �ִ� ���� ����
vector<int> mx;    //�ִ� ���� ������ x��ǥ
vector<int> my;    //�ִ� ���� ������ y��ǥ
vector<int> diry = { 0,1,0,-1 };
vector<int> dirx = { -1,0,1,0 };

void dfs(int x, int y, int cnt, int flag)
{

	if (ans < cnt) ans = cnt;

	for (int i = 0; i < 4; i++) //ó������ ���� for���� ������ �� for(int &i:dirx) for(int &y: diry)�� ���� �ð� �ʰ�!!!
	{
		if (x + dirx[i] < 0 || x + dirx[i] >= N || y + diry[i] < 0 || y + diry[i] >= N) continue;
		else if (visit[x + dirx[i]][y + diry[i]]) continue; //�湮�� �͵� üũ �ؾ���!!!
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
					mountain[x + dirx[i]][y + diry[i]] -= k; //�̰͵� ����� ����!!!

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
		start = time(NULL); // �ð� ���� ����

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				scanf("%d", &mountain[i][j]);
				if (maximum <= mountain[i][j])
				{
					//if (maximum < mountain[i][j] && xy != 0) //���� ��ġ�� �ִ� ������ ��ġ�� �ƴϿ��ٸ�
					//{
					//	mx.clear();
					//	my.clear();
					//	xy = 0; //�ʱ�ȭ ���ִ� �� �����ϱ� !!!
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

		end = time(NULL); // �ð� ���� ��
		printf("%f\n", (double)(end - start)); //��� ���

		for (int i = 0; i < xy; i++)
		{
			//printf("%d %d\n", mx[i], my[i]);
			dfs(mx[i], my[i], 0, 0);
		}

		printf("#%d %d\n", T, ans + 1);
	}
	return 0;
}