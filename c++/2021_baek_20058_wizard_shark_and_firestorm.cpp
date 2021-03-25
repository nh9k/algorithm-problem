//https://www.acmicpc.net/problem/20058
//제출 번호	아이디	문제	결과	메모리	시간	언어	코드 길이	제출한 시간
//27687381	nh9k	20058	맞았습니다!!2240	44	C++17 / 수정	2709
//풀이시간: 약 2시간
//주의사항1) 인접 얼음이 3개 미만일 시 -1 하는 코드에서 확인하고자하는 얼음 중심이 0인 경우는 pass하기
//주의사항2) answer2(가장 큰 덩어리)를 풀때 인접 얼음으로 가는 건 bfs를 사용해야 + 초기에는 습관처럼 dfs 사용함
//주의사항3) bfs 사용시 방문한 곳을 또 방문할 필요 없음. 중복 체크 조심!

#include <iostream>
#include <queue>
#include <math.h>
using namespace std;

int map[64][64], newmap[64][64];
bool chk[64][64];
int N;
queue<int> Q;
int answer2;

void rotate_map(int x, int y, int q) {
	for (int i = x; i < x + q; ++i) {
		for (int j = y; j < y + q; ++j) {
			newmap[x+(j-y)][y+q-1-(i-x)] = map[i][j];
		}
	}
}

bool out_range(int x, int y) {
	if ((x < 0) || (y < 0) || (x >(N - 1)) || (y >(N - 1))) return false;
	return true;
}

int ice_bfs(int x, int y) {
	int cnt = 0;

	if ((newmap[x - 1][y] > 0) && out_range(x - 1,y)) cnt++;
	if ((newmap[x + 1][y] > 0) && out_range(x + 1, y)) cnt++;
	if ((newmap[x][y - 1] > 0) && out_range(x, y - 1)) cnt++;
	if ((newmap[x][y + 1] > 0) && out_range(x, y + 1)) cnt++;

	return cnt;
}

void ice_chk() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (newmap[i][j] <= 0) chk[i][j] = false;
			else if (ice_bfs(i, j) < 3) chk[i][j] = true;
			else chk[i][j] = false;
		}
	}

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (chk[i][j])
			{
				map[i][j] = newmap[i][j] - 1;
			}
			else
			{
				map[i][j] = newmap[i][j];
			}
			chk[i][j] = false;
		}
	}
}

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

void area_ice(int x, int y, int curans) {
	if (chk[x][y]) return;
	else if (map[x][y] <= 0) {
			chk[x][y] = true;
			return;
		}
	else{
		queue <pair<int, int>> pos;
		pos.push({ x,y });
		chk[pos.front().first][pos.front().second] = true;

		while (!pos.empty())
		{

			for (int i = 0; i < 4; ++i) {
				int mx = pos.front().first + dx[i];
				int my = pos.front().second + dy[i];
				if (!out_range(mx, my))
					continue;
				else if (chk[mx][my])
					continue;
				else if (map[mx][my] <= 0)
				{
					chk[mx][my] = true;
					continue;
				}
				else
				{
					curans++;
					pos.push({ mx, my });
					chk[mx][my] = true;
				}
			}
			pos.pop();
		}
		if (curans > answer2) {
			answer2 = curans;
		}
	}
}



int main() {
	int tmpQ, tmpvalue;
	cin >> N >> tmpQ;
	N = pow(2, N);
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> map[i][j];
		}
	}
	for (int i = 0; i < tmpQ; ++i)
	{
		cin >> tmpvalue;
		Q.push(pow(2, tmpvalue));
	}

	while (!Q.empty())
	{
		for (int i = 0; i < (N / Q.front()); ++i) {
			for (int j = 0; j < (N / Q.front()); ++j) {
				rotate_map(i*Q.front(), j*Q.front(), Q.front());
			}
		}

		ice_chk();
		Q.pop();
	}

	int answer1 = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			answer1 += map[i][j];
		}
	}
	cout << answer1 << endl;

	answer2 = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			area_ice(i, j, 1);
		}
	}
	cout << answer2 << endl;

	return 0;
}