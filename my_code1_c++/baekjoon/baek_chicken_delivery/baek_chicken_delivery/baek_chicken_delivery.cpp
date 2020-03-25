#include <iostream>
//#include <cmath>
#include <algorithm>
using namespace std;

int n, m;
typedef struct {
	int x, y, d_sum;
}chicken;
chicken c[13];
bool onoff_c[13];
typedef struct {
	int x, y;
}home;
home h[100];
int hsz, csz;
int minimum;

int sumof_minimum()
{
	int sum = 0;
	int minimum_d;
	for (int i = 0; i < hsz; i++)
	{
		minimum_d = 1000000;
		for (int j = 0; j < csz; j++)
		{
			if (onoff_c[j] == 0 && !(csz == 1 || csz == m)) continue;

			if (minimum_d > abs(h[i].x - c[j].x) + abs(h[i].y - c[j].y))
			{
				minimum_d = abs(h[i].x - c[j].x) + abs(h[i].y - c[j].y);
			}
		}
		sum += minimum_d;
	}
	return sum;
}

void determine_chicken(int idx, int cnt)
{
	if (cnt == m)
	{   
		int  temp = sumof_minimum();
		if (minimum > temp)
		{
			minimum = temp;
		}
		return ;
	}

	for (int i = idx; i < csz; i++)
	{
		onoff_c[i] = true;
		determine_chicken(i + 1, cnt + 1);
		onoff_c[i] = false;
	}
	return;
}

int main() {
	cin >> n >> m;
	int temp;
	hsz = 0, csz = 0;

	for (int ni = 0; ni < n; ni++)
	{
		for (int nj = 0; nj < n; nj++)
		{
			cin >> temp;
			if (temp == 1) //집
			{
				h[hsz].x = ni;
				h[hsz].y = nj;
				hsz++;
			}
			else if (temp == 2) //치킨 집
			{
				c[csz].x = ni;
				c[csz].y = nj;
				csz++;
			}
		}
	}
	if (csz == 1 || csz == m)
	{
		cout << sumof_minimum() << "\n";
	}
	else {
		minimum = 1000000;
		determine_chicken(0,0);
		cout << minimum << "\n";
	}
	return 0;
}
/*
4 2
0 2 0 1
0 1 2 2
0 0 0 0
1 0 2 1
*/
