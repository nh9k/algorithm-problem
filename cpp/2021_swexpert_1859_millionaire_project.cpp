#include<iostream>
using namespace std;
int selling_price[1000000];


int main(int argc, char** argv)
{
	int test_case;
	int T;
	cin >> T;
	
	int N;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		cin >> N;
		for (int i = 0; i < N; ++i) {
			cin >> selling_price[i];
		}

		long long maximum = 0;
		int budget = selling_price[N - 1];

		for (int i = N - 2; i >= 0; --i) {
			if (budget >= selling_price[i])
			{
				maximum += (budget - selling_price[i]);
			}
			else 
			{
				budget = selling_price[i];
			}
		}

		cout << "#" << test_case << " " << maximum << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}