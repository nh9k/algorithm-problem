#include <iostream>
using namespace std;
int num, number[11], oper[4];//input
int min_value, max_value;

void dfs(int calculate, int idx, int plus, int minus, int multiple, int devide)
{
	if (idx == num)
	{
		if (min_value > calculate)
			min_value = calculate;
		if (max_value < calculate)
			max_value = calculate;
		return;
	}

	if (plus) dfs(calculate + number[idx], idx + 1, plus - 1, minus, multiple, devide);
	if(minus) dfs(calculate - number[idx], idx + 1, plus, minus-1, multiple, devide);
	if(multiple) dfs(calculate * number[idx], idx + 1, plus, minus, multiple-1, devide);
	if(devide) dfs(calculate / number[idx], idx + 1, plus, minus, multiple, devide-1);
}

int main() 
{	
	cin >> num;
	for (int n = 0; n < num; n++)
	{
		cin >> number[n];
	}
	for (int n = 0; n < 4; n++)
	{
		cin >> oper[n];
	}
	min_value = 1e9;
	max_value = (-1)*1e8;
	dfs(number[0], 1, oper[0], oper[1], oper[2], oper[3]);
	cout << max_value << '\n' << min_value << '\n';
	return 0;
}