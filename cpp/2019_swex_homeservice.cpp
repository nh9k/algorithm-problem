#include <iostream>

int n, m;
bool map[20][20];

int scan(int k,int i,int j)
{
	int col = 1;
	int home = 0;
	for (int q = i - (k - 1); q <= i; q++)
	{
		for (int w = j - (col - 1); w <= j + (col - 1); w++)
		{
			if (q<0 || w<0 || q>n - 1 || w>n - 1) continue;
			if (map[q][w] == 1)
				home++;
		}
		col++;
	}
	col = 1;
	for (int q = i + (k - 1); q > i; q--)
	{
		for (int w = j - (col - 1); w <= j + (col - 1); w++)
		{
			if (q<0 || w<0 || q>n - 1 || w>n - 1) continue;
			if (map[q][w] == 1)
				home++;
		}
		col++;
	}
	if (((m*home) - ((k*k) + ((k - 1)*(k - 1)))) >= 0)
	{
		return home;
	}
	else return 0;
}

int service()
{
	int K = (n + 1);
	int max = 0, chk = 0;

	for (int k = 1; k <= K; k++)
	{
		for (int i = 0; i < n ; i++)
		{
			for (int j = 0; j < n; j++)
			{
				chk = scan(k, i, j);
				if (max < chk)
				{
					max = chk;
				}
			}
		}
	}
	return max;
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
	{
		scanf("%d %d", &n, &m);
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				scanf("%d", &map[j][k]);
		
		printf("#%d %d\n", i + 1, service());
	}
	return 0;
}