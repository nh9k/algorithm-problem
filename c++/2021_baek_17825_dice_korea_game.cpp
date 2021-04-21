//1시간 32분 풀이
//말이 겹치는지 확인할 때 40 지점 검사 해주는 것 때문에 시간 더 할애.

#include <iostream>
#include <vector>
using namespace std;

int max_point;
int dice[10];
vector <int> map[4];
typedef struct {
	int f, s;
}horse;
horse h[4];

bool is_exist(int idx) {
	for (int i = 0; i < 4; ++i) {
		if (idx == i) continue;
		if (h[i].s == -1) continue;

		if (h[i].f == h[idx].f && h[i].s == h[idx].s) {
			return true;
		}

		if ((h[idx].f == 1 || h[idx].f == 3) && h[idx].s >= 4) {
			if (h[i].f == 2) {
				if ((h[idx].s - 1) == h[i].s) return true;
			}
			else if (h[i].f == 1 || h[i].f == 3) {
				if (h[idx].s == h[i].s) return true;
			}
		}
		else if (h[idx].f == 2 && h[idx].s >= 3 ) {
			if (((h[idx].s + 1) == h[i].s) && (h[i].f == 1 || h[i].f == 3)) return true;
		}
		
		if ((h[idx].f == 1 || h[idx].f == 3) && h[i].f == 0) {
			if (h[idx].s == 7 && h[i].s == 20) return true;
		}
		else if (h[idx].f == 2 && h[i].f == 0) {
			if (h[idx].s == 6 && h[i].s == 20) return true;
		}
		else if (h[idx].f == 0 && (h[i].f == 1 || h[i].f == 3)) {
			if (h[idx].s == 20 && h[i].s == 7) return true;
		}
		else if (h[idx].f == 0 && h[i].f == 2) {
			if (h[idx].s == 20 && h[i].s == 6) return true;
		}

	}
	return false;
}

void dfs(int idx, int point) {
	if (idx >= 10) {
		if (max_point <= point) {
			max_point = point;
		}
		return;
	}
	int memf, mems;
	for (int i = 0; i < 4; ++i) {
		if (h[i].s == -1) continue;
		memf = h[i].f;
		mems = h[i].s;
		int move = h[i].s + dice[idx];

		if (map[h[i].f].size() <= move) { //도착
				h[i].s = -1;
		}
		else {
			//이동
			if (h[i].f == 0 && move == 5) {
				h[i].f = 1;
				h[i].s = 0;
			}
			else if (h[i].f == 0 && move == 10) {
				h[i].f = 2;
				h[i].s = 0;
			}
			else if (h[i].f == 0 && move == 15) {
				h[i].f = 3;
				h[i].s = 0;
			}
			else {
				h[i].s = move;
			}
		}
		if ( h[i].s != -1 && is_exist(i) == 0 ) {
			dfs(idx + 1, point + map[h[i].f][h[i].s]);

		}
		else if (h[i].s == -1) {
			dfs(idx + 1, point);
		}
		h[i].f = memf;
		h[i].s = mems;
	}
}


int main() {
	for (int i = 0; i < 10; ++i)
		cin >> dice[i];

	for (int i = 0; i <= 40; i += 2) {
		map[0].push_back(i);
	}
	for (int i = 10; i <= 19; i += 3) {
		map[1].push_back(i);
	}
	for (int i = 20; i <= 24; i += 2) {
		map[2].push_back(i);
	}
	map[3].push_back(30);
	for (int i = 28; i >= 26; i -= 1) {
		map[3].push_back(i);
	}
	for (int i = 25; i <= 40; i += 5) {
		map[1].push_back(i);
		map[2].push_back(i);
		map[3].push_back(i);
	}
	
	dfs(0, 0);

	cout << max_point << endl;
}
