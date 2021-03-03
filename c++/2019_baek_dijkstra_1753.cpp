#include <iostream>
#include <queue>
#include <vector>
#define maxv 20001 //이거 왜 20001인지 이해하기			@@왜냐면 20000번째 정점을 넣기 위함 1부터 20000의 정점이 있으므로,
#define maxe 300001
#define INF 1e9
using namespace std;

int v, e, start;
int dist[maxv] = { 0, };

typedef struct node
{
	int end; //end node
	int w; //weight(edge of from to end)
}node;
vector<node> edge[maxe]; //정확한 index가 maxe가 맞는지 이해하기		@@maxv를 넣어야 함 왜냐면 index가 노드에 대해서 이기때문

void dijkstra()
{
	dist[start] = 0;
	priority_queue <pair<int, int>, vector<pair<int, int>>,greater<pair<int, int>>> calcost;
	calcost.push({ 0,start }); //vertex의 cost와 vertex를 넣음

	int cost, now_node;
	while (!calcost.empty()) //이게 왜 가능할지, pop()을 하나씩 해도 가능한지 이해하기			@@
	{
		cost = calcost.top().first;
		now_node = calcost.top().second; //now_node가 출발 vertex
		calcost.pop();

		int new_cost, before_cost;
		for (int i = 0; i < edge[now_node].size(); i++) 
		{
			new_cost = dist[now_node] + edge[now_node][i].w;  //출발 vertex + edge
			before_cost = dist[edge[now_node][i].end]; //원래 도착 vertex

			if (new_cost < before_cost) //새로 계산한 cost가 더 작다면
			{
				dist[edge[now_node][i].end] = new_cost; 
				calcost.push({ new_cost, edge[now_node][i].end }); //도착 vertex의 cost를 new_cost로 갱신
			}
		}

	}
}
int main()
{
	freopen("sample_input.txt", "r", stdin);
	scanf("%d %d", &v, &e); //number of vertex, edge
	scanf("%d", &start); //start node

	int from, to, cost;
	for (int i = 0; i < e; i++)
	{
		scanf("%d %d %d", &from, &to, &cost);
		edge[from].push_back(node{ to, cost });
	}
	for (int i = 1; i <= v; i++) //initialization of each vertex cost
		dist[i] = INF;

	dijkstra();

	for (int i = 1; i <= v; i++) //이거 왜 <= 인지 이해하기 20001과 관련 있는가? 							@@
	{
		if (dist[i] != INF) printf("%d\n", dist[i]);
		else printf("INF\n");
	}

	return 0;
}

//소스 참고: http://melonicedlatte.com/algorithm/2018/03/04/061153.html

//시간 복잡도
//하나는 각 정점마다 인접한 간선들을 모두 검사하는 작업이고,
//다른 하나는 우선순위 큐에 원소를 넣고 삭제하는 작업입니다.
//각 정점은 정확히 한 번씩 방문되고, 따라서 모든 간선은 한 번씩
//검사된다는 사실을 떠올리면 간선들을 검사하는 데는
//전체 O(| E | )의 시간이 걸립니다.
//우선순위 큐가 가장 커지는 최악의 시나리오는
//그래프의 모든 간선이 검사될 때마다 dist[]가 갱신되고
//우선순위 큐에 정점의 번호가 추가되는 것입니다.
//이때 추가는 각 간선마다 최대 한 번 일어나기 때문에,
//우선순위 큐에 추가되는 원소의 수는 최대 O(| E | )의 시간이 걸리고,
//O(| E | )개의 원소에 대해 이 작업을 하려면 전체 시간 복잡도는
//O(| E || log | E | )가 됨을 알 수 있습니다.
//이 두 작업에 걸리는 시간을 더하면
//O(| E || log | E | )가 됩니다만,
//대개의 경우 그래프에서 간선의 개수
//| E | 는 | V | ^ 2보다 작기 때문에
//O(log | E | ) = O(log | V | )라고 볼 수 있습니다.
//따라서 시간 복잡도는 O(| E || log | V | )가 됩니다.


//(1) 왜 우선순위 큐를 쓸까 ?
//
//결론적으로 말해서 최소거리 값 갱신 횟수의 증가때문이다.먼저 우선순위 큐를 쓰지 않고 일반 큐를 써도 결과
//
//에는 차이가 없다.하지만 우선순위 큐를 쓰는 이유는 속도에 이점이 있기 때문이다.다익스트라 알고리즘에서
//
//속도에 영향을 주는 요소는 큐에서 노드를 꺼내오는 횟수와 우선순위 큐의 갱신 횟수이다.이게 무슨 뜻이냐면
//
//예를들어 보자.만약 위의 예제에서 일반 큐를 쓴다면 A에서 검사를 시작할 때, 연결된 두 노드 B와 C중 B부터
//
//검사한다.하지만 우선순위 큐라면 C부터 검사한다.왜냐하면 우선순위 큐로 인해 최소 거리로 정렬된 순서로
//
//큐에서 추출되기 때문이다.이 상황을 정리하면
//
//
//
//A에서 E까지 최소거리를 검사할 때
//
//일반 큐)
//
//A->B->C->E->B->D->E->E 순으로 검사
//
//첫 번째 E 노드를 검사할 때, 현재 B까지 최소거리는 4, C까지 최소거리는 1, E까지 최소거리는 8이 된다.
//
//하지만 그 다음 B노드를 검사할 때 B의 최소거리가 3으로 갱신되기 때문에 이전에 계산한 작업이
//
//무의미한 값이 된다.이런 경우가 일반 큐를 사용할 때 나타나는 시간상의 비효율적인 대표 예이다.
//
//
//
//우선순위 큐)
//
//A->C->B->B->D->E->E->E 순으로 검사
//
//이 검사는 이전에 계산해둔 값이 그 단계에서 최소값이라는 것이 보장되기 때문에 갱신 횟수가 현저히 적어진다.
//
//
//
//이해를 돕기위한 작은 예지만 그래프의 크기가 커지면 커질수록 이런 일반 큐와 우선순위 큐 사이의 중복갱신
//
//횟수가 일반큐가 월등히 많아지게 된다.그러므로 최종적으로 일반 큐에서는 O(E + V ^ 2)에서 우선순위 큐 사용 시
//
//O(ElogV)으로 시간상의 이점이 발생하게 된다. (V는 정점 수, E는 엣지 수)
//
//
//
//(2) 왜 음의 가중치는 계산을 못할까 ?
//
//결론적으로 말해서 그 이유는 이전 노드까지 계산해둔 최소거리 값이 최소라고 보장할 수 없기 때문이다.
//
//다익스트라는 정점을 지날수록 가중치가 증가한다 라는 사실을 전제하고 쓰여진 알고리즘이다.하지만 음의
//
//가중치가 있다면 정점을 지날수록 가중치가 감소할 수도 있다는 의미가 되므로 앞선 전제가 무너진다.그러므로
//
//다익스트라 알고리즘에서는 음의 가중치를 계산할 수 없다.하지만 이와같은 점을 음의 가중치에서도 최소거리를
//
//계산하는 벨만 - 포드 알고리즘이 존재한다.
//
//출처: https://makefortune2.tistory.com/26 [Simple in Complex with Simple]