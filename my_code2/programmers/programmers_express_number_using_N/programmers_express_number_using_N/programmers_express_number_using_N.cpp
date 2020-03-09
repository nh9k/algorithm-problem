//#include <string>
//#include <vector>
#include <iostream> //cout
#include <algorithm> //min
#include <unordered_set> //unordered_set
using namespace std;
int cpy_N, cpy_number, answer;

void dfs(int cnt, int num)
{
	if (num == cpy_number)
	{
		answer = min(answer, cnt);
		return;
	}
	if (cnt >= 8) return;
	for (int i = 1; i <= 8-cnt; ++i)
	{
		int make_num = cpy_N;
		for(int j=2; j<=i; ++j)
			make_num = make_num * 10 + cpy_N;

		dfs(cnt + i, num + make_num);
		dfs(cnt + i, num - make_num);
		dfs(cnt + i, num * make_num);
		if(num!=0) dfs(cnt + i, num / make_num);
		dfs(cnt + 2, num + 1); // 1 = (cpy_N / cpy_N);
		dfs(cnt + 2, num - 1);
	}
}

int dp(int N, int number)
{//8�� ���� �� ��ǥ ���� set�ȿ� �ִ��� �˻� - ������ -1 ����
 //8�� ���� ���� set�ȿ� �ִٸ�, �� ���� Ƚ���� �����ϸ�, �װ��� �ּ� ���� Ƚ��

	unordered_set <int> num[11];
	int mul_num[9];

	mul_num[0] = 0;
	for (int i = 1; i <= 8; ++i)
	{
		mul_num[i] = mul_num[i - 1] * 10 + N; //N, NN, NNN, NNNN,...,NNNNNNNN ����
	}

	for (int i = 1; i <= 8; ++i)
	{
		num[i].insert(mul_num[i]);
		for (auto j = num[i].begin(); j != num[i].end(); ++j)
		{
			for (int k = 1; /*(k <= i) &&*/ (k <= 8-i); ++k)
			{
				num[i + k].insert((*j) + mul_num[k]);
				num[i + k].insert((*j) - mul_num[k]);
				num[i + k].insert((*j) * mul_num[k]);
				num[i + k].insert((*j) / mul_num[k]);
				num[i + 2].insert((*j) + 1); // 1 = (N / N); �̰� �� �������!
				num[i + 2].insert((*j) - 1);
			}
		}
		for (auto j = num[i].begin(); j != num[i].end(); ++j)
		{
			if ((*j) == number) return i;
		}
	}
	return -1;
}

int solution(int N, int number) {
	////way1. dfs
	//cpy_N = N, cpy_number = number, answer = 9;
	//dfs(0, 0);
	//if (answer == 9) return -1;
	//else return answer;

	////way2. dp
	return dp(N, number);	
}

void main()
{
	cout << solution(5, 12) << endl;
	cout << solution(2, 11) << endl;
}

