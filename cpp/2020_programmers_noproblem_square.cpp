//�ùٸ��� ���� ���� Ǯ����
//double���� longlong���� ������ �ֱ� ����
//gcd�� Ǯ��
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