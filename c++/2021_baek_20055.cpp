//제출 번호	아이디	문제	결과	메모리	시간	언어	코드 길이	제출한 시간
//26969914	nh9k	20055	맞았습니다!!2016	56	C++17 / 수정	1051
//풀이 시간: 44분
//실제 시험때는 20분만에 풀었던 문제이나, 더 늦게 풀게된 이유는,
//1. 컨베이어 벨트가 이동할 때, 로봇이 함께 이동하는 것을 확인해주지 않아서
//2. 컨베이어 벨트가  이동할 때, 로봇을 함께 이동시키고 첫번째 자리의 로봇은 false로 넣어주는 것


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector <int> belt;
int N, K;
bool robot[101];

int detectK() {
	int cnt = 0;
	for (int i = 0; i < belt.size(); ++i) {
		if (belt[i] == 0)
		{
			cnt++;
		}
	}
	if (cnt >= K)
		return true;
	return false;
}

int main()
{
	cin >> N >> K;
	int tmp;
	for (int i = 0; i < (N * 2); ++i) {
		cin >> tmp;
		belt.push_back(tmp);
	}

	int step = 0;
	while (!detectK())
	{

		rotate(belt.rbegin(), belt.rbegin() + 1, belt.rend());
		for (int i = N - 1; i > 0; --i) {
			robot[i] = robot[i - 1];
		}
		robot[0] = false;

		for (int i = N - 1; i >= 0; --i) {
			if (robot[i] && (i == N - 1)) {
				robot[i] = false;
				continue;
			}
			if ((robot[i + 1] == false) && (robot[i]) && (belt[i+1] > 0))
			{
				robot[i + 1] = true;
				belt[i + 1] -= 1;
				robot[i] = false;

				if ((i + 1) == (N - 1))
				{
					robot[i + 1] = false;
				}
			}
		}

		if ((robot[0] == false) && (belt[0] > 0))
		{
			robot[0] = true;
			belt[0] -= 1;
		}

		step++;
	}

	cout << step;
	return 0;
}