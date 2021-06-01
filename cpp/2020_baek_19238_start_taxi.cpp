//���� 19238�� ��ŸƮ�ý�
//���� Ǯ�� �ð� �� 6�ð�(���� �ð� ����)
//����:
//dfs�� �� Ǯ����.
//�ִ� ��θ� �������ν� bfs�� �������� ���ݰ� bfs�� �ٲ� Ǯ���Ͽ���.
//���� ��ġ�� ���ÿ� �ٸ� �°��� ��� ��ġ�� �� �� ������ �𸣰� map�� �� �°��� �����ϵ��� �Ͽ���.
//map�� vector�� �ٲ��ָ鼭, ��ü���� �Լ��� �ٽ� �����Ͽ���.
//
//ä�� ��ȣ	���̵�	���� ��ȣ	���	�޸�	�ð�	���	�ڵ� ����	������ �ð�
//23311051	nh9k	19238	�¾ҽ��ϴ�!!2000	4	C++14 / ����	4686	2�� ��

#include <iostream>
#include <queue>
#define MAX_PATH 401
using namespace std;

struct taxi {
	int x, y, fuel;
}t;
int p[401];
struct 
vector <int> map[21][21];
bool chkmap[21][21];
int N, M;
int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, 1, 0, -1 };


bool out_range(int x, int y) {
	if ((x < 0) || (x >= N) || (y < 0) || (y >= N))
		return true;
	return false;
}

void reset_chkmap() {
	for (int ni = 0; ni < N; ++ni) {
		for (int nj = 0; nj < N; ++nj) {
			chkmap[ni][nj] = 0;
		}
	}
}


int main() {
	//**************************************input**************************************//
	cin >> N >> M >> t.fuel;

	int temp;
	for (int ni = 0; ni < N; ++ni) {
		for (int nj = 0; nj < N; ++nj) {
			cin >> temp;
			if (temp == 0)
				map[ni][nj].push_back(0);
			else
				map[ni][nj].push_back(-1);
		}
	}

	cin >> t.x >> t.y;
	t.x -= 1;
	t.y -= 1;

	int temp1, temp2, temp3, temp4;
	for (int mi = 1; mi <= M; ++mi) {
		cin >> temp1 >> temp2 >> temp3 >> temp4;
		if (map[temp1 - 1][temp2 - 1].front() == 0) {
			map[temp1 - 1][temp2 - 1].pop_back();
			map[temp1 - 1][temp2 - 1].push_back( mi);
		}
		else if (map[temp1 - 1][temp2 - 1].front() != 0) {
			map[temp1 - 1][temp2 - 1].push_back(mi);
		}

		if (map[temp3 - 1][temp4 - 1].front() == 0) {
			map[temp3 - 1][temp4 - 1].pop_back(); 
			map[temp3 - 1][temp4 - 1].push_back(mi + 1000);
		}
		else if (map[temp3 - 1][temp4 - 1].front() != 0) {
			map[temp3 - 1][temp4 - 1].push_back( mi + 1000);
		}
	}	

	//**************************************logic**************************************//

	while (M) {
		int s_x = 21, s_y = 21, s_l = MAX_PATH, s_n = 0;
		//�°� �¿췯 ���� - �ִܰŸ�
		bool pass_on = false;
		if (map[t.x][t.y].front() != -1) {
			for (int k = 0; k < map[t.x][t.y].size(); ++k) {
				if ((map[t.x][t.y][k] != 0) && (map[t.x][t.y][k] < 1000))
				{
					s_x = t.x, s_y = t.y, s_l = 0, s_n = map[t.x][t.y][k];

					pass_on = true;
				}
			}
		}
		if (!pass_on) {
			queue <pair<int, int>> q;
			queue <int> q_sl;
			q.push({ t.x, t.y });
			q_sl.push({ 0 });
			while (q.size()) {
				if (s_l < q_sl.front() + 1) {
					q.pop();
					q_sl.pop();
				}
				else {
					for (int i = 0; i < 4; ++i) {
						int mx = q.front().first + dx[i];
						int my = q.front().second + dy[i];

						if (out_range(mx, my)) continue;
						if (chkmap[mx][my]) continue;
						if (map[mx][my].front() == -1) continue;
						if ((!((map[mx][my].front() == 0) && (map[mx][my].size() == 1))) && (s_l >= (q_sl.front() + 1))) {
							for (int k = 0; k < map[mx][my].size(); ++k) {
								if ((map[mx][my][k] < 1000) && (map[mx][my][k]!=0)) {
									if (s_x > mx) {
										s_x = mx;
										s_y = my;
										s_l = q_sl.front() + 1;
										s_n = map[mx][my][k];
									}
									else if (s_x == mx) {
										if (s_y >= my) {
											s_y = my;
											s_l = q_sl.front() + 1;
											s_n = map[mx][my][k];
										}
									}
								}
							}

						}
						chkmap[mx][my] = 1;
						q.push({ mx, my });
						q_sl.push(q_sl.front() + 1);
					}
					q.pop();
					q_sl.pop();
				}
			}
			reset_chkmap();
		}
		

		if (s_l == MAX_PATH) {
			cout << -1; 
			return 0;
		}

		//cout << s_l << endl;
		t.fuel -= s_l;
		t.x = s_x, t.y = s_y;
		for (int k = 0; k < map[s_x][s_y].size(); ++k) {
			if (map[s_x][s_y][k] == s_n)
				map[s_x][s_y][k] = 0;
		}
		if (t.fuel <= 0) {
			cout << -1;
			return 0;
		}//************************************** �°� �����ַ� ���� - �ִܰŸ�
		else {
			s_l = MAX_PATH;
			queue <pair<int, int>> q;
			queue <int> q_sl;
			q.push({ t.x, t.y });
			q_sl.push({ 0 });
			while (q.size()) {
				for (int i = 0; i < 4; ++i) {
					int mx = q.front().first + dx[i];
					int my = q.front().second + dy[i];

					if (out_range(mx, my)) continue;
					if (chkmap[mx][my]) continue;
					if (map[mx][my].front() == -1) continue;

					bool pass_on2 = false;
					if (!((map[mx][my].front() == 0) && (map[mx][my].size() == 1))) {
						for (int k = 0; k < map[mx][my].size(); ++k) {
							if (map[mx][my][k] == (s_n + 1000)) {
								s_x = mx, s_y = my, s_l = q_sl.front() + 1;
								s_n = map[mx][my][k];
								map[mx][my][k] = 0;
								pass_on2 = true;
							}
						}
					}
					if (!pass_on2){
						chkmap[mx][my] = 1;
						q.push({ mx, my });
						q_sl.push(q_sl.front() + 1);
					}
				}
				if (s_n > 1000) break;
				q.pop();
				q_sl.pop();
			}
			reset_chkmap();
		}
		//cout << s_n << " " << s_l << endl;
		if (s_l == MAX_PATH) {
			cout << -1;
			return 0;
		}
		t.fuel -= s_l;
		
		if (t.fuel < 0) {
			cout << -1;
			return 0;
		}
		t.x = s_x, t.y = s_y;
		t.fuel += (s_l * 2);
		M -= 1;
	}

	cout << t.fuel;
	return 0;
}
