#include <iostream>
#include <cstring>
using namespace std;

int d, w, k;
bool protector[13][20] = { 0, }, changer[13][20] = { 0, };
bool perm[13];
int cnt;

bool checker() //�˻�
{
	int mem, presame;
	for (int i = 0; i < w; i++)
	{
		mem = protector[0][i];
		presame = 0;
		for (int j = 0; j < d; j++)
		{
			if (mem == protector[j][i])
			{
				presame++;
			}
			else
			{
				presame = 1;
				mem = protector[j][i];
			}
			if (presame >= k)  break;  //���� ���ٿ��� �̹� ������ �����Ǿ��� ���
			if (d - k < j && presame <= 1) return false; //���� ���ٿ��� �̹� ������ �������� �ʾ��� ��� 
		}
	}
	return true;
}

void permutation(int c, int ones) //k�� �ּڰ�(��ǰ �ٸ��� Ƚ��), 1�� ����
{
	for (int i = 0; i < c; i++)
	{
		if (i > c - ones - 1) perm[i] = 1;
		else perm[i] = 0;
	}
}

void dfs(int min, int dir, int idx) //�ϳ��� ��ȯ�ϴ� �Լ�: ��ǰ �ٸ��� ����, permutation index
{
	if (checker()) {
		cnt = min;
		return;
	}
	if (dir >= min) return; //index�� ��ä��� ���̻� index ���� �Ƚ�Ŵ

	for (int i = idx; i < d; i++) {

		for (int j = 0; j < w; j++) //��ǰ ĥ��
		{
			changer[i][j] = protector[i][j];
			protector[i][j] = perm[dir];
		}
		dfs(min, dir + 1, i+1); //permutation index�� �ϳ��� ������Ű�� ��ǰ ĥ�� ������ŭ ������ �����ϵ���
		if (cnt > -1) return;

		for (int j = 0; j < w; j++) //��ǰ �ǵ���
		{
			protector[i][j] = changer[i][j];
		}
	}
}

void minimum()
{
	cnt = -1;
	for (int i = 0; i < d; i++) { //��ǰ �ٸ��� ����
		for (int j = 0; j <= i; j++) { //��ǰ�� �ٸ��� ���� �߿� 1�� ����
			permutation(i, 0);
			for (int j = 0; j < d; j++)
				for (int h = 0; h < w; h++)
					changer[j][h] = 0;

			dfs(i, 0, 0); //��ǰ�ٸ��� ������ permutation�� index
			if (cnt > -1) return;
		}
	}
	cnt = d;
	return;
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	int t;
	scanf("%d", &t);

	for (int i = 0; i < t; i++)
	{
		scanf("%d %d %d", &d, &w, &k);

		for (int j = 0; j < d; j++)
			for (int h = 0; h < w; h++)
				protector[j][h] = 0;

		for (int j = 0; j < d; j++)
			for (int h = 0; h < w; h++)
				scanf("%d", &protector[j][h]);

		if (k == 1)
			printf("#%d %d\n", i + 1, 0);
		else //��ǰ�ٸ��� Ƚ���� printf
		{
			minimum();
			printf("#%d %d\n", i + 1, cnt);
		}
	}
	return 0;
}