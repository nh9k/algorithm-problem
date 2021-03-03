//제출 번호	아이디	문제	결과	메모리	시간	언어	코드 길이	제출한 시간
//26855047	nh9k	14890	맞았습니다!!2056	0	C++17 / 수정	1528
//경사로
//풀이 시간 측정안함
//문제를 풀기전 알고리즘 제대로 세우고 풀기
//가로 방향, 세로 방향 알고리즘 동일하니 실수 말기
//마지막에 내려가는 경우일경우, 사다리를 놓았는데 부족한 경우도 있으므로 체크하는 부분 조심!

#include <iostream>
using namespace std;

int map[101][101];
int L, N, cnt;
//int mem;
//
//void memfunc(int pass)
//{
//	if (mem != pass)
//	{
//		cout << 0;
//	}
//	else
//		cout << 1;
//	mem = pass;
//}

int main() {
	cin >> N >> L;
	for (int ni = 0; ni < N; ++ni) {
		for (int nj = 0; nj < N; ++nj) {
			cin >> map[ni][nj];
		}
	}

	int pass = 2*N;
	//mem = 2 * N;

	for (int ni = 0; ni < N; ++ni) {
		cnt = 1;
		for (int nj = 1; nj < N; ++nj) {
			cnt++;

			if ((map[ni][nj - 1] + 1) == map[ni][nj]) //up
			{
				cnt -= L;
				if (cnt <= 0) {
					pass -= 1;
					cnt = 1;
					break;
				}
			}
			else if ((map[ni][nj - 1] - 1) == map[ni][nj]) //down
			{
				if (cnt <= 0) {
					pass -= 1;
					cnt = 1;
					break;
				}
				cnt = 0;
				cnt -= (L - 1);
			}
			else if (map[ni][nj - 1] != map[ni][nj])
			{
				pass -= 1;
				cnt = 1;
				break;
			}

		}
		if (cnt < 0) {
			pass -= 1;
		}
		//memfunc(pass);
	}

	//cout << endl;
	for (int nj = 0; nj < N; ++nj) {
		cnt = 1;
		for (int ni = 1; ni < N; ++ni) {
			cnt++;

			if ((map[ni - 1][nj] + 1) == map[ni][nj]) //up
			{
				cnt -= L;
				if (cnt <= 0) {
					pass -= 1;
					cnt = 1;
					break;
				}
			}
			else if ((map[ni - 1][nj] - 1) == map[ni][nj]) //down
			{
				if (cnt <= 0) {
					pass -= 1;
					cnt = 1;
					break;
				}
				cnt = 0;
				cnt -= (L - 1);
			}
			else if (map[ni - 1][nj] != map[ni][nj])
			{
				pass -= 1;
				cnt = 1;
				break;
			}
		}
		if (cnt < 0) {
			pass -= 1;
		}

		//memfunc(pass);
	}

	cout << pass << endl;
	return 0;
}
