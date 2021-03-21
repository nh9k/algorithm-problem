//���� ��ȣ	���̵�	����	���	�޸�	�ð�	���	�ڵ� ����	������ �ð�
//27520211	nh9k	20056	�¾ҽ��ϴ�!!2668	24	C++17 / ����	3169	23�� ��
//
//����ϰ� Ǯ �� �ִ� ������������ �ұ��ϰ� ��ĥ�� �����ϸ� Ǯ���� ����.
//���� Ǯ��
//- map�� ���̾ ������ push�Ѵٴ� ���̵� �ִٸ� ���� �ۼ�����(�ð��ʰ� �ذ�)
//- ������ ���� ������ Ʋ���� ��: new_ball �Լ����� ���̾�� 1���϶��� �ٽ� map�� �־��ִ� ���� ��������
//- �Ϻ��ϰ� �ۼ��ߴٰ� �����ߴµ� ���� �� �ٷ� Ʋ���� ��: ������ 0�� ��� ó�����ֱ�(new_ball�Լ�����(summ / 5) >= 1) �κ�)


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

int what_dir(int dir1, int dir2) //����0, Ȧ1, ¦2, ȥ��3
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
