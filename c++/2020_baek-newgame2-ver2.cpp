#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, K, realmap[12][12];
vector <int> checkmap[12][12];
typedef struct {
	int x, y, m;
}horse;
vector <horse> h;
int mx[5] = { 0,0,0,-1,1 }, my[5] = { 0,1,-1,0,0 }, reverse_[5] = { 0,2,1,4,3 };

bool OutRange(int x, int y) {
	if (x < 0 || y < 0 || x >= N || y >= N)
		return true;
	return false;
}

void simulation(int ki) {
	int movex = h[ki].x + mx[h[ki].m], movey = h[ki].y + my[h[ki].m];

	if (OutRange(movex, movey) || (realmap[movex][movey] == 2)) {
		h[ki].m = reverse_[h[ki].m];
		movex = h[ki].x + mx[h[ki].m], movey = h[ki].y + my[h[ki].m];

		if (OutRange(movex, movey) || (realmap[movex][movey] == 2)) {
			return;
		}
	}

	auto target = find(checkmap[h[ki].x][h[ki].y].begin(), checkmap[h[ki].x][h[ki].y].end(), ki);
	int beforex = h[ki].x, beforey = h[ki].y;

	if (realmap[movex][movey] == 1) //빨
		reverse(target, checkmap[h[ki].x][h[ki].y].end()); 

	for (auto i = target; i != checkmap[beforex][beforey].end(); i++)
	{
		checkmap[movex][movey].push_back(*i); //옮기고
		h[*i].x = movex, h[*i].y = movey; //갱신하고
		//i = checkmap[beforex][beforey].erase(i); //지우고
	}
	checkmap[beforex][beforey].erase(target, checkmap[beforex][beforey].end());
}

bool is4floor(int ki) {
	if (checkmap[h[ki].x][h[ki].y].size() >= 4)
		return true;
	return false;
}

int main()
{
	cin >> N >> K;

	//입력
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> realmap[i][j];
		}
	}

	int inputx, inputy, inputm;
	for (int ki = 0; ki < K; ++ki)
	{
		cin >> inputx >> inputy >> inputm;
		h.push_back({ inputx - 1, inputy - 1, inputm });
		checkmap[inputx - 1][inputy - 1].push_back(ki);
	}

	//1000번
	for (int turn = 1; turn <= 1000; ++turn)
	{
		for (int ki = 0; ki < K; ++ki) {

			simulation(ki);

			if (is4floor(ki)) {
				cout << turn;
				return 0;
			}
		}
	}
	cout << -1;
	return 0;
}