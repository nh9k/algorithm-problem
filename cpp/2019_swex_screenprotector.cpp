#include <iostream>
#include <cstring>
using namespace std;

int d, w, k;
bool protector[13][20] = { 0, }, changer[13][20] = { 0, };
bool perm[13];
int cnt;

bool checker() //검사
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
			if (presame >= k)  break;  //세로 한줄에서 이미 조건이 만족되었을 경우
			if (d - k < j && presame <= 1) return false; //세로 한줄에서 이미 조건이 만족되지 않았을 경우 
		}
	}
	return true;
}

void permutation(int c, int ones) //k의 최솟값(약품 바르는 횟수), 1의 개수
{
	for (int i = 0; i < c; i++)
	{
		if (i > c - ones - 1) perm[i] = 1;
		else perm[i] = 0;
	}
}

void dfs(int min, int dir, int idx) //하나씩 교환하는 함수: 약품 바르는 개수, permutation index
{
	if (checker()) {
		cnt = min;
		return;
	}
	if (dir >= min) return; //index를 다채우면 더이상 index 증가 안시킴

	for (int i = idx; i < d; i++) {

		for (int j = 0; j < w; j++) //약품 칠함
		{
			changer[i][j] = protector[i][j];
			protector[i][j] = perm[dir];
		}
		dfs(min, dir + 1, i+1); //permutation index를 하나씩 증가시키며 약품 칠한 개수만큼 까지만 시행하도록
		if (cnt > -1) return;

		for (int j = 0; j < w; j++) //약품 되돌림
		{
			protector[i][j] = changer[i][j];
		}
	}
}

void minimum()
{
	cnt = -1;
	for (int i = 0; i < d; i++) { //약품 바르는 개수
		for (int j = 0; j <= i; j++) { //약품을 바르는 개수 중에 1의 개수
			permutation(i, 0);
			for (int j = 0; j < d; j++)
				for (int h = 0; h < w; h++)
					changer[j][h] = 0;

			dfs(i, 0, 0); //약품바르는 개수와 permutation의 index
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
		else //약품바르는 횟수를 printf
		{
			minimum();
			printf("#%d %d\n", i + 1, cnt);
		}
	}
	return 0;
}