/*
@nh9k @다시보기
문제 번호 문제 이름 채점 번호	아이디	문제 번호	결과		메모리	시간	언어	코드 길이
백준1904	01타일	19538852	nh9k	1904	맞았습니다!!	5892	4ms	C++14 / 수정	538B
*/

#include <iostream>
using namespace std;
//int cnt;

//void tile(int N, int cur_N)
//{
//	if (N == cur_N)
//	{
//		cnt++;
//		return;
//	}
//	if (N < cur_N)
//		return;
//	for (int i = 0; i < 2; ++i)
//	{
//		if (i == 0)
//			tile(N, cur_N + 2);
//		else
//			tile(N, cur_N + 1);
//	}
//}
int N, d[1000001];

int main() {
	//int N;
	//cin >> N;
	//cnt = 0;
	//tile(N, 0);
	//cout << cnt % 15746;


	cin >> N;
	d[0] = 0; d[1] = 1; d[2] = 2;
	for (int i = 3; i <= N; i++) {
		d[i] = d[i - 2] + d[i - 1];
		d[i] %= 15746;
	}
	cout << d[N];
}