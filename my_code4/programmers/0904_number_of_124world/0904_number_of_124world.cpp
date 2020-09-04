//프로그래머스 - 124 나라의 숫자
#include <string>
#include <vector>
#include <iostream>

using namespace std;

string solution(int n) {
	string answer = "";

	while (n != 0) {
		if (n % 3 == 0)
		{
			answer = "4" + answer;
			n = n / 3 - 1;
		}
		else
		{
			answer = to_string(n % 3) + answer;
			n = n / 3;
		}		
	}


	return answer;
}

int main(void) {
	cout << solution(16);

	return 0;
}