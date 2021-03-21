//제출 번호	아이디	문제	결과	메모리	시간	언어	코드 길이	제출한 시간
//27533754	nh9k	20057	맞았습니다!!2988	100	C++17 / 수정	1837	25초 전
//풀이시간: 1시간 32분
//주의1: 한번에 여러칸 이동하는 것이 아니라, 한번에 한칸씩 이동하는 점!
//주의2: 모래가 격자 밖으로 나갈 수 있다 == 나간 모래는 알파에 남은 모래를 넣을 때 빼고 넣어야 한다!

#include <iostream>
using namespace std;
int map[499][499];
int N;
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };
struct tornado {
	int x, y;
}t;
int percent[10] = { 1,1,7,7,10,10,2,2,5,0 };
int chx[4][10] = { {-1,1,-1,1,-1,1,-2,2,0,0},{-1,-1,0,0,1,1,0,0,2,1},{-1,1,-1,1,-1,1,-2,2,0,0},{1,1,0,0,-1,-1,0,0,-2,-1} };
int chy[4][10] = { {1,1,0,0,-1,-1,0,0,-2,-1},{-1,1,-1,1,-1,1,-2,2,0,0},{-1,-1,0,0,1,1,0,0,2,1},{-1,1,-1,1,-1,1,-2,2,0,0} };

void moving(int dir)
{
	int curx, cury;
	int curs = map[t.x][t.y];

	for (int i = 0; i < 10; ++i) {
		curx = t.x + chx[dir][i];
		cury = t.y + chy[dir][i];

		if (curx < 0 || curx > N - 1 || cury < 0 || cury > N - 1) {
			curs -= (map[t.x][t.y] * percent[i]) / 100;
		}
		else if (i == 9) {
			map[curx][cury] += curs;
			map[t.x][t.y] = 0;
		}
		else
		{
			map[curx][cury] += (map[t.x][t.y] * percent[i]) / 100;
			curs -= (map[t.x][t.y] * percent[i]) / 100;
		}
	}
	if (t.x >= 0 && t.x <= N - 1 || t.y >= 0 || t.y <= N - 1)
		map[t.x][t.y] = 0;
}

void printing() {
	cout << t.x << " " << t.y << endl;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cout << map[i][j];
		}cout << endl;
	}cout << endl;
}

int main()
{
	int ans = 0;
	cin >> N;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> map[i][j];
			ans += map[i][j];
		}
	}

	int dir = 0;
	t.x = N/2, t.y = N/2;
	for (int i = 1; i <= N; ++i) {
		for (int j = 0; j < i; ++j) {
			t.x += dx[dir];
			t.y += dy[dir];
			moving(dir);
		}

		//printing();
		if (t.x == 0 && t.y == -1) break;
		dir++;

		for (int j = 0; j < i; ++j) {
			t.x += dx[dir];
			t.y += dy[dir];
			moving(dir);
		}
		//printing();
		dir++;
		if (dir > 3) dir = 0;
	}

	int ans_contain = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			ans_contain += map[i][j];
		}
	}
	cout << ans - ans_contain;
}