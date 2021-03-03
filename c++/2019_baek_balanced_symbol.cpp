#include <iostream>
#include <string>
#include <stack>
using namespace std;

void solution(string input)
{
	int ssz = input.length();
	stack <char> balance;

	for (int sz = 0; sz < ssz; ++sz)
	{	
		if (balance.empty()) {
			if (input[sz] == ')') 
			{
				cout << "NO" << '\n';
				return;
			}
			balance.push('(');
			continue;
		}
		
		if (input[sz]==')')
		{
			balance.pop();
		}
		else
		{
			balance.push('(');
		}
	}
	if (!balance.empty())
	{
		cout << "NO" << '\n';
		return;
	}
	else
		cout << "YES" << '\n';
}

int main()
{
	int tc;
	cin >> tc;
	string input;
	for (int t = 0; t < tc; ++t)
	{
		cin >> input;
		solution(input);
	}

	return 0;
}