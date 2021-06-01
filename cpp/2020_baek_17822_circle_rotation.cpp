//백준 원판돌리기
//3시간 풀이
//돌릴 원판의 번호를 고를 때 N->M 실수함
//평균값과 같을 경우 아무것도 취해주면 안됨을 실수함
//5번 예제가 있는 것을 늦게 알아챔
//평균값 구하는 알고리즘을 깜빡함
//
//그외
//배열 인덱스 에러를 피하기 위해, if문 왼쪽부터 검사함(확인해보기)
//rotate 함수는 배열도 사용가능. 처음, 중간, 끝 값만 잘 지정해주고 + 반시계 시계가 생각하는 것과 다름
//벡터 할당 시 기억하기
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

	if ((ni != (N - 1)) && (circle[ni + 1][mi] == num)) { //상		
		erasefail_s = 0;
		BFS(ni + 1, mi, num);
	}

	if ((ni != 0) && (circle[ni - 1][mi] == num)) { //하
		erasefail_s = 0;
		BFS(ni - 1, mi, num);
	}

	if ((mi != 0) && (circle[ni][mi - 1] == num)) { //좌
		erasefail_s = 0;
		BFS(ni, mi - 1, num);
	}
	else if ((mi == 0) && circle[ni][M - 1] == num) {
		erasefail_s = 0;
		BFS(ni, M - 1, num);
	}

	if ((mi != (M - 1)) && (circle[ni][mi + 1] == num)) { //우
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
	// 입력
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

		//회전
		for (int xi = 1; (rot[ti].x*xi) <= N; ++xi) {
			int rotx = (xi * rot[ti].x) - 1; //원판 번호

			if (rot[ti].d == 1) { //시계
				rotate(circle[rotx].begin(), circle[rotx].begin() + rot[ti].k, circle[rotx].end());
			}
			else { //반시계
				rotate(circle[rotx].begin(), circle[rotx].begin() + (M - rot[ti].k), circle[rotx].end());
			}
		}

		//cout << "회전" << endl;
		//for (int ni = 0; ni < N; ++ni) {
		//	for (int mi = 0; mi < M; ++mi) {
		//		cout << circle[ni][mi];
		//	}cout << endl;
		//}cout << endl;


		//BFS
		for (int ni = 0; ni < N; ++ni) {
			for (int mi = 0; mi < M; ++mi) {
				check[ni][mi] = 0; //방문 체크 초기화
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

		//cout << "같은 거 제거후" << endl;
		//for (int ni = 0; ni < N; ++ni) {
		//	for (int mi = 0; mi < M; ++mi) {
		//		cout << circle[ni][mi];
		//	}cout << endl;
		//}cout << endl;

		//같은 수가 없는 경우
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

		//cout << "같은 수 없는 경우" << endl;
		//for (int ni = 0; ni < N; ++ni) {
		//	for (int mi = 0; mi < M; ++mi) {
		//		cout << circle[ni][mi];
		//	}cout << endl;
		//}cout << endl;

		//끝
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

	//끝
	int sum = 0;
	for (int ni = 0; ni < N; ++ni) {
		for (int mi = 0; mi < M; ++mi) {
			sum += circle[ni][mi];
		}
	}
	cout << sum;
	return 0;
}