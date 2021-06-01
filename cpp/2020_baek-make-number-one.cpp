/*
@nh9k, baekjoon 1463 1�� �����
ä�� ��ȣ	���̵�	���� ��ȣ	���	�޸�	�ð�	���	�ڵ� ����
19714300	nh9k	1463	�¾ҽ��ϴ�!!1984	16	C++14 / ����	518	
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

