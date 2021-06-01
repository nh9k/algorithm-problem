//2020 KAKAO BLIND RECRUITMENT 기둥과 보 설치
//기둥은 보의 한쪽 끝 부분에 있거나 -> 양쪽 끝부분에 있어도 되는 데 착각함


#include <string>
#include <vector>
#include <iostream>
using namespace std;
bool col_map[101][101], row_map[101][101];


bool can_col(int x, int y) {
	if (y == 0)
		return true;
	else if (row_map[y][x - 1] || row_map[y][x])
		return true;
	else if (col_map[y - 1][x])
		return true;
	return false;
}

bool can_row(int x, int y) {
	if (col_map[y-1][x] || col_map[y-1][x + 1])
		return true;
	else if (row_map[y][x - 1] && row_map[y][x + 1])
		return true;
	return false;
}

void building(int x, int y, int a) {
	if (a == 0) //col
	{
		if (can_col(x, y))
			col_map[y][x] = true;
	}
	else //row
	{
		if (can_row(x, y))
			row_map[y][x] = true;
	}
}

void pull_down(int x, int y, int a)
{
	if (a == 0)
	{
		col_map[y][x] = false;
		if (col_map[y + 1][x] && (!can_col(x, y + 1)))
			col_map[y][x] = true;
		else if (row_map[y + 1][x] && (!can_row(x, y + 1)))
			col_map[y][x] = true;
		else if (row_map[y + 1][x - 1] && (!can_row(x - 1, y + 1)))
			col_map[y][x] = true;
	}
	else
	{
		row_map[y][x] = false;
		if (row_map[y][x - 1] && (!can_row(x - 1, y)))
			row_map[y][x] = true;
		else if (row_map[y][x + 1] && (!can_row(x + 1, y)))
			row_map[y][x] = true;
		else if (col_map[y][x] && (!can_col(x, y)))
			row_map[y][x] = true;
		else if (col_map[y][x + 1] && (!can_col(x + 1, y)))
			row_map[y][x] = true;
	}
}



void cout_map()
{
	cout << "col" << endl;
	for (int i = 0; i <= 5; ++i) {
		for (int j = 0; j <= 5; ++j) {
			cout << col_map[i][j];
		}
		cout << endl;
	}

	cout << "row" << endl;
	for (int i = 0; i <= 5; ++i) {
		for (int j = 0; j <= 5; ++j) {
			cout << row_map[i][j];
		}
		cout << endl;
	}


}



vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
	for (int i = 0; i < build_frame.size(); ++i) {
		if (build_frame[i][3])
		{
			building(build_frame[i][0], build_frame[i][1], build_frame[i][2]);
		}
		else
		{
			pull_down(build_frame[i][0], build_frame[i][1], build_frame[i][2]);
		}
		cout_map();
	}

	vector<vector<int>> answer;
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= n; ++j) {
			if (col_map[j][i])
				answer.push_back({ i,j,0 });
			if (row_map[j][i])
				answer.push_back({ i,j,1 });
		}
	}

	for (int i = 0; i < answer.size(); ++i)
		cout << answer[i][0] << answer[i][1] << answer[i][2] << endl;

	return answer;
}


int main() {
	//solution(5, { {1, 0, 0, 1},{1, 1, 1, 1},{2, 1, 0, 1},{2, 2, 1, 1},{5, 0, 0, 1},{5, 1, 0, 1},{4, 2, 1, 1},{3, 2, 1, 1} });
	solution(5, { {0, 0, 0, 1},{2, 0, 0, 1},{4, 0, 0, 1},{0, 1, 1, 1},{1, 1, 1, 1},{2, 1, 1, 1},{3, 1, 1, 1},{2, 0, 0, 0},{1,1,1,0 },{2,2,0,1} });


	return 0;
}