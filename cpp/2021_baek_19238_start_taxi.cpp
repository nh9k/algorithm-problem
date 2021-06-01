//https://www.acmicpc.net/problem/19238
//���� ��ȣ	���̵�	����	���	�޸�	�ð�	���	�ڵ� ����	������ �ð�
//28698684	nh9k	19238	�¾ҽ��ϴ�!!2024	280	C++17 / ����	2246
//���� Ǯ��: https://github.com/nh9k/algorithm-problem/blob/master/c%2B%2B/2020_baek_19238_start_taxi.cpp
//���� Ǯ�̿� ���� �ڵ���̸� �������� �ٿ����� �޸𸮵� ���ݴ� �ٿ�����, �ð��� 270ms �� �ɷȴ�. 
//�ð��� �����ϴ� ������ �ϵ��� ���� �޶����� �ʴ´ٸ�, ��� �ð��� �ٿ����� Ȯ���غ� �� �ϴ�.
//�����ġ�� �� ������ġ�� �Ǵ� �κ��� bfs ������ �� �˷����� �ʾƼ� ���� �ٲ��������.
//ver.2 ó�� ��ġ�� 1���� �����ؼ� ������������, �������� -1 ���־ ������ �ȴ�.


#include <iostream>
#include <vector>
#include <queue>

using namespace std;
int N, M;
int map[20][20], visit[20][20];
struct taxi {
	int x, y, fuel;
};
taxi t;
struct person{
	int x1, y1, x2, y2;
	bool end;
};
vector <person> p;
struct pri {
	int dist, x, y, idx;
};
struct cmp {
	bool operator()(pri &a, pri &b) {
		if (a.dist == b.dist) {
			if (a.x == b.x) {
				return a.y > b.y;
			}
			else
				return a.x > b.x;
		}
		else
			return a.dist > b.dist;
	}
};



int dx[] = { -1,0,1,0 };
int dy[] = { 0,1,0,-1 };
int bfs(int sx, int sy, int ex, int ey) {
	if (sx == ex && sy == ey) return 0; //�� ������ �� �־�� ��
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			visit[i][j] = 0;
		}
	}

	queue <pair<int, int>> q;
	q.push({ t.x, t.y });
	while (!q.empty()) {
		for (int i = 0; i < 4; ++i) {
			int mx = q.front().first + dx[i];
			int my = q.front().second + dy[i];

			if (mx < 0 || my < 0 || mx >= N || my >= N || map[mx][my] == 1 || visit[mx][my] != 0)
				continue;

			visit[mx][my] = visit[q.front().first][q.front().second] + 1;
			if (ex == mx && ey == my) return visit[mx][my];
			q.push({ mx, my });

		}
		q.pop();
	}
	return 1e9;
}

/*
//ver. 2
int bfs(int sx, int sy, int ex, int ey) {
	if (sx == ex && sy == ey) return 0; //�� ������ �� �־����
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			visit[i][j] = 0;
		}
	}

	queue <pair<int, int>> q;
	q.push({ t.x, t.y });
	visit[t.x][t.y] = 1;
	while (!q.empty()) {
		for (int i = 0; i < 4; ++i) {
			int mx = q.front().first + dx[i];
			int my = q.front().second + dy[i];

			if (mx < 0 || my < 0 || mx >= N || my >= N || map[mx][my] == 1 || visit[mx][my] != 0)
				continue;

			visit[mx][my] = visit[q.front().first][q.front().second] + 1;
			if (ex == mx && ey == my) return visit[mx][my] - 1;
			q.push({ mx, my });

		}
		q.pop();
	}
	return 1e9;
}
*/



int main() {
	cin >> N >> M >> t.fuel;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> map[i][j];
		}
	}
	
	cin >> t.x >> t.y;
	t.x -= 1;
	t.y -= 1;
	int tmpx1, tmpy1, tmpx2, tmpy2;
	for (int i = 0; i < M; ++i) {
		cin >> tmpx1 >> tmpy1 >> tmpx2 >> tmpy2;
		p.push_back({ tmpx1-1, tmpy1-1, tmpx2-1, tmpy2-1, false });
	}

	while (M != 0) {
		priority_queue <pri, vector<pri>, cmp> pq;

		//bfs for taxi to person
		for (int i = 0; i < p.size(); ++i) {
			if (p[i].end == false)
				pq.push({ bfs(t.x, t.y, p[i].x1, p[i].y1), p[i].x1, p[i].y1, i });
		}

		t.fuel -= pq.top().dist;
		if (t.fuel < 0) {
			cout << -1;
			return 0;
		}
		else {
			t.x = pq.top().x;
			t.y = pq.top().y;
		}
		
		//bfs for taxi to destination
		int end_dist = bfs(t.x, t.y, p[pq.top().idx].x2, p[pq.top().idx].y2);

		t.fuel -= end_dist;
		if (t.fuel < 0) {
			cout << -1;
			return 0;
		}
		else {
			t.fuel += end_dist * 2;
			t.x = p[pq.top().idx].x2;
			t.y = p[pq.top().idx].y2;
			p[pq.top().idx].end = true;
			M -= 1;
		}
	}
	cout << t.fuel;
}