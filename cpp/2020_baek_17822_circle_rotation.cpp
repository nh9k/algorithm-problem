//���� ���ǵ�����
//3�ð� Ǯ��
//���� ������ ��ȣ�� �� �� N->M �Ǽ���
//��հ��� ���� ��� �ƹ��͵� �����ָ� �ȵ��� �Ǽ���
//5�� ������ �ִ� ���� �ʰ� �˾�è
//��հ� ���ϴ� �˰����� ������
//
//�׿�
//�迭 �ε��� ������ ���ϱ� ����, if�� ���ʺ��� �˻���(Ȯ���غ���)
//rotate �Լ��� �迭�� ��밡��. ó��, �߰�, �� ���� �� �������ְ� + �ݽð� �ð谡 �����ϴ� �Ͱ� �ٸ�
//���� �Ҵ� �� ����ϱ�
//for (int ni = 0; ni < N; ++ni) {
//	circle.push_back(vector <int>(M, 0));
//	for (int mi = 0; mi < M; ++mi) {
//	}
//}

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, M, T;
struct rotation {
	int x;
	int d;
	int k;
}rot[51];
vector <vector<int>> circle;
bool check[51][51];
bool erasefail, erasefail_s;

void BFS(int ni, int mi, int num) {

	if (check[ni][mi] == 0) {
		circle[ni][mi] = 0;
		check[ni][mi] = 1;
	}
	else {
		return;
	}

	if ((ni != (N - 1)) && (circle[ni + 1][mi] == num)) { //��		
		erasefail_s = 0;
		BFS(ni + 1, mi, num);
	}

	if ((ni != 0) && (circle[ni - 1][mi] == num)) { //��
		erasefail_s = 0;
		BFS(ni - 1, mi, num);
	}

	if ((mi != 0) && (circle[ni][mi - 1] == num)) { //��
		erasefail_s = 0;
		BFS(ni, mi - 1, num);
	}
	else if ((mi == 0) && circle[ni][M - 1] == num) {
		erasefail_s = 0;
		BFS(ni, M - 1, num);
	}

	if ((mi != (M - 1)) && (circle[ni][mi + 1] == num)) { //��
		erasefail_s = 0;
		BFS(ni, mi + 1, num);
	}
	else if ((mi == (M - 1)) && circle[ni][0] == num) {
		erasefail_s = 0;
		BFS(ni, 0, num);
	}
}

int main()
{
	// �Է�
	cin >> N >> M >> T;

	int num;
	for (int ni = 0; ni < N; ++ni) {
		circle.push_back(vector <int>(M, 0));
		for (int mi = 0; mi < M; ++mi) {
			cin >> num;
			circle[ni][mi] = num;
		}
	}

	int xi, di, ki;
	for (int ti = 0; ti < T; ++ti) {
		cin >> xi >> di >> ki;
		rot[ti].x = xi;
		rot[ti].d = di;
		rot[ti].k = ki;
	}

	for (int ti = 0; ti < T; ++ti) {

		//ȸ��
		for (int xi = 1; (rot[ti].x*xi) <= N; ++xi) {
			int rotx = (xi * rot[ti].x) - 1; //���� ��ȣ

			if (rot[ti].d == 1) { //�ð�
				rotate(circle[rotx].begin(), circle[rotx].begin() + rot[ti].k, circle[rotx].end());
			}
			else { //�ݽð�
				rotate(circle[rotx].begin(), circle[rotx].begin() + (M - rot[ti].k), circle[rotx].end());
			}
		}

		//cout << "ȸ��" << endl;
		//for (int ni = 0; ni < N; ++ni) {
		//	for (int mi = 0; mi < M; ++mi) {
		//		cout << circle[ni][mi];
		//	}cout << endl;
		//}cout << endl;


		//BFS
		for (int ni = 0; ni < N; ++ni) {
			for (int mi = 0; mi < M; ++mi) {
				check[ni][mi] = 0; //�湮 üũ �ʱ�ȭ
			}
		}
		erasefail = 1;
		int mem = 0;
		for (int ni = 0; ni < N; ++ni) {
			for (int mi = 0; mi < M; ++mi) {
				if (circle[ni][mi] != 0) {
					erasefail_s = 1;
					mem = circle[ni][mi];
					BFS(ni, mi, circle[ni][mi]);
					if (erasefail_s == 1) {
						circle[ni][mi] = mem;
					}
					else {
						erasefail = 0;
					}
				}
			}
		}

		//cout << "���� �� ������" << endl;
		//for (int ni = 0; ni < N; ++ni) {
		//	for (int mi = 0; mi < M; ++mi) {
		//		cout << circle[ni][mi];
		//	}cout << endl;
		//}cout << endl;

		//���� ���� ���� ���
		if (erasefail == 1) {
			float sum = 0;
			int cnt = 0;
			for (int ni = 0; ni < N; ++ni) {
				for (int mi = 0; mi < M; ++mi) {
					sum += circle[ni][mi];
					if (circle[ni][mi] != 0)
						cnt++;
				}
			}
			if (sum == 0) {
				cout << 0;
				return 0;
			}
			sum /= (float)cnt;
			//cout << sum << endl;
			for (int ni = 0; ni < N; ++ni) {
				for (int mi = 0; mi < M; ++mi) {
					if (circle[ni][mi] != 0) {
						if ((float)circle[ni][mi] > sum)
							circle[ni][mi] -= 1;
						else if ((float)circle[ni][mi] < sum)
							circle[ni][mi] += 1;
					}
				}
			}
		}

		//cout << "���� �� ���� ���" << endl;
		//for (int ni = 0; ni < N; ++ni) {
		//	for (int mi = 0; mi < M; ++mi) {
		//		cout << circle[ni][mi];
		//	}cout << endl;
		//}cout << endl;

		//��
		bool end = 1;
		for (int ni = 0; ni < N; ++ni) {
			for (int mi = 0; mi < M; ++mi) {
				if (circle[ni][mi] != 0) {
					end = 0;
					break;
				}
			}
		}
		if (end == 1) {
			cout << 0;
			return 0;
		}

	}

	//��
	int sum = 0;
	for (int ni = 0; ni < N; ++ni) {
		for (int mi = 0; mi < M; ++mi) {
			sum += circle[ni][mi];
		}
	}
	cout << sum;
	return 0;
}