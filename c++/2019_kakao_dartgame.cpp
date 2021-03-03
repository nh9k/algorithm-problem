#include <string>
#include <cstring>
#include <iostream>
using namespace std;

int solution(string dartResult) {
	int result[3], ridx = -1;
	int length = dartResult.length();
	bool flag = false;
	for (int i = 0; i < length; i++)
	{
		if (flag == true) {
			flag = false;
			continue;
		}
		if (dartResult[i] >= '0' && dartResult[i] <= '9') //점수
		{ 
			ridx++;
			if (dartResult[i + 1] == '0') {
				result[ridx] = 10;
				flag = true;
				continue;
			}
			result[ridx] = dartResult[i] - '0';
		}

		if (dartResult[i] >= 'A' && dartResult[i] <= 'Z') //점수 1,2,3제곱
		{
			if (dartResult[i] == 'D')
			{
				result[ridx] *= result[ridx];
			}
			else if (dartResult[i] == 'T')
			{
				result[ridx] = (result[ridx] * result[ridx] * result[ridx]);
			}
		}

		if (dartResult[i] == '*')//스타상 아차상
		{
			if (ridx == 0) //첫번째 점수
			{
				result[ridx] *= 2;
			}
			else
			{
				result[ridx] *= 2;
				result[ridx - 1] *= 2;
			}
		}
		else if (dartResult[i] == '#')
		{
			result[ridx] *= (-1);
		}
	}
	int answer = result[0] + result[1] + result[2];
	return answer;
}


int main()
{
	cout << solution("1S2D * 3T") << endl;

	cout << solution("1D2S#10S") << endl;
	cout << solution("1D2S0T") << endl;
	cout << solution("1S*2T*3S") << endl;
	cout << solution("1D#2S*3S") << endl;
	cout << solution("1T2D3D#") << endl;
	cout << solution("1D2S3T*") << endl;


}