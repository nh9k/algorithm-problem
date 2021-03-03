/*
@nh9k
문제 번호	문제 이름		채점 번호	아이디	문제 번호	결과			메모리	시간	언어			코드 길이	
백준1003	피보나치 함수	19538406	nh9k	1003		맞았습니다!!		1984	4		C++14 / 수정	665
*/

#include <iostream>
using namespace std;
typedef struct {
	int zero_, one_, num;
}memory;
memory m[41];

int fibonacci(int n) {
	if (m[n].num != 0) {
		return m[n].num;
	}
	if (n == 0) {
		m[n].num = 0;
		m[n].one_ = 0;
		m[n].zero_ = 1;
		return 0;
	}
	else if (n == 1) {
		m[n].num = 1;
		m[n].one_ = 1;
		m[n].zero_ = 0;
		return 1;
	}
	else {
		m[n].num = fibonacci(n - 1) + fibonacci(n - 2);
		m[n].one_ = m[n - 1].one_ + m[n - 2].one_;
		m[n].zero_ = m[n - 1].zero_ + m[n - 2].zero_;
		return m[n].num;
	}
}

int main() {
	int N, T;
	cin >> T;
	for (int i = 0; i < T; ++i)
	{
		cin >> N;
		fibonacci(N);
		cout <<  m[N].zero_ << " " << m[N].one_ << endl;
	}
}