//1시간 16분 풀이
//mx = i + dx[fire_map[i][j][k].d] * (fire_map[i][j][k].s%N); 에서 N으로 나눠주지 않아 메모리 초과
#include <iostream>
#include <vector>
using namespace std;

int N;
typedef struct{
	int m, d, s;
}ball;
vector<ball> fire_map[50][50];
vector<ball> tmp_map[50][50];
int dx[8] = { -1,-1,0,1,1,1,0,-1 };
int dy[8] = { 0,1,1,1,0,-1,-1,-1 };


int what_dir(int cur_, int new_) {
	if (cur_ == 0)
	{
		if (new_ % 2 == 1) {
			return 1;
		}
		else {
			return 2;
		}
	}
	else if (cur_ == 1) {
		if (new_ % 2 == 1) {
			return 1;
		}
		else {
			return 3;
		}
	}
	else if (cur_ == 2) {
		if (new_ % 2 == 1) {
			return 3;
		}
		else {
			return 2;
		}
	}
	else {
		return 3;
	}
}

void moving() {
	int mx, my;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < fire_map[i][j].size(); ++k) {
				mx = i + dx[fire_map[i][j][k].d] * (fire_map[i][j][k].s%N);
				my = j + dy[fire_map[i][j][k].d] * (fire_map[i][j][k].s%N);

				if (mx < 0) {
					mx = N - (abs(mx) % N);
				}
				else if (mx > (N - 1)) {
					mx = mx % N;
				}
				if (my < 0) {
					my = N - (abs(my) % N);
				}
				else if (my > (N - 1)) {
					my = my % N;
				}

				tmp_map[mx][my].push_back({ fire_map[i][j][k] });
			}
			fire_map[i][j].clear();
		}
	}
}

void spread() {
	int m, s, d;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (tmp_map[i][j].size() > 1) {
				m = 0, s = 0, d = 0;
				for (int k = 0; k < tmp_map[i][j].size(); ++k) {
					m += tmp_map[i][j][k].m;
					s += tmp_map[i][j][k].s;
					d = what_dir(d, tmp_map[i][j][k].d);
				}
				if (m / 5 >= 1) {
					if (d == 3) {
						for (int k = 1; k < 8; k += 2)
							fire_map[i][j].push_back({ m / 5, k, s / int(tmp_map[i][j].size()) });
					}
					else {
						for (int k = 0; k < 8; k += 2)
							fire_map[i][j].push_back({ m / 5, k, s / int(tmp_map[i][j].size()) });
					}
				}
				tmp_map[i][j].clear();
			}
			else if (tmp_map[i][j].size() == 1) {
				fire_map[i][j].push_back({ tmp_map[i][j][0] });
				tmp_map[i][j].clear();
			}
		}
	}
}


int main() {
	int  M, K;
	cin >> N >> M >> K;

	int tmpr, tmpc, tmpm, tmps, tmpd;
	for (int i = 0; i < M; ++i) {
		cin >> tmpr >> tmpc >> tmpm >> tmps >> tmpd;
		fire_map[tmpr-1][tmpc-1].push_back({ tmpm, tmpd ,tmps});
	}

	for (int c = 0; c < K; ++c) {
		moving();
		spread();
	}

	int sum_m = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < fire_map[i][j].size(); ++k) {
				sum_m += fire_map[i][j][k].m;
			}
		}
	}
	cout << sum_m;
}