#include<iostream>
#include <string>
#include <algorithm>

using namespace std;
int max_money;
string cur_money;

void recur(int stidx, int cnt) {
	if (cnt == 0) {
		if (stoi(cur_money) > max_money) {
			max_money = stoi(cur_money);
		}
		return;
	}

	for (int i = stidx; i < cur_money.size(); ++i) {
		for (int j = i + 1; j < cur_money.size(); ++j) {

			swap(cur_money[i], cur_money[j]);
			recur(i, cnt - 1);
			swap(cur_money[i], cur_money[j]);
		}
	}
}


int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin >> T;

	int exchange;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> cur_money >> exchange;

		max_money = 0;
		recur(0, exchange);

		cout << "#" << test_case << " " << max_money << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}