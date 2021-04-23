//5648. [모의 SW 역량테스트] 원자 소멸 시뮬레이션
//1시간 15분 풀이
#include <iostream>
#include <vector>
using namespace std;

int map[4001][4001];
int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };
int N;
typedef struct {
	int x, y, dir, k;
}atom;
vector <atom> a;

int main() {
	int test_case = 0;
	cin >> test_case;

	for (int t = 0; t < test_case; ++t) {
		cin >> N;
		int tmpx, tmpy, tmpd, tmpk;
		for (int i = 0; i < N; ++i) {
			cin >> tmpx >> tmpy >> tmpd >> tmpk;
			a.push_back({ tmpy * (-2) + 2000, tmpx * 2 + 2000, tmpd, tmpk });
			//map[a[i].x][a[i].y] += a[i].k;
		}

		int answer = 0;
		while (!a.empty()) {
			for (int i = 0; i < a.size(); ++i) {
				map[a[i].x][a[i].y] = 0;
				int mx = a[i].x + dx[a[i].dir];
				int my = a[i].y + dy[a[i].dir];

				if (mx < 0 || my < 0 || mx > 4000 || my > 4000) {
					a[i].k = 0;
					continue;
				}

				a[i].x = mx;
				a[i].y = my;
				map[mx][my] += a[i].k;
 			}

			int vsz = a.size();
			for (int i = vsz -1; i >= 0; --i) {
				if (a[i].k == 0) {
					a.erase(a.begin() + i);
				}
				else if (map[a[i].x][a[i].y] != a[i].k) {
					answer += map[a[i].x][a[i].y];
					map[a[i].x][a[i].y] = 0;
					a.erase(a.begin() + i);
				}
			}
		}
		cout << "#" << t + 1 << " " << answer << endl;
	}
}