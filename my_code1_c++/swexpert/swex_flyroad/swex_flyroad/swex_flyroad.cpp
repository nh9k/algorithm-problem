#include <iostream>
#include <vector>
using namespace std;

int n, x;
int map[20][20];
int map2[20][20];

int scanner()
{
	int mem, sum = 0;
	int cnt, f1, ff;
	for (int i = 0; i < n; i++) //���η� ��ĵ
	{
		mem = map[0][i];
		f1 = 0, ff = 0; //��� ���� �ʱ�ȭ ���� ���
		cnt = 0;
		for (int j = 0; j < n; j++)
		{
			if (mem == map[j][i])
			{
				cnt++;
				if (f1 == 1)
				{
					if (cnt >= x) {
						ff = 1;
						f1 = 0; cnt = 0;
					}
				}
				if (cnt == n) ff = 1;
			}
			else
			{
				if (mem > map[j][i] && mem <= map[j][i] + 1) //������ ���� �� �϶� //�ΰ� ���� ���̸� ������.
				{
					if (f1 == 1) //�ϰ� ���� ��ġ�Ϸ� ������ �� �ϰ��϶�
					{
						ff = 0; break;
					}
					else f1 = 1; ///ó������ ���� ���� ������ ��
				}
				else if (mem < map[j][i] && mem >= map[j][i] - 1) //������ ū �� �϶� //�ΰ� ū���̸� ������.
				{
					if (f1 == 1) { //�ϰ� ���� ��ġ�Ϸ� ������ ����϶� 
						ff = 0; break;
					}
					else if (cnt >= x)
					{
						if (j - x - 1 < 0) ff = 1; //�迭 ���̸�
						else {					   //�迭 ���̸�
							if (map[j - x - 1][i] == map[j - x][i])
							{
								ff = 1; map[j - 1][i] = map[j][i]; //���� ��ġ
							}
						}
					}
					else //�������� ū���� ���ö�
					{
						ff = 0;
						break;
					}
				}
				else { //�ΰ� �̻� ����� ���
					ff = 0;
					break;
				}
				cnt = 1;
				mem = map[j][i];
			}
		}
		if (f1 == 1) ff = 0;
		if (ff == 1) {
			//printf("1");
			sum += 1;
		}
		//else
			//printf("0");
	}
	//printf("����:: %d    ", sum);

	for (int i = 0; i < n; i++) //���η� ��ĵ.
	{
		mem = map2[i][0];
		f1 = 0, ff = 0; //��� ���� �ʱ�ȭ ���� ���
		cnt = 0;
		//printf("i::%d\n", i);
		for (int j = 0; j < n; j++)
		{
			if (mem == map2[i][j])
			{
				cnt++;
				if (f1 == 1)
				{
					if (cnt >= x) {
						ff = 1;
						f1 = 0; cnt = 0;
					}
				}
				if (cnt == n) ff = 1;
			}
			else
			{
				if (mem > map2[i][j] && mem <= map2[i][j] + 1) //������ ���� �� �϶� //�ΰ� ���� ���̸� ������.
				{
					if (f1 == 1) { // �ϰ� ���� ��ġ�ؾ��ϴ� �� ������ �ƴ� ���
						ff = 0;
						break;
					}
					else f1 = 1; ///ó������ ���� ���� ������ ��
				}
				else if (mem < map2[i][j] && mem >= map2[i][j] - 1) //������ ū �� �϶� //�ΰ� ū���̸� ������.
				{
					if (f1 == 1) { //�ϰ� ���� ��ġ�Ϸ� ������ ����϶� 
						ff = 0; break;
					}
					else if (cnt >= x)
					{
						if (j - x - 1 < 0) ff = 1; //�迭 ���̸�
						else {					   //�迭 ���̸�
							if (map2[i][j - x - 1] == map2[i][j - x])
							{
								ff = 1; map2[i][j - 1] = map2[i][j];
							}
						}
					}
					else //�������� ū���� ���ö�
					{
						ff = 0;
						break;
					}
				}
				else { //�ΰ� �̻� ����� ��� ����ؾ� ��
					ff = 0;
					break;
				}
				cnt = 1;
				mem = map2[i][j];
			}
		}
		if (f1 == 1) ff = 0;
		if (ff == 1) {
			//printf("1");
			sum += 1;
		}
		//else
			//printf("0");
	}
	//printf("����:: %d    ", sum);

	return sum;
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
	{
		scanf("%d %d", &n, &x);

		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
			{
				scanf("%d", &map[j][k]);
				map2[j][k] = map[j][k];
			}

		//visit.assign(n, 0);
		printf("#%d %d\n", i + 1, scanner());
	}
	return 0;
}