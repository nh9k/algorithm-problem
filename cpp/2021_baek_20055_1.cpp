//34∫– «Æ¿Ã
#include <iostream>
using namespace std;
int N, K;
#include <vector>
#include <algorithm>
vector <pair<int, bool>> belt;


int main() {
	cin >> N >> K;

	int tmp;
	for (int i = 0; i < 2 * N; ++i) {
		cin >> tmp;
		belt.push_back({ tmp, 0 });
	}

	for (int i = 1; ; ++i) {
		rotate(belt.begin(), belt.end() - 1, belt.end());
		//for (int j = 0; j < 2 * N; j++) {
		//	cout << belt[j].first;
		//}cout << endl;

		if (belt[N-1].second == 1) {
			belt[N-1].second = 0;
		}
		for (int j = N-2; j >= 0; --j) {
			if ((belt[j + 1].second == 0) && (belt[j+1].first >= 1) && (belt[j].second == 1)) {
				belt[j + 1].second = 1;
				belt[j + 1].first -= 1;
				belt[j].second = 0;
			}
		}
		if (belt[N - 1].second == 1) {
			belt[N - 1].second = 0;
		}

		if ((belt[0].second == 0) && (belt[0].first >= 1)) {
			belt[0].second = 1;
			belt[0].first -= 1;
		}

		int weight_zero = 0;
		for (int j = 0; j < 2*N; ++j) {
			if (belt[j].first == 0)
				weight_zero++;
		}
		if (weight_zero >= K) {
			cout << i;
			break;
		}

	}
}