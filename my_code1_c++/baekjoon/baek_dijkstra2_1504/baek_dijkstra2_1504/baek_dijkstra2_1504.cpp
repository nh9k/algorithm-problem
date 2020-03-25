#include <iostream>
#include <queue>
#include <vector>
#define maxv 801
#define maxe 200001
#define INF 987654321
using namespace std;

int v, e, must1, must2;
typedef struct node
{
	int end;
	int w;
}node;
vector<node> edge[maxv];
int dist[3][maxv];

void dijkstra(int start, int idx)
{
	//for (int i = 1; i <= v; i++)
	//	dist[idx][i] = INF;

	dist[idx][start] = 0; //1번 정점에서 start
	priority_queue <pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> calcost; //cost 와 정점
	calcost.push({ 0,start }); //시작은 weight = 0, 

	int now_node, now_cost;
	while (!calcost.empty())
	{
		now_cost = calcost.top().first;
		now_node = calcost.top().second;
		calcost.pop();

		int new_cost, post_cost;
		for (int k = 0; k < edge[now_node].size(); k++)
		{
			new_cost = dist[idx][now_node] + edge[now_node][k].w;
			post_cost = dist[idx][edge[now_node][k].end];

			if (new_cost < post_cost)
			{
				dist[idx][edge[now_node][k].end] = new_cost;
				calcost.push({ new_cost, edge[now_node][k].end });
			}
		}
	}
	return;
}

int main()
{
	//freopen("sample_input.txt", "r", stdin);
	scanf("%d %d", &v, &e);
	int from, to, cost;
	for (int i = 0; i < e; i++)
	{
		scanf("%d %d %d", &from, &to, &cost);
		edge[to].push_back({ from ,cost }); //양방향
		edge[from].push_back({ to, cost });
	}
	scanf("%d %d", &must1, &must2);

	for (int i = 0; i < 3; i++) {
		fill(dist[i], dist[i] + v + 1, INF);
	}

	dijkstra(1, 0); //1~v
	dijkstra(must1, 1);// must1~v
	dijkstra(must2, 2); //must2~v
	//1->must1->must2->v  VS  1->must2->must1->v
	unsigned int minimum = min(dist[0][must1] + dist[1][must2] + dist[2][v], dist[0][must2] + dist[2][must1] + dist[1][v]);

	if (minimum >= INF) printf("-1\n");
	else
	{
		printf("%d\n", minimum);
	}

	return 0;
}