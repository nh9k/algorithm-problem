//제출 번호	아이디	문제	결과	메모리	시간	언어	코드 길이	제출한 시간
//26644574	nh9k	14891	맞았습니다!!2024	0	C++17 / 수정	1798
//1시간 26분 풀이 =>> 
//(1) input string으로 받기, input에서 -48해야 0또는 1로 됨
//(2) queue는 front가 pop 부분
//(3) rotate는 rbegin이 오른쪽으로 회전
//(4) is_rotate 함수에서 +1, -1 실수

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

queue<pair<int, int>> demand;
vector<bool> tooth[4];
int do_rotate[4];
int seq[4][3] = { {1,2,3},{0,2,3},{1,3,0},{2,1,0} };

void sum_12()
{
	int sum_tooth = 0;

	if (tooth[0][0] != 0)
		sum_tooth += 1;
	if (tooth[1][0] != 0)
		sum_tooth += 2;
	if (tooth[2][0] != 0)
		sum_tooth += 4;
	if (tooth[3][0] != 0)
		sum_tooth += 8;

	cout << sum_tooth;
	return;
}

void is_rotate(int n, int dir)
{
	do_rotate[n] = dir;
	for (int i = 0; i < 3; ++i)
	{
		if (seq[n][i] < n)
		{
			if ((tooth[seq[n][i]][2] == tooth[seq[n][i] + 1][6]) ||
				(do_rotate[seq[n][i] + 1] == 0))
				do_rotate[seq[n][i]] = 0;
			else if (do_rotate[seq[n][i] + 1] == 1)
				do_rotate[seq[n][i]] = -1;
			else if (do_rotate[seq[n][i] + 1] == -1)
				do_rotate[seq[n][i]] = 1;
		}
		else
		{
			if ((tooth[seq[n][i]][6] == tooth[seq[n][i] - 1][2]) ||
				(do_rotate[seq[n][i] - 1] == 0))
				do_rotate[seq[n][i]] = 0;
			else if (do_rotate[seq[n][i] - 1] == 1)
				do_rotate[seq[n][i]] = -1;
			else if (do_rotate[seq[n][i] - 1] == -1)
				do_rotate[seq[n][i]] = 1;
		}
	}
}

int main() {

	string tmp;
	for (int i = 0; i < 4; ++i)
	{
		cin >> tmp;
		for (int j = 0; j < 8; ++j)
		{
			tooth[i].push_back(int(tmp[j]) - 48);
		}
	}

	int k, tmp1, tmp2;
	cin >> k;
	for (int i = 0; i < k; ++i)
	{
		cin >> tmp1 >> tmp2;
		demand.push({ tmp1 - 1, tmp2 });
	}

	for (int i = 0; i < k; ++i) {
		is_rotate(demand.front().first, demand.front().second);
		for (int j = 0; j < 4; ++j)
		{
			if (do_rotate[j] == 1)
				rotate(tooth[j].rbegin(), tooth[j].rbegin() + 1, tooth[j].rend());
			else if (do_rotate[j] == -1)
				rotate(tooth[j].begin(), tooth[j].begin() + 1, tooth[j].end());
		}
		demand.pop();
	}

	sum_12();
	return 0;
}