#include <iostream>  //0.00678s // ����: https://2youngjae.tistory.com/139
#include <vector>

using namespace std;

int n, m, k;
int maxnum, maxdir, sumnum;
int mx[5] = { 0,-1,1,0,0 };
int my[5] = { 0,0,0,-1,1 };
vector<vector<int>> gunzip, map;

void scaning() //������ġ0, ������ġ1, �̻��� ��2, �̵�����3
{
	map.assign(n, vector<int>(n, 0));

	for (int i = 0; i < k; i++) //������ ��ġ ����
	{
		if (gunzip[i][2] != 0) { //�̻����� 0���� �� ���� ���̻� �̵���Ű�� ���� !!! �ǵ��� ����
			gunzip[i][0] += mx[gunzip[i][3]];
			gunzip[i][1] += my[gunzip[i][3]];
			map[gunzip[i][0]][gunzip[i][1]] += 1;
		}
	}

	for (int i = 0; i < k; i++)
	{
		if (gunzip[i][2] != 0) //�̻����� 0�� �ƴ� �͸� Ȯ�� �Ѵ�.
		{
			if (gunzip[i][0] >= 1 && gunzip[i][0] <= n - 2 && gunzip[i][1] >= 1 && gunzip[i][1] <= n - 2) //�̵� �� �׵θ��� �ƴ� ��� 
			{
				//������ ��ġ�� �ڵ�
				//�̻��� ��ġ��, ���� ū �� ���� ���� ����, �������� �̻��� 0
				if (map[gunzip[i][0]][gunzip[i][1]] > 1) //������ �������� ���
				{
					maxnum = 0; maxdir = 0; sumnum = 0;
					for (int j = 0; j < k; j++) //�ִ� ������ ã�� ���� for��
					{
						if (gunzip[j][0] == gunzip[i][0] && gunzip[j][1] == gunzip[i][1]) //map�� ������ �ִ� ������ ��ġ�� ���� ���
						{
							sumnum += gunzip[j][2]; //������ ��ħ
							if (maxnum < gunzip[j][2])
							{
								maxnum = gunzip[j][2]; //�ִ� ������ ã��
								maxdir = gunzip[j][3];
							}
						}
					}
					for (int j = 0; j < k; j++) //�ִ� ���� �ܿ� �������� �Ҹ��ϱ� ���� for��
					{
						if (gunzip[j][0] == gunzip[i][0] && gunzip[j][1] == gunzip[i][1]) //map�� ������ �ִ� ������ ��ġ�� ���� ���
						{
							if (maxnum != gunzip[j][2])
							{
								gunzip[j][2] = 0; //���� �Ҹ�
							}
							else
							{
								gunzip[j][2] = sumnum;
								gunzip[j][3] = maxdir;
							}
						}
					}
				}
			}
			else if (gunzip[i][0] >= 0 && gunzip[i][0] <= n - 1 && gunzip[i][1] >= 0 && gunzip[i][1] <= n - 1) //�̵� �� �׵θ��� ���
			{
				//gunzip[i][2] = floor(float(gunzip[i][2]) / 2.0); // �̻��� �� ���� //1�� �� 0 �Ǵ��� ����
				gunzip[i][2] = gunzip[i][2] / 2;
				if (gunzip[i][3] == 1) gunzip[i][3] = 2; //���� ����
				else if (gunzip[i][3] == 2) gunzip[i][3] = 1;
				else if (gunzip[i][3] == 3) gunzip[i][3] = 4;
				else if (gunzip[i][3] == 4) gunzip[i][3] = 3;
			}
		}
	}
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
	{
		scanf("%d %d %d", &n, &m, &k);

		gunzip.assign(k, vector<int>(4, 0));
		for (int j = 0; j < k; j++)
			scanf("%d %d %d %d", &gunzip[j][0], &gunzip[j][1], &gunzip[j][2], &gunzip[j][3]);

		for (int j = 0; j < m; j++) //�ð� ����
			scaning();

		int ans = 0;
		for (int j = 0; j < k; j++)
			ans += gunzip[j][2];

		printf("#%d %d\n", i + 1, ans);
	}
	return 0;
}