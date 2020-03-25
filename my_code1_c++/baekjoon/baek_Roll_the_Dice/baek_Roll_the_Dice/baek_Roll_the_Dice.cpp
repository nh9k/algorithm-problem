#include <iostream>
using namespace  std;

typedef struct {
	int top=0, bottom=0, west=0, east=0, north=0, south=0;
}DICE;

DICE d;
int map[20][20];
int n, m, x, y, k;
//동:1, 서:2, 북:3, 남:4
int dy[5] = { 0,1,-1,0,0 }, dx[5] = { 0,0,0,-1,1 };

void dice(int dir)
{
	int temp = d.top;

	if (dir == 2) //동
	{
		d.top = d.east;
		d.east = d.bottom;
		d.bottom = d.west;
		d.west = temp;
	}
	else if (dir == 1)//서
	{
		d.top = d.west;
		d.west = d.bottom;
		d.bottom = d.east;
		d.east = temp;
	}
	else if (dir == 4)//북
	{
		d.top = d.north;
		d.north = d.bottom;
		d.bottom = d.south;
		d.south = temp;
	}
	else//남
	{
		d.top = d.south;
		d.south = d.bottom;
		d.bottom = d.north;
		d.north = temp;
	}
	return;
}

void rolling(int dir)
{
	x += dx[dir], y += dy[dir];
	if (x < 0 || x >= n || y < 0 || y >= m)
	{
		x -= dx[dir], y -= dy[dir];
		return;
	}

	dice(dir);
	if (map[x][y] != 0) //map -> 주사위의 바닥면으로 복사, 칸에 쓰인 수는 0
	{
		//cout << map[x][y] << endl;
		d.bottom = map[x][y];
		map[x][y] = 0;
	}
	else //주사위의 바닥면 -> map 으로 복사
	{
		map[x][y] = d.bottom;
	}
	
	cout << d.top << "\n";
	return;
}

int main()
{
	cin >> n >> m >> x >> y >> k;
	for (int ni = 0; ni < n; ni++)
	{
		for (int mi = 0; mi < m; mi++)
		{
			cin >> map[ni][mi];
		}
	}
	for (int ki = 0; ki < k; ki++)
	{
		int temp;
		cin >> temp;
		rolling(temp);
	}
	return 0;
}