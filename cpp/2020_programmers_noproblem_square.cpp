//올바르지 않은 논리로 풀었음
//double형과 longlong형의 문제가 있기 때문
//gcd로 풀기
#include <math.h>
#include <iostream>
using namespace std;

long long solution(int w, int h)
{
	long long answer = (long long)w * (long long)h;
	long long mem = 0;

	for (int i = 1; i <= w; ++i)
	{
		double hx = (double)((long long)h*(long long)i) / (double)w;
		answer -= (ceil(hx) - mem);
		mem = floor(hx);
	}
	return answer;
}

int main(void)
{
	cout << solution(8, 12);
}