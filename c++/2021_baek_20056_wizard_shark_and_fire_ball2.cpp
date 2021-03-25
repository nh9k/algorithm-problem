//제출 번호	아이디	문제	결과	메모리	시간	언어	코드 길이	제출한 시간
//27520211	nh9k	20056	맞았습니다!!2668	24	C++17 / 수정	3169	23초 전
//
//깔끔하게 풀 수 있는 문제였음에도 불구하고 며칠간 생각하며 풀었던 문제.
//문제 풀이
//- map에 파이어볼 정보를 push한다는 아이디어만 있다면 쉽게 작성가능(시간초과 해결)
//- 마지막 예제 문제가 틀렸을 때: new_ball 함수에서 파이어볼이 1개일때도 다시 map에 넣어주는 것을 잊지말기
//- 완벽하게 작성했다고 생각했는데 제출 후 바로 틀렸을 때: 질량이 0일 경우 처리해주기(new_ball함수에서(summ / 5) >= 1) 부분)


#include <iostream>
#include <vector>
using namespace std;

int dr[8] = { -1,-1,0,1,1,1,0,-1 };
int dc[8] = { 0,1,1,1,0,-1,-1,-1 };
int N, K;
typedef struct {
	int m, s, d;
}fireball;

vector <fireball> map[50][50];
vector <fireball> newmap[50][50];


bool is_odd(int number) {
	if (number % 2 == 0)
		return false;
	else
		return true;
}

int what_dir(int dir1, int dir2) //없음0, 홀1, 짝2, 혼합3
{
	if (dir1 == 0) {
		if (is_odd(dir2))
			return 1;
		else
			return 2;
	}
	else if (dir1 == 3)
		return 3;
	else if (dir1 == 1)
	{
		if (is_odd(dir2))
			return 1;
		else
			return 3;
	}
	else if (dir1 == 2)
	{
		if (is_odd(dir2))
			return 3;
		else
			return 2;
	}
}

void moving() {
	int r, c;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < map[i][j].size(); ++k) {
				r = (i + (dr[map[i][j][k].d] * (map[i][j][k].s % N)));
				c = (j + (dc[map[i][j][k].d] * (map[i][j][k].s % N)));

				if (r > (N - 1)) r -= N;
				if (c > (N - 1)) c -= N;
				if (r < 0) r += N;
				if (c < 0) c += N;

				newmap[r][c].push_back(map[i][j][k]);
			}
		}
	}
}

void new_ball() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			map[i][j].clear();
			int summ = 0, sums = 0, sumd = 0;
			for (int k = 0; k < newmap[i][j].size(); ++k) {
				summ += newmap[i][j][k].m;
				sums += newmap[i][j][k].s;
				sumd = what_dir(sumd, newmap[i][j][k].d);
			}

			if ((sumd == 3) && ((summ/5)>=1)) {
				map[i][j].push_back({ summ / 5, sums / int(newmap[i][j].size()), 1});
				map[i][j].push_back({ summ / 5, sums / int(newmap[i][j].size()), 3});
				map[i][j].push_back({ summ / 5, sums / int(newmap[i][j].size()), 5});
				map[i][j].push_back({ summ / 5, sums / int(newmap[i][j].size()), 7});
			}
			else if((sumd!=0) && (newmap[i][j].size()!=1) && ((summ / 5) >= 1)) {
				map[i][j].push_back({ summ / 5, sums / int(newmap[i][j].size()), 0 });
				map[i][j].push_back({ summ / 5, sums / int(newmap[i][j].size()), 2 });
				map[i][j].push_back({ summ / 5, sums / int(newmap[i][j].size()), 4 });
				map[i][j].push_back({ summ / 5, sums / int(newmap[i][j].size()), 6 });
			}
			else if(newmap[i][j].size()==1)
				map[i][j].push_back(newmap[i][j][0]);

			newmap[i][j].clear();
		}
	}
}

int main() {
	int tmpr, tmpc, tmpm, tmps, tmpd, M;
	cin >> N >> M >> K;
	for (int i = 0; i < M; ++i) {
		cin >> tmpr >> tmpc >> tmpm >> tmps >> tmpd;
		map[tmpr - 1][tmpc - 1].push_back({ tmpm, tmps, tmpd });
	}


	for (int ki = 0; ki < K; ++ki)
	{
		moving();
		new_ball();
	}

	int sum_m = 0;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			for (int k = 0; k < map[i][j].size(); ++k) {
				sum_m += map[i][j][k].m;
			}
		}
	}
	cout << sum_m;
}
