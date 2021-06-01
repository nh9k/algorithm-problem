//백준 주사위 윷놀이
//풀이시간: 2시간 55분
//
//주의
//size(r1)이 안되서 직접 숫자 대입, 벡터였으면 될듯.
//숫자가 40인 부분에 말이 겹칠 수 있는 점을 간과함
//경로 4의 경우에 30이 두번 들어가 if문 조건을 추가 작성함
//dfs() 후에 다시 idx와 route를 제자리로 돌려놓는 것을 깜빡함
//소스 코드가 복잡해서 읽고, 눈으로 디버깅하기에 힘듦이 존재했음
//
//채점 번호	아이디	문제 번호	결과	메모리	시간	언어	코드 길이	제출한 시간
//23173657	nh9k	17825	맞았습니다!!1984	20	C++14 / 수정	5100

#include <iostream>
using namespace std;

int r1[] = { 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40 };
int r2[] = { 10,13,16,19,25,30,35,40 };
int r3[] = { 20,22,24,25,30,35,40};
int r4[] = { 30,28,27,26,25,30,35,40 };

int dice[10];
int max_value = 0;
struct horse {
	int idx;
	int route; //5 == end
}h[4];

bool is_arrive(int hi) {
	if (h[hi].route == 1) {
		if (h[hi].idx >= 21) {
			h[hi].route = 5;
			return true;
		}
	}	
	else if (h[hi].route == 2) {
		if (h[hi].idx >= 8) {
			h[hi].route = 5;
			return true;
		}
	}	
	else if (h[hi].route == 3) {
		if (h[hi].idx >= 7) {
			h[hi].route = 5;
			return true;
		}
	}	
	else if (h[hi].route == 4) {
		if (h[hi].idx >= 8) {
			h[hi].route = 5;
			return true;
		}
	}
	else {
		return true;
	}
	return false;
}

bool is_other(int hinput) {
	if (is_arrive(hinput)) return false;

	for (int hi = 0; hi < 4; ++hi) {
		if (hinput == hi) continue; //다른 말과 비교
		if (h[hi].route == 5) continue; //이미 도착한 말은 비교 x

		if (h[hinput].route == h[hi].route) { //루트가 같은 경우
			if (h[hinput].idx == h[hi].idx) //위치가 같으면
				return true;
		}
		else { //루트가 다른 경우
			if (h[hinput].route == 1) { //루트 1
				if ((h[hi].route == 2) && (h[hi].idx == 0) && (r1[h[hinput].idx] == 10))
					return true;
				if ((h[hi].route == 3) && (h[hi].idx == 0) && (r1[h[hinput].idx] == 20))
					return true;
				if ((h[hi].route == 4) && (h[hi].idx == 0) && (r1[h[hinput].idx] == 30))
					return true;

				if ((h[hi].route == 2) && (r2[h[hi].idx] == 40) && (r1[h[hinput].idx] == 40))
					return true;
				if ((h[hi].route == 3) && (r3[h[hi].idx] == 40) && (r1[h[hinput].idx] == 40))
					return true;
				if ((h[hi].route == 4) && (r4[h[hi].idx] == 40) && (r1[h[hinput].idx] == 40))
					return true;
			}
			else if (h[hinput].route == 2) { //루트 2
				if ((h[hinput].idx == 0) && (h[hi].route == 1) && (r1[h[hi].idx] == 10)) //루트1
					return true;
				if ((r2[h[hinput].idx] == 40) && (h[hi].route == 1) && (r1[h[hi].idx] == 40)) //루트1
					return true;
				if ((h[hi].route == 3) && (r3[h[hi].idx] == r2[h[hinput].idx])) //루트3
					return true;
				if ((h[hi].route == 4) && (r4[h[hi].idx] == r2[h[hinput].idx]) && (h[hi].idx !=0)) //루트4
					return true;
			}
			else if (h[hinput].route == 3) { //루트 3
				if ((h[hinput].idx == 0) && (h[hi].route == 1) && (r1[h[hi].idx] == 20))
					return true;
				if ((r3[h[hinput].idx] == 40) && (h[hi].route == 1) && (r1[h[hi].idx] == 40)) //루트1
					return true;
				if ((h[hi].route == 2) && (r2[h[hi].idx] == r3[h[hinput].idx]))
					return true;
				if ((h[hi].route == 4) && (r4[h[hi].idx] == r3[h[hinput].idx]) && (h[hi].idx != 0))
					return true;
			}			
			else if (h[hinput].route == 4) { //루트 4
				if ((h[hinput].idx == 0) && (h[hi].route == 1) && (r1[h[hi].idx] == 30))
					return true;
				if ((r4[h[hinput].idx] == 40) && (h[hi].route == 1) && (r1[h[hi].idx] == 40)) //루트1
					return true;
				if ((h[hi].route == 2) && (r2[h[hi].idx] == r4[h[hinput].idx]) && (h[hinput].idx != 0))
					return true;
				if ((h[hi].route == 3) && (r3[h[hi].idx] == r4[h[hinput].idx]) && (h[hinput].idx != 0))
					return true;
			}
		}
	}
	return false;
}

