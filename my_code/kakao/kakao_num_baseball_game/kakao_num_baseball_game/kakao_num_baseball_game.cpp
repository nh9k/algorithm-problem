#include <string>
#include <vector>
#include <iostream>
using namespace std;
typedef struct {
	int number[3], s, b;
}NUM;
NUM N[100];
int N_SIZE, temp[3], answer;
bool onoff[10];

void permu_(int cnt)//세 자리 순열을 만들기
{
	if (cnt >= 3) //스트라이크, 볼이 맞는지 확인하기
	{
		int tmp_s = 0, tmp_b = 0;
		//cout << temp[0] << temp[1] << temp[2] << endl;
		for (int nsz = 0; nsz < N_SIZE; ++nsz)
		{
			if (temp[0] == N[nsz].number[0])
				++tmp_s;
			else if (temp[0] == N[nsz].number[1] || temp[0] == N[nsz].number[2])
				++tmp_b;

			if (temp[1] == N[nsz].number[1])
				++tmp_s;
			else if (temp[1] == N[nsz].number[0] || temp[1] == N[nsz].number[2])
				++tmp_b;

			if (temp[2] == N[nsz].number[2])
				++tmp_s;
			else if (temp[2] == N[nsz].number[0] || temp[2] == N[nsz].number[1])
				++tmp_b;

			//cout << tmp_s << " " << tmp_b << endl;
			if (!(tmp_s == N[nsz].s && tmp_b == N[nsz].b))
			{
				return;
			}
			tmp_s = 0, tmp_b = 0;
		}
		answer++;
		return;
	}

	for (int i = 1; i < 10; ++i)
	{
		if (onoff[i]) continue;
		onoff[i] = true;
		if (cnt == 0) temp[0] = i;
		else if (cnt == 1) temp[1] = i;
		else temp[2] = i;
		permu_(cnt + 1);
		onoff[i] = false;
	}
	return;
}

int solution(vector<vector<int>> baseball) {
	N_SIZE = 0;
	for (int i = 0; i < baseball.size(); ++i)
	{
		for (int j = 0; j < baseball[i].size(); ++j)
		{
			if (j == 0)
			{
				N[N_SIZE].number[0] = (baseball[i][j] / 100);
				N[N_SIZE].number[1] = (baseball[i][j] / 10) - (N[N_SIZE].number[0] * 10);
				N[N_SIZE].number[2] = baseball[i][j] - (N[N_SIZE].number[0] * 100 + N[N_SIZE].number[1] * 10);
			}
			else if (j == 1)
				N[N_SIZE].s = baseball[i][j];
			else
			{
				N[N_SIZE].b = baseball[i][j];
				//cout << N[N_SIZE].number[0] << N[N_SIZE].number[1] << N[N_SIZE].number[2] << endl;
				++N_SIZE;
			}
		}
	}

	permu_(0);
	return answer;
}

void main()
{
	cout << solution({ {123, 1, 1},{356, 1, 0},{327, 2, 0},{489, 0, 1} });
	return;
}