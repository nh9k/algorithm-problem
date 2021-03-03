//���(dfs) combination ���� �˰��� https://yabmoons.tistory.com/99
#include <iostream>
#include <vector>	 //���� ���
#include <algorithm> //���� ���, sort ���

using namespace std;
vector <int> memb;
vector <int> visit;
int check;

void dfs(int idx,int cnt)
{
	if (cnt == 6) //6���� �����Ƿ�
	{
		for (int i = 0; i < check; i++)
			if(visit[i]==true) printf("%d ", memb[i]);		
		printf("\n");
		return;
	}
	for (int i = idx; i < check; i++)
	{
		//if (visit[i] == true) continue; //�̰� ��� dfs(i+1, cnt+1)�� �־���
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
