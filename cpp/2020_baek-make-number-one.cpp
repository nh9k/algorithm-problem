/*
@nh9k, baekjoon 1463 1로 만들기
채점 번호	아이디	문제 번호	결과	메모리	시간	언어	코드 길이
19714300	nh9k	1463	맞았습니다!!1984	16	C++14 / 수정	518	
*/
#include <iostream>
using namespace std;

static int Operatormin = 1000000;

void recursion(int num, int OperatorCnt) { //Top-down(dp problem)
	if (Operatormin < OperatorCnt) return;
	if (num <= 1)
	{
		if ((Operatormin > OperatorCnt) && (num==1))
			Operatormin = OperatorCnt;
		return;
	}

	if (num % 3 == 0) {
		recursion(num / 3, OperatorCnt + 1);
	}
	if (num % 2 == 0) {
		recursion(num / 2, OperatorCnt + 1);
	}
	recursion(num - 1, OperatorCnt + 1);
}

int main() {
	int Num;
	cin >> Num;

	recursion(Num, 0);
	cout << Operatormin;
}

