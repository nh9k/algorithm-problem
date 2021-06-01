//1�ð� 15�� ���� Ǯ��.
//(1)�迭�� ũ��� 
//(2)������ �ʱ���ǥ, 
//(3)y���� ������ �򰥷���
//(4)ksum�� �ʱ�ȭ������ �ʾ�
//������� ����

#include <iostream>
using namespace std;

struct atom {
	int x, y, d, k;
}a[1001];
int an, ksum;
int dx[4] = { 0,0,-1,1 };
int dy[4] = { -1,+1,0,0 };
int map[4001][4001];

void simulation()
{
	bool repeat = true;
	while (repeat)
	{
		for (int ai = 0; ai < an; ++ai)
		{
			if (a[ai].k == 0) continue;
			a[ai].x += dx[a[ai].d];
			a[ai].y += dy[a[ai].d];
			if (a[ai].x < 0 || a[ai].x>4000 || a[ai].y < 0 || a[ai].y>4000)
			{
				a[ai].k = 0;
				continue;
			}
			map[a[ai].y][a[ai].x] += a[ai].k;
		}

		for (int ai = 0; ai < an; ++ai)
		{
			if (a[ai].k == 0) continue;
			if (map[a[ai].y][a[ai].x] != a[ai].k)
			{
				ksum += a[ai].k;
				a[ai].k = 0;
			}
		}

		for (int ai = 0; ai < an; ++ai)
		{
			if (a[ai].x < 0 || a[ai].x>4000 || a[ai].y < 0 || a[ai].y>4000)
			{
				continue;
			}
			map[a[ai].y][a[ai].x] = 0;
		}

		repeat = false;
		for (int ai = 0; ai < an; ++ai)
		{
			if (a[ai].k)
			{
				repeat = true;
				break;
			}
		}
	}
}

int main()
{
	int t;
	cin >> t;
	for (int ti = 0; ti < t; ++ti)
	{
		cin >> an;
		int tmpx, tmpy, tmpd, tmpk;

		for (int ai = 0; ai < an; ++ai)
		{
			cin >> tmpx >> tmpy >> tmpd >> tmpk;
			a[ai] = { (tmpx * 2 )+ 2000, (tmpy*(-2)) + 2000, tmpd, tmpk };
		}

		ksum = 0;
		simulation();
		cout << "#" << ti + 1 << " " << ksum << endl;
	}

	return 0;
}

