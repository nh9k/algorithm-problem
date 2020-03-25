#include <iostream>
#include <queue>

using namespace std;
int n, k;
queue<int> subin;
vector<int> visit;

void visiting(int position)
{
	if (position >= 0 && position <= 100000)
	{
		if (visit[position] != true)
		{
			visit[position] = true;
			subin.push(position);
		}
	}
}

int bfs(int n, int k)
{
	subin.push(n);
	visit.assign(100001, 0);
	visit[n] = true;
	
	int time = 0;
	int p, size;
	while (1)
	{
		size = subin.size(); //이걸 for 문에서 바로 계산할 경우 for 조건문 검사할 때 마다 새로 계산 하니 조심!!!
		for (int i = 0; i < size; i++)
		{
			p = subin.front();
			subin.pop();
			//visit[p] = false; // 방문 체크를 하고 다시 꺼줄 필요가 없음. 방문한 곳은 아에 갈 필요가 없음(tree)!!!
			//printf("p::%d\n", p);
			//printf("time::%d\n", time);
			if (p == k) return time;
			else {
				visiting(p - 1);
				visiting(p + 1);
				visiting(2 * p);
			}
		}
		time += 1;
	}
}

int main(void)
{
	scanf("%d %d", &n, &k);
	printf("%d\n",bfs(n, k));

	return 0;
}
