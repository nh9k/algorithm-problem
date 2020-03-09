#include <iostream>
using namespace std;
int e_m;
int money[6] = { 500,100,50,10,5,1 };

int main()
{
	cin >> e_m;
	e_m = 1000 - e_m;

	int cnt = 0, idx = 0;
	while (1)
	{
		if (e_m == 0) break;
		if (e_m >= money[idx])
		{
			e_m -= money[idx];
			cnt++;
		}
		else idx++;
	}
	cout << cnt;
}