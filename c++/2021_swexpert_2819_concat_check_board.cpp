//2819. 격자판의 숫자 이어 붙이기
#include<iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int checkboard[4][4];
int dx[] = { -1,0,1,0 };
int dy[] = { 0, 1,0,-1 };
vector <string> number_case;


void dfs(int x, int y, string temp_case) {
	if (temp_case.size() == 7) {
		number_case.push_back(temp_case);
		return;
	}

	for (int i = 0; i < 4; ++i) {
		int mx = x + dx[i];
		int my = y + dy[i];
		if (mx < 0 || my < 0 || mx > 3 || my > 3)
			continue;
		dfs(mx, my, temp_case + to_string(checkboard[mx][my]));
	}
}


int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				cin >> checkboard[i][j];
			}
		}

		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				dfs(i, j, to_string(checkboard[i][j]));
			}
		}

		sort(number_case.begin(), number_case.end());
		vector<string>::iterator end_iter = unique(number_case.begin(), number_case.end());

		cout << "#" << test_case << " " << end_iter -  number_case.begin() << endl;
		number_case.clear();
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}