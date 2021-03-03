//���� ��ȣ	���̵�	����	���	�޸�	�ð�	���	�ڵ� ����	������ �ð�
//26644574	nh9k	14891	�¾ҽ��ϴ�!!2024	0	C++17 / ����	1798
//1�ð� 26�� Ǯ�� =>> 
//(1) input string���� �ޱ�, input���� -48�ؾ� 0�Ǵ� 1�� ��
//(2) queue�� front�� pop �κ�
//(3) rotate�� rbegin�� ���������� ȸ��
//(4) is_rotate �Լ����� +1, -1 �Ǽ�

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