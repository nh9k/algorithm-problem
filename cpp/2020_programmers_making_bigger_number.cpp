//6�ڸ� ��(if number.length==10 and k==4)�� �̴´ٸ� 
//�ڿ��� 5�ڸ� ���� ������ �տ��� ���� ū 1�ڸ��� �̱�
//����, �ڿ��� 4�ڸ����� ������ �տ��� ���� ū 1�ڸ��� �̱�...(but, �� ���� ���� index����)
//ä���� �����մϴ�.
//��Ȯ��  �׽�Ʈ
//�׽�Ʈ 1 ��	���(0.00ms, 3.86MB)
//�׽�Ʈ 2 ��	���(0.00ms, 3.73MB)
//�׽�Ʈ 3 ��	���(0.00ms, 3.91MB)
//�׽�Ʈ 4 ��	���(0.01ms, 3.93MB)
//�׽�Ʈ 5 ��	���(0.02ms, 3.79MB)
//�׽�Ʈ 6 ��	���(2.52ms, 3.95MB)
//�׽�Ʈ 7 ��	���(5.39ms, 4.01MB)
//�׽�Ʈ 8 ��	���(52.41ms, 4.02MB)
//�׽�Ʈ 9 ��	���(1.25ms, 5.39MB)
//�׽�Ʈ 10 ��	���(1820.48ms, 5.57MB)
//�׽�Ʈ 11 ��	���(0.00ms, 3.91MB)
//�׽�Ʈ 12 ��	���(0.00ms, 3.78MB)
//ä�� ���
//��Ȯ�� : 100.0
//	�հ� : 100.0 / 100.0
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

//kȤ�� number.length()-k��ŭ ���ڸ� �̾Ƽ� ���� ū ���� ���� answer�� ���ϴ� ��� -> �ð� �ʰ�
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