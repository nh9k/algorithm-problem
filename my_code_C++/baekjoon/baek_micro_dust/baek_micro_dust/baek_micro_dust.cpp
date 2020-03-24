#include <iostream>
using namespace std;
int r, c, t;
int map[51][51], cpy_map[51][51];
int dx[4] = { -1,0,1,0 }, dy[4] = { 0,1,0,-1 }, air[2][4] = { { 1,0,3,2 },{ 1,2,3,0 } };
typedef struct {
	int x[2], y[2];
}AIR;
AIR device;

void spread()
{
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			if (map[i][j] != 0 && map[i][j] != -1)
			{
				if (map[i][j] < 5) {
					cpy_map[i][j] += map[i][j];
					continue;
				}
				int cnt = 0;
				for (int m = 0; m < 4; ++m)
				{
					if (i + dx[m] < 0 || i + dx[m] >= r || j + dy[m] < 0 || j + dy[m] >= c) continue;
					else if (map[i + dx[m]][j + dy[m]] == -1) continue; 

					cpy_map[i + dx[m]][j + dy[m]] += map[i][j] / 5;
					++cnt;
				}
				cpy_map[i][j] += map[i][j] - ((map[i][j] / 5) * cnt);
			}
			else if(map[i][j] == -1) cpy_map[i][j] = -1;
		}
	}
}

void clean_device(int up_down)
{
	int temp_x = device.x[up_down] + dx[air[up_down][0]], temp_y = device.y[up_down] + dy[air[up_down][0]];
	int dir = 0;
	int temp_value1 = 0, temp_value2;
	while (map[temp_x][temp_y] != -1)
	{
		if (temp_y >= c || temp_x < 0 || temp_y < 0 || temp_x >= r)
		{
			temp_x -= dx[air[up_down][dir]], temp_y -= dy[air[up_down][dir]];
			++dir;
			temp_x += dx[air[up_down][dir]], temp_y += dy[air[up_down][dir]];
			continue;
		}

		temp_value2 = map[temp_x][temp_y];
		map[temp_x][temp_y] = temp_value1;
		temp_value1 = temp_value2;

		temp_x += dx[air[up_down][dir]], temp_y += dy[air[up_down][dir]];
	}

	return;
}

int check()
{
	int sum = 0;
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			if (map[i][j] != 0 && map[i][j] != -1)
			{
				//cout << map[i][j] << endl;
				sum += map[i][j];
			}
		}
	}
	return sum;
}

int main()
{
	cin >> r >> c >> t;
	int tempidx = 0;
	for (int i = 0; i < r; ++i)
	{
		for (int j = 0; j < c; ++j)
		{
			cin >> map[i][j];
			if (map[i][j] == -1) {
				device.x[tempidx] = i, device.y[tempidx] = j;
				tempidx++;
			}
		}
	}

	for (int tcnt = 0; tcnt < t; ++tcnt)
	{
		spread();

		//cpy_map[device.x[0]][device.y[0]] = -1;
		//cpy_map[device.x[1]][device.y[1]] = -1;

		//cout << endl;
		for (int i = 0; i < r; ++i)
		{
			for (int j = 0; j < c; ++j)
			{
				//cout << cpy_map[i][j] << " ";
				map[i][j] = cpy_map[i][j];
				cpy_map[i][j] = 0;
			}//cout << endl;
		}//cout << endl;

		clean_device(0);
		clean_device(1);

		//for (int i = 0; i < r; ++i)
		//{
		//	for (int j = 0; j < c; ++j)
		//	{
		//		cout << map[i][j] << " ";
		//	}cout << endl;
		//}cout << endl;
	}

	cout << check();
	return 0;
}