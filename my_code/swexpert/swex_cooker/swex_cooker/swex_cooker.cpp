#include<iostream>
using namespace std;

int n, s[16][16], v[16], minimum;

void dfs(int idx, int cnt)
{
	if (cnt == (n / 2) - 1)
	{
		int cook1 = 0, cook2 = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (v[i] && v[j] && i != j)
					cook1 += s[i][j];

				else if ((!v[i]) && (!v[j]) && i != j)
					cook2 += s[i][j];
			}
		}
		if (abs(cook1 - cook2) < minimum)
			minimum = abs(cook1 - cook2);
		return;
	}

	for (int i = idx; i < n; i++)
	{
		if (v[i]) continue;
		v[i] = true;
		dfs(i+1, cnt+1);
		v[i] = false;
	}
}

int main(int argc, char** argv)
{
	int test_case, T; 
	freopen("sample_input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				scanf("%d", &s[i][j]);

		v[0] = true;
		minimum = 999999999;
		dfs(1, 0);
		printf("#%d %d\n", test_case, minimum);
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}