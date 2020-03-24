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
		size = subin.size(); //�̰� for ������ �ٷ� ����� ��� for ���ǹ� �˻��� �� ���� ���� ��� �ϴ� ����!!!
		for (int i = 0; i < size; i++)
		{
			p = subin.front();
			subin.pop();
			//visit[p] = false; // �湮 üũ�� �ϰ� �ٽ� ���� �ʿ䰡 ����. �湮�� ���� �ƿ� �� �ʿ䰡 ����(tree)!!!
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
