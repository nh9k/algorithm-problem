#include <iostream>
#define million 1000000
int n, room[million], first_d, second_d;
long long cnt = 0;
using namespace std;

void calculation()
{
	for (int ni = 0; ni < n; ni++)
	{
		room[ni] -= first_d;

		if (room[ni] <= 0)
			continue;

		if (room[ni] <= second_d)
		{
			cnt++;
		}
		else
		{
			int share = room[ni] / second_d;
			int floating_p = room[ni] % second_d;
			if (floating_p == 0)
			{
				cnt += share;
			}
			else
			{
				cnt += (share + 1);
			}
		}
	}
	cnt += n;

	return;
}

int main()
{
	//while (1)
	//{
	//cout.precision(11);
	//cout << fixed << 3 << endl;
	//cout<< fixed<< double(3) << endl;
	//cout << fixed << long long(3) << endl;
	cin >> n;
	for (int ni = 0; ni < n; ni++)
	{
		cin >> room[ni];
	}
	cin >> first_d >> second_d;

	calculation();
	cout << cnt << endl;
	//}
	return 0;
} 