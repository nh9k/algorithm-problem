#include <iostream>
//#include <vector>
//using namespace std;

int map[350][350], visit[350][350];
//vector<vector<int>> map, visit;
int n, m, k;
int dx[4] = { -1,0,1,0 }; //�������
int dy[4] = { 0,1,0,-1 };


void pluscell(int i, int j)
{
	for (int h = 0; h < 4; h++)
	{	
		if (visit[i + dx[h]][j + dy[h]] != -1) 
			continue; //������ �̹� ���� ���̸�,
		if (map[i][j] <= map[i + dx[h]][j + dy[h]] && visit[i + dx[h]][j + dy[h]] == -1) 
			continue; //�̹� �� ū ������ ���Ǿ��ִµ� ��� ����� �Ÿ� 
		
		map[i + dx[h]][j + dy[h]] = map[i][j];
	}		
}

void check() //���� + �˻��� map�� ������ ����Ű�� �Լ�
{
	for (int i = 0; i < n + k; i++) //����
	{
		for (int j = 0; j < m + k; j++)
		{
			if (map[i][j] == 0) continue; // ��� �ȵȰ�
			if (visit[i][j] > 2*map[i][j]) continue; //�̹� ���� ����

			visit[i][j] += 1;
		}
	}
	for (int i = 0; i < n + k; i++) //�˻�
	{
		for (int j = 0; j < m + k; j++)
		{
			if (map[i][j] == 0) continue; // ��� �ȵȰ�
			if (visit[i][j] > map[i][j]) continue; //�̹� ��� ���� ����

			if (map[i][j] == visit[i][j])//������ �ð�
				pluscell(i, j); //�ֺ��� ����
		}
	}
}

int result() //��ü map�� ���鼭 ����� ��ü �ٱ� ������ ������ ���� �Լ�
{
	int cnt = 0;
	for (int i = 0; i < n + k; i++)
	{
		for (int j = 0; j < m + k; j++)
		{
			if (2*map[i][j]-1 > visit[i][j] && map[i][j]!= 0 )
			{
				cnt++;
			}
		}
	}
	return cnt;
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	int testcase;
	scanf("%d", &testcase);
	for (int i = 0; i < testcase; i++)
	{
		scanf("%d %d %d", &n, &m, &k);

		//map.assign(n + k, vector<int>(m + k, 0));
		//visit.assign(n + k, vector<int>(m + k, -1));
		for (int j = 0; j < k + n; j++)
		{
			for (int h = 0; h < k + m; h++)
			{
				map[j][h] = 0;
				visit[j][h] = -1;
			}
		}

		for (int j = 0; j < n; j++)
			for (int h = 0; h < m; h++)
				scanf("%d", &map[k / 2 + j][k / 2 + h]);

		for (int j = 0; j < k; j++)
			check();

		printf("#%d %d\n", i + 1, result());
	}
	return 0;
}