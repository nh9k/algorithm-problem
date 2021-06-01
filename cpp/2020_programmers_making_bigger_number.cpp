//6자리 수(if number.length==10 and k==4)를 뽑는다면 
//뒤에서 5자리 수를 제외한 앞에서 가장 큰 1자리수 뽑기
//다음, 뒤에서 4자리수를 제외한 앞에서 가장 큰 1자리수 뽑기...(but, 앞 과정 다음 index부터)
//채점을 시작합니다.
//정확성  테스트
//테스트 1 〉	통과(0.00ms, 3.86MB)
//테스트 2 〉	통과(0.00ms, 3.73MB)
//테스트 3 〉	통과(0.00ms, 3.91MB)
//테스트 4 〉	통과(0.01ms, 3.93MB)
//테스트 5 〉	통과(0.02ms, 3.79MB)
//테스트 6 〉	통과(2.52ms, 3.95MB)
//테스트 7 〉	통과(5.39ms, 4.01MB)
//테스트 8 〉	통과(52.41ms, 4.02MB)
//테스트 9 〉	통과(1.25ms, 5.39MB)
//테스트 10 〉	통과(1820.48ms, 5.57MB)
//테스트 11 〉	통과(0.00ms, 3.91MB)
//테스트 12 〉	통과(0.00ms, 3.78MB)
//채점 결과
//정확성 : 100.0
//	합계 : 100.0 / 100.0
#include <string>
#include <vector>

using namespace std;

string solution(string number, int k) {
	string answer = "";
	k = number.size() - k;
	int prepick = 0;
	for (int left_cnt = k; left_cnt > 0; --left_cnt)
	{
		int max_num = number[prepick];
		int max_numi = prepick;
		for (int pick = prepick; pick < (number.size() - (left_cnt - 1)); ++pick)
		{
			if (max_num < number[pick])
			{
				max_num = number[pick];
				max_numi = pick;
			}
		}
		answer += max_num;
		prepick = max_numi + 1;
	}
	return answer;
}

//k혹은 number.length()-k만큼 숫자를 뽑아서 가장 큰 수인 최종 answer을 정하는 방법 -> 시간 초과
//#include <string>
//#include <vector>
//
//using namespace std;
//int cntK;
//string Num, answer;
//vector <int> elist;
//
//void eraseK(int idx, int cnt)
//{
//	if (Num.length() - idx + cnt < cntK)
//		return;
//	if (cntK == cnt)
//	{
//		string temp = Num;
//		for (int e = elist.size() - 1; e >= 0; --e)
//			temp.erase(elist[e], 1);
//		if (stoi(temp) > stoi(answer))
//			answer = temp;
//		return;
//	}
//	for (int i = idx; i < Num.length(); ++i)
//	{
//		elist.push_back(i);
//		eraseK(i + 1, cnt + 1);
//		elist.pop_back();
//	}
//}
//
//void pickK(int idx, int cnt, string num)
//{
//	if (Num.length() - idx + cnt < cntK)
//		return;
//	if (cntK == cnt && (stoi(answer) < stoi(num)))
//	{
//		answer = num;
//		return;
//	}
//	for (int i = idx; i < Num.length(); ++i)
//		pickK(i + 1, cnt + 1, num + Num[i]);
//}
//
//string solution(string number, int k) {
//	answer = "0";
//	Num = number;
//	if (k < number.length() - k) {
//		cntK = k;
//		eraseK(0, 0);
//	}
//	else {
//		cntK = number.length() - k;
//		pickK(0, 0, "0");
//	}
//
//	if (answer.length() == number.size() - k)
//		return answer;
//	else
//		return answer.substr(1, answer.length() - 1);
//}
//
//#include <iostream>
//
//int main()
//{
//	cout << solution("98769876", 3) << endl;
//	cout << solution("1111", 2) << endl;
//	cout << solution("69240278", 2) << endl;
//	string a = "12";
//	string b = "23";
//	cout << a + b << endl;
//}