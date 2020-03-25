//baekjoon 10971 외판원 순회2
//https://www.acmicpc.net/problem/10971

#include <iostream>
#include <algorithm>
#include <vector> 
using namespace std;

int N, minimum, mem;
vector<vector<int>> W;
vector <int> Num;

int main()
{
	N = 0; // 도시의 수
	mem = 1000000001; //초기화

	scanf("%d", &N);
	W.assign(N, vector<int>(N, 0));
	Num.assign(N+1, 0);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			scanf("%d", &W[i][j]);
		Num[i] = i;
	}
	do {
		minimum = 0;
		Num[N] = Num[0];
		for (int i = 0; i < N; i++) {
		
			if (W[Num[i]][Num[i+1]] == 0) {
				minimum = 10000000; break;
			}
			minimum += W[Num[i]][Num[i + 1]];
		}
		if (mem > minimum) mem = minimum;
	} while (next_permutation(Num.begin(), Num.end()-2)); 

	printf("%d\n", mem);
	return 0;
}