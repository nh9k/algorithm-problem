//제출 번호	아이디	문제	결과	메모리	시간	언어	코드 길이	제출한 시간
//28658329	nh9k	16236	맞았습니다!!2156	0	C++17 / 수정	2415	20초 전
//priority_queue를 사용할 수 있어야함.
//-> 4방향 모두 탐색후 시간 제일 적은 순, 위쪽, 왼쪽, 오른쪽, 아랫쪽 순으로 봐야함.
//-> 이 순서로 봐도, 처음이 아닌 다음 값으로 널리널리 퍼질 경우 4방향 모두 보고 priority queue를 사용하지 않을 경우 문제가 생김!
//greater의 경우 top이 최솟값인 경우로 사용
//cmp의 경우: >가 top이 최솟값으로 사용


#include <iostream>
#include <queue>
using namespace std;
int n, max_time, fish_n;
int map[20][20], visit[20][20];
typedef struct {
	int x, y, gram;
}pos;
typedef struct {
	int time, x, y;
}pri;
pos shark;
int dx[] = { -1, 0, 0, 1 };
int dy[] = { 0, -1, 1, 0 };


struct cmp {
	bool operator()(pri &a, pri &b) {
		if (a.time == b.time) {
			if (a.x == b.x) {
				return a.y > b.y;
			}
			else
				return a.x > b.x;
		}
		else
		{ //오름차순
			return a.time > b.time;
		}
	}
};



bool is_visit(int x, int y) {
	if (visit[x][y] != -1)
		return true;
	return false;
}

bool is_outrange(int x, int y) {
	if (x < 0 || y < 0 || x >= n || y >= n) {
		return true;
	}
	return false;
}

bool is_bigfish(int x, int y) {
	if (map[x][y] > shark.gram) {
		return true;
	}
	return false;
}

void shark_moving(int x, int y, int time, int ate_n, int cur_n) {
	if (max_time < time) {
		max_time = time;
	}

	if (fish_n <= ate_n) {
		return;
	}

	//cout << endl;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			visit[i][j] = -1;
			//cout << map[i][j];
		}//cout << endl;
	}

	queue <pair<int, int>> chk;
	priority_queue <pri, vector<pri>, cmp> q;

	chk.push({ x,y });
	visit[x][y] = 0;

	while (!chk.empty()) {
		int chk_sz = chk.size();
		for (int qi = 0; qi < chk_sz; ++qi) {
			for (int i = 0; i < 4; ++i) {
				int mx = chk.front().first + dx[i];
				int my = chk.front().second + dy[i];

				if (is_outrange(mx, my) || is_visit(mx, my) || is_bigfish(mx, my)) continue;

				visit[mx][my] = visit[chk.front().first][chk.front().second] + 1;
				q.push({ visit[mx][my], mx, my });
			}
			chk.pop();
		}

		while (!q.empty()) {
			if (map[q.top().x][q.top().y] != 0 && (map[q.top().x][q.top().y] < shark.gram)) {
				cur_n++;
				if (cur_n == shark.gram) {
					shark.gram += 1;
					cur_n = 0;
				}

				map[q.top().x][q.top().y] = 0;
				shark_moving(q.top().x, q.top().y, time + visit[q.top().x][q.top().y], ate_n + 1, cur_n);
				if (max_time != 0) return;
			}
			chk.push({ q.top().x , q.top().y });
			q.pop();
		}
	}

}


int main() {
	cin >> n;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> map[i][j];
			if (map[i][j] == 9) {
				shark.x = i;
				shark.y = j;
				shark.gram = 2;
				map[i][j] = 0;
			}
			else if (map[i][j] != 0)
				fish_n++;
		}
	}


	shark_moving(shark.x, shark.y, 0, 0, 0);
	cout << max_time << endl;
}