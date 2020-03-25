//https://goodgid.github.io/SWEA-4008/
#include<iostream>
using namespace std;

int n, num[12], oper[4], maximum, minimum;

void dfs(int nidx, int result, int p, int m, int mp, int d)
{
	if (nidx >= n)
	{
		if (maximum < result)
			maximum = result;
		if (minimum > result)
			minimum = result;
		return;
	}

	if (p) dfs(nidx + 1, result + num[nidx], p - 1, m, mp, d);
	if (m) dfs(nidx + 1, result - num[nidx], p, m - 1, mp, d);
	if (mp) dfs(nidx + 1, result * num[nidx], p, m, mp - 1, d);
	if (d) dfs(nidx + 1, result / num[nidx], p, m, mp, d - 1);
}

int main(int argc, char** argv)
{
	int test_case, T;
	freopen("sample_input.txt", "r", stdin);
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> n;

		for (int i = 0; i < 4; i++)
			cin >> oper[i]; //연산자 개수를 입력 받음

		for (int i = 0; i < n; i++)
			cin >> num[i]; // 숫자를 입력 받음

		maximum = -9999999; minimum = 9999999;
		dfs(1, num[0], oper[0], oper[1], oper[2], oper[3]);

		printf("#%d %d\n", test_case, maximum - minimum);
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}