#include <iostream>
#include <algorithm>
using namespace std;
int cost[4], plan[12];
int temp[13];

int dp()
{
	
	for (int pi = 1; pi < 13; ++pi)
	{
		temp[pi] = min(plan[pi-1] * cost[0], cost[1]);
	}

	for (int pi = 0; pi < 13; ++pi)
	{
		if (pi > 0)
			temp[pi] += temp[pi - 1];
		if (pi > 2)
			temp[pi] = min(temp[pi], temp[pi-3]+cost[2]);
	}

	if (cost[3] < temp[12])
		return cost[3];
	else
		return temp[12];

}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	int tc;
	cin >> tc;
	for (int t = 0; t < tc; t++)
	{
		cin >> cost[0] >> cost[1] >> cost[2] >> cost[3];

		for (int pi = 0; pi < 12; ++pi)
			cin >> plan[pi];

		cout << "#" << t+1 << " " << dp()<<"\n";
	}
}