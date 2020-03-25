#include <iostream>
using namespace std;
int n, m, map[8][8], cctv_idx, dontlook;
typedef struct {
	int x, y, num;
}CCTV;
CCTV cctv[8];
int mx[4] = { -1,0,1,0 }, my[4] = { 0,1,0,-1 }, mov[6] = {0,4,2,4,4,1}; //mov의 0인덱스 주의!!

void go(int idx, int go_dir)
{
	int temp_x, temp_y;

	temp_x = cctv[idx].x + mx[go_dir], temp_y = cctv[idx].y + my[go_dir];
	while (temp_x >= 0 && temp_x < n && temp_y >= 0 && temp_y < m) //조건이 ||아니고 &&인거 주의!!
	{
		if (map[temp_x][temp_y] == 0)
		{
			map[temp_x][temp_y] = 8;
		}
		else if (map[temp_x][temp_y] == 6) //벽
		{
			return;
		}
		//cctv가 있거나 이미 간 곳이면 그냥 넘어감
		temp_x += mx[go_dir], temp_y += my[go_dir];
	}

}

void display_map(int idx, int dir)
{
	if (cctv[idx].num == 1) //idx가 아니라 cctv[idx].num, 즉 cctv 종류 번호를 넣는거 조심!!
	{
		go(idx, dir);
	}
	else if (cctv[idx].num == 2)
	{
		go(idx, dir);
		go(idx, dir + 2);
	}
	else if (cctv[idx].num == 3)
	{
		go(idx, dir);
		if(dir==3) go(idx, 0);
		else go(idx, dir + 1);
	}
	else if (cctv[idx].num == 4)
	{
		go(idx, dir);
		if (dir == 2)
		{
			go(idx, dir + 1);
			go(idx, 0);
		}
		else if (dir == 3)
		{
			go(idx, 0);
			go(idx, 1);
		}
		else
		{
			go(idx, dir + 1);
			go(idx, dir + 2);
		}
	}
	else
	{
		go(idx, dir);
		go(idx, dir+1);
		go(idx, dir+2);
		go(idx, dir+3);
	}
}

void dfs(int cnt)
{
	if (cnt == cctv_idx)
	{
		int temp = 0;
		for (int ni = 0; ni < n; ++ni)
		{
			for (int mi = 0; mi < m; ++mi)
			{
				if (map[ni][mi] == 0)
					temp++;
			}
		}
		if (dontlook > temp)
			dontlook = temp;
		return;
	}
	for (int i = 0; i < mov[cctv[cnt].num]; ++i)
	{
		int cpy_map[8][8];
		for (int ni = 0; ni < n; ++ni)
		{
			for (int mi = 0; mi < m; ++mi)
			{
				cpy_map[ni][mi] = map[ni][mi];
			}
		}
		display_map(cnt, i);
		dfs(cnt + 1);

		for (int ni = 0; ni < n; ++ni)
		{
			for (int mi = 0; mi < m; ++mi)
			{
				map[ni][mi] = cpy_map[ni][mi];
			}
		}
	}
}

int main()
{
	cin >> n >> m;
	for (int ni = 0; ni < n; ++ni)
	{
		for (int mi = 0; mi < m; ++mi)
		{
			cin >> map[ni][mi];
			if (map[ni][mi] != 0 && map[ni][mi] != 6) //여기 ||이 아니라 &&인 것 조심!!
			{
				cctv[cctv_idx].x = ni, cctv[cctv_idx].y = mi, cctv[cctv_idx].num = map[ni][mi];
				cctv_idx++;
			}			
		}
	}

	dontlook = 65;
	dfs(0);
	cout << dontlook;
}