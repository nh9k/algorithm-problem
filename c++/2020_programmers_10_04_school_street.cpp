#include <string>
#include <vector>

using namespace std;
int map[101][101];

int solution(int m, int n, vector<vector<int>> puddles) {
	//m==x==[][x]
	for (int sz = 0; sz < puddles.size(); ++sz)
		map[puddles[sz][1] - 1][puddles[sz][0] - 1] = -1;
	for (int x = 0; x < m; ++x) {
		if (map[0][x] == -1) {
			for (int x1 = x; x1 < m; ++x1)
				map[0][x1] = 0;
			break;
		}
		map[0][x] = 1;
	}
	for (int y = 0; y < n; ++y) {
		if (map[y][0] == -1) {
			for (int y1 = y; y1 < n; ++y1)
				map[y1][0] = 0;
			break;
		}
		map[y][0] = 1;
	}


	for (int y = 1; y < n; ++y) {
		for (int x = 1; x < m; ++x) {
			if (map[y][x] == -1) map[y][x] = 0;
			else map[y][x] = (map[y - 1][x] + map[y][x - 1]) % 1000000007;
		}
	}

	return map[n - 1][m - 1];
}