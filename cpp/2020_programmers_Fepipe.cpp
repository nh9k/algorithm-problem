#include <string>
#include <vector>
#include <iostream>
using namespace std;

int solution(string arrangement) { // ���� ���������� �����ִ� ���
	int answer = 0;

	vector <int> stk;
	for (int i = 0; i < arrangement.size(); ++i)
	{
		if (arrangement[i] == '(')
		{
			stk.push_back(0);
		}
		else if(stk.size()!=1)
		{
			if (stk[stk.size() - 1] == 0)
			{
				stk[stk.size() - 2] += 1;
			}
			else
			{
				answer += stk[stk.size() - 1] + 1;
				stk[stk.size() - 2] += stk[stk.size() - 1];
			}
			stk.pop_back();
		}
		else
		{
			if (stk[stk.size() - 1] != 0)
				answer += stk[stk.size() - 1] + 1;
			stk.pop_back();				
		}
		cout << answer << endl;
	}
	return answer;
}

#include <stack>

int good_solution(string a) { //��� ���� ������ ���� or  ) �������� �ѹ��� �����ִ� ���
	int answer = 0;
	stack<char> s;

	for (int i = 0; i < a.length(); i++) {
		if (a[i] == '(')
			s.push(a[i]);
		else {
			s.pop();
			if (a[i - 1] == '(')
				answer += s.size();
			else
				answer++;
		}
	}
	return answer;
}

int main()
{
	solution("()(((()())(())()))(())");
	return 0;
}