//���� ��ȣ	���̵�	����	���	�޸�	�ð�	���	�ڵ� ����	������ �ð�
//27533754	nh9k	20057	�¾ҽ��ϴ�!!2988	100	C++17 / ����	1837	25�� ��
//Ǯ�̽ð�: 1�ð� 32��
//����1: �ѹ��� ����ĭ �̵��ϴ� ���� �ƴ϶�, �ѹ��� ��ĭ�� �̵��ϴ� ��!
//����2: �𷡰� ���� ������ ���� �� �ִ� == ���� �𷡴� ���Ŀ� ���� �𷡸� ���� �� ���� �־�� �Ѵ�!

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