void dfs(int sum, int cnt) {
	if (cnt >= 10) {
		if (sum > max_value)
			max_value = sum;
		//cout << "sum: " << sum << endl;
		return;
	}

	for (int hi = 0; hi < 4; ++hi) {
		int memidx = h[hi].idx;
		int memroute = h[hi].route;

		if (h[hi].route == 1) {

			h[hi].idx += dice[cnt];

			if (is_other(hi)) {
				h[hi].idx = memidx;
				h[hi].route = memroute;
				continue;
			}
			else if (!is_arrive(hi)) {
				int origin = r1[h[hi].idx];
				if (r1[h[hi].idx] == 10) {
					h[hi].route = 2;
					h[hi].idx = 0;
				}
				else if (r1[h[hi].idx] == 20) {
					h[hi].route = 3;
					h[hi].idx = 0;
				}
				else if (r1[h[hi].idx] == 30) {
					h[hi].route = 4;
					h[hi].idx = 0;
				}
				dfs(sum + origin, cnt + 1);
			}
			else
				dfs(sum, cnt + 1);
		}		
		else if (h[hi].route == 2) {
			h[hi].idx += dice[cnt];

			if (is_other(hi)) {
				h[hi].idx = memidx;
				h[hi].route = memroute;
				continue;
			}		
			else if (!is_arrive(hi)) {
				dfs(sum + r2[h[hi].idx], cnt + 1);
			}
			else {
				dfs(sum, cnt + 1);
			}			
		}		
		else if (h[hi].route == 3) {
			h[hi].idx += dice[cnt];

			if (is_other(hi)) {
				h[hi].idx = memidx;
				h[hi].route = memroute;
				continue;
			}
			else if (!is_arrive(hi)) {
				dfs(sum + r3[h[hi].idx], cnt + 1);
			}
			else {
				dfs(sum, cnt + 1);
			}
		}		
		else if (h[hi].route == 4) {
			h[hi].idx += dice[cnt];

			if (is_other(hi)) {
				h[hi].idx = memidx;
				h[hi].route = memroute;
				continue;
			}
			else if (!is_arrive(hi)) {
				dfs(sum + r4[h[hi].idx], cnt + 1);
			}
			else {
				dfs(sum, cnt + 1);
			}
		}
		h[hi].idx = memidx;
		h[hi].route = memroute;
	}
}



int main(){
	//입력
	for (int i = 0; i < 10; ++i) {
		cin >> dice[i];
	}

	//알고리즘
	for (int hi = 0; hi < 4; ++hi) {
		h[hi].route = 1;
		h[hi].idx = 0;
	}
	dfs(0,0);

	//결과
	cout << max_value;
	return 0;
}