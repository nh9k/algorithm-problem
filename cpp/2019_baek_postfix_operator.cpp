#include <iostream>
#include <queue>
#include <stack>
#include <string>
using namespace std;

int isOperator(char a)
{
	if (a == '+' || a == '-')
		return 1;
	else if (a == '*' || a == '/')
		return 2;
}

int main()
{
	freopen("sample_.txt", "r", stdin);
	int tc;
	cin >> tc;
	for (int t = 0; t < tc; t++)
	{
		string input;
		cin >> input;

		string result = "";
		stack <char> oper;
		for (int sz = 0; sz < input.length(); sz++)
		{
			if (input[sz] >= 'A' && input[sz] <= 'Z')
			{
				result += input[sz];
			}
			else if (input[sz] == ')')
			{
				while (oper.top() != '(')
				{
					result += oper.top();
					oper.pop();
				}
				oper.pop(); //'('¸¦ pop
			}
			else if (input[sz] == '(')
				oper.push('(');
			else
			{
				while ((!oper.empty()) && (isOperator(input[sz]) <= isOperator(oper.top())))
				{
					if (oper.top() == '(') break;
					result += oper.top();
					oper.pop();
					
				}
				oper.push(input[sz]);
			}
		}
		while (!oper.empty())
		{
			result += oper.top();
			oper.pop();
		}
		cout << result << '\n';
	}


	return 0;
}