#include <iostream>
#include <vector>
using namespace std;

int n, map[101][101];
int dx[4] = { 1,0,-1,0 }, dy[4] = { 0,-1,0,1 }, clockwise[4] = { 3,0,1,2 }, oppos[4] = { 2,3,0,1 };

void dragon_curve(int x, int y, int d, int g) //드래곤 커브를 map에 표시하는 함수
{
	//cout << d << endl;
	vector <int> curve;
	curve.push_back(d);
	map[x][y] = 1;
	x += dx[d], y += dy[d];
	map[x][y] = 1;

	int cnt = 0;
	while (cnt != g)
	{
		int vsz = curve.size();
		for (int idx = vsz - 1; idx != -1; idx--)
		{
			d = clockwise[oppos[curve[idx]]];
			x += dx[d];
			y += dy[d];
			curve.push_back(d);
			if (x < 0 || x>100 || y < 0 || y>100)
				continue;

			map[x][y] = 1;
		}
		cnt++;
	}

	return;
}

int check() //격자를 돌면서 정사각형이 몇개인지 세아림
{
	int cnt = 0;
	for (int y = 0; y < 100; y++)
	{
		for (int x = 0; x < 100; x++)
		{
			//cout << map[y][x];
			if (map[y][x] && map[y][x + 1] && map[y + 1][x] && map[y + 1][x + 1])
			{
				cnt++;
			}
		}//cout << endl;
	}//cout << endl;
	return cnt;
}

int main()
{
	//while (1)
	//{
	cin >> n;
	for (int ni = 0; ni < n; ni++)
	{
		int x, y, d, g; //시작점, 시작방향, 세대
		cin >> x >> y >> d >> g;
		dragon_curve(x, y, d, g);
	}
	cout << check() << endl;
	//}

	return 0;
}