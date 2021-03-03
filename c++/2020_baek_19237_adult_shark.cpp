//백준 19237번 어른 상어
//시뮬레이션 문제
//문제 풀이 시간 약 2시간
//채점 번호	아이디	문제 번호	결과	메모리	시간	언어	코드 길이	제출한 시간
//23299093	nh9k	19237	맞았습니다!!2032	16	C++14 / 수정	3293
//
//주의
//if ((s[mi].x == s[mj].x) && (s[mi].y == s[mj].y) && (s[mj].live == true)) { //살아있는 상어랑 검사해야함


#include <iostream>
using namespace std;

struct Priority {
	int dir[5][5];
}p[401];
struct Shark {
	int x, y;
	int dir;
	bool live;
}s[401];
struct Map {
	int s_num;
	int s_k;
}m[20][20];
int N, M, K;
int dx[] = { 0, -1, 1, 0, 0 };
int dy[] = { 0, 0, 0, -1, 1 };


bool shark_1_only() {
	for (int mi = 2; mi <= M; ++mi) {
		if (s[mi].live == true) {
			return false;
		}
	}
	return true;
}

void erase_smell() {
	for (int xi = 0; xi < N; ++xi) {
		for (int yi = 0; yi < N; ++yi) {
			if (m[xi][yi].s_num != 0) {
				m[xi][yi].s_k -= 1;
				if (m[xi][yi].s_k <= 0) {
					m[xi][yi].s_num = 0;
				}
			}
		}
	}
}

void make_smell() {
	for (int mi = 1; mi <= M; ++mi) {
		if (s[mi].live == true) {
			m[s[mi].x][s[mi].y].s_num = mi;
			m[s[mi].x][s[mi].y].s_k = K;
		}
	}
}

bool out_range(int x, int y) {
	if ((x < 0) || (x >= N) || (y < 0) || (y >= N)) {
		return true;
	}
	return false;
}

void shark_move() {
	for (int mi = 1; mi <= M; ++mi) {
		for (int i = 0; i < 8; ++i) {
			if (i < 4) { //아무냄새x칸
				int whichdir = i + 1;
				int mx = s[mi].x + dx[p[mi].dir[s[mi].dir][whichdir]];
				int my = s[mi].y + dy[p[mi].dir[s[mi].dir][whichdir]];

				if (out_range(mx, my)) continue;
				if (m[mx][my].s_num == 0) {
					s[mi].x = mx;
					s[mi].y = my;
					s[mi].dir = p[mi].dir[s[mi].dir][whichdir];
					break;
				}
			}
			else { //자신의 냄새칸
				int whichdir = i - 3;
				int mx = s[mi].x + dx[p[mi].dir[s[mi].dir][whichdir]];
				int my = s[mi].y + dy[p[mi].dir[s[mi].dir][whichdir]];

				if (out_range(mx, my)) continue;
				if (m[mx][my].s_num == mi) {
					s[mi].x = mx;
					s[mi].y = my;
					s[mi].dir = p[mi].dir[s[mi].dir][whichdir];
					break;
				}
			}
		}
		for (int mj = 1; mj < mi; ++mj) {
			if ((s[mi].x == s[mj].x) && (s[mi].y == s[mj].y) && (s[mj].live == true)) { //살아있는 상어랑 검사해야함
				s[mi].live = false; //쫓겨남
			}
		}
	}
}

void print_map() {
	for (int xi = 0; xi < N; ++xi) {
		for (int yi = 0; yi < N; ++yi) {
			cout << m[xi][yi].s_num << " " << m[xi][yi].s_k << "  ";
		}cout << endl;
	}cout << endl; cout << endl;

	for (int mi = 1; mi <= M; ++mi) {
			cout << mi << endl;
			cout << s[mi].live << endl;
			cout << s[mi].x << " " << s[mi].y << " " << s[mi].dir << endl;
	}cout << endl;
}


int main() {
	//***********************************input**************************************//
	cin >> N >> M >> K;

	int temp;
	for (int xi = 0; xi < N; ++xi) {
		for (int yi = 0; yi < N; ++yi) {
			cin >> temp;
			if (temp != 0) {
				s[temp].x = xi;
				s[temp].y = yi;
				s[temp].live = true;
			}		
		}
	}

	for (int mi = 1; mi <= M; ++mi) {
		cin >> s[mi].dir;
	}

	for (int mi = 1; mi <= M; ++mi) {
		cin >> p[mi].dir[1][1] >> p[mi].dir[1][2] >> p[mi].dir[1][3] >> p[mi].dir[1][4];
		cin >> p[mi].dir[2][1] >> p[mi].dir[2][2] >> p[mi].dir[2][3] >> p[mi].dir[2][4];
		cin >> p[mi].dir[3][1] >> p[mi].dir[3][2] >> p[mi].dir[3][3] >> p[mi].dir[3][4];
		cin >> p[mi].dir[4][1] >> p[mi].dir[4][2] >> p[mi].dir[4][3] >> p[mi].dir[4][4];		
	}

	//***********************************logic**************************************//
	for (int time = 1; time <= 1000; ++time) {
		make_smell();
		shark_move();
		erase_smell();
		//cout << time - 1 << endl;
		//print_map();
		if (shark_1_only()) {
			cout << time;
			return 0;
		}
	}
	cout << -1;
	return 0;
}