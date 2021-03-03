//재귀(dfs) combination 관련 알고리즘 https://yabmoons.tistory.com/99
#include <iostream>
#include <vector>	 //벡터 사용
#include <algorithm> //순열 사용, sort 사용

using namespace std;
vector <int> memb;
vector <int> visit;
int check;

void dfs(int idx,int cnt)
{
	if (cnt == 6) //6개를 뽑으므로
	{
		for (int i = 0; i < check; i++)
			if(visit[i]==true) printf("%d ", memb[i]);		
		printf("\n");
		return;
	}
	for (int i = idx; i < check; i++)
	{
		//if (visit[i] == true) continue; //이거 대신 dfs(i+1, cnt+1)을 넣어줌
		visit[i] = true;
		dfs(i+1, cnt + 1);
		visit[i] = false;
	}
	
}

int main(void)
{
	check = 1;
	while (check)
	{
		scanf("%d", &check);
		if (check == 0) break;

		memb.assign(check, 0);
		visit.assign(check, 0);

		for (int i = 0; i < check; i++)
			scanf("%d", &memb[i]);

		dfs(0,0);
		printf("\n");
	}
	return 0;
}
