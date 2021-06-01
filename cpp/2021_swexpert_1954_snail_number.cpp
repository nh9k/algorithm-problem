//1954. 달팽이 숫자
#include<iostream>

using namespace std;

int snail[10][10];
int dx[] = { 0,1,0,-1 };
int dy[] = { 1,0,-1,0 };

bool is_end(int x, int y) {
	for (int i = 0; i < 4; i++)
		if (snail[x + dx[i]][y + dy[i]] == 0)
			return false;
	return true;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		int n;
		cin >> n;

		if (n == 1)
		{
			cout << "#" << test_case << endl;
			cout << "1" << endl;
			continue;
		}
		else if (n == 2) {
			cout << "#" << test_case << endl;
			cout << "1 2" << endl;
			cout << "4 3" << endl;
			continue;
		}

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				snail[i][j] = 0;
			}
		}

		int x = 0, y = 0, num = 1, dir = 0;
		int mx, my;
		while (1) {
			snail[x][y] = num;
			mx = x + dx[dir];
			my = y + dy[dir];
			if (mx < 0 || my < 0 || mx >= n || my >= n || snail[mx][my] != 0) {
				dir++;
				if (dir > 3) dir = 0;
				mx = x + dx[dir];
				my = y + dy[dir];
				if (is_end(x, y)) break;
			}
			x = mx;
			y = my;
			num++;
		}

		cout << "#" << test_case << endl;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				cout << snail[i][j] << " ";
			}cout << endl;
		}
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}