/*
문제: 백준9461, 파도반수열
N=100일 경우 OVERFLOW, s[100]을 위해 longlong형 선언
채점 번호	아이디	문제 번호	결과	메모리	시간	언어	코드 길이
19545394	nh9k	9461	맞았습니다!!1984	4	C++14 / 수정	369
*/

#include <iostream>
long long s[101]; //sequence  //전역선언:s[0] = 0

int main()
{
	int T, N;
	std::cin >> T;

	s[1] = 1;
	s[2] = 1;
	for (int c = 0; c < T; ++c)
	{
		std::cin >> N;

		if (s[N] != 0) {
			std::cout << s[N] << std::endl;
		}
		else {
			for (int i = 3; i <= N; ++i) {
				s[i] = s[i - 3] + s[i - 2];
			}
			std::cout << s[N] << std::endl;
		}
	}
}