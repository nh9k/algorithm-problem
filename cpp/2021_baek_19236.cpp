//제출 번호	아이디	문제	결과	메모리	시간	언어	코드 길이	제출한 시간
//26934114	nh9k	19236	맞았습니다!!2016	0	C++17 / 수정	2590	30초 전
//풀이 시간: 약 2시간
//dfs 돌릴때 조심해야하는 부분인! 
//원래대로 되돌려 놓는 것! fish 위치, 방향, map 기록
//조심!


#include <iostream>
using namespace std;
int map[4][4];
int eatmax;
#define SN 100

struct {
	int x, y, dir;
}fish[17];

struct {
	int x, y, dir;
}shark;

int dirx[8] = { -1,-1,0,1,1,1,0,-1 };
int diry[8] = { 0,-1,-1,-1,0,1,1,1 };

int chk_map(int x, int y)
{
	if (x < 0 || y < 0 || x >= 4 || y >= 4)
		return 2;
	else if (map[x][y] == SN)
		return 2;
	else if (map[x][y] != 0)
		return 1;
	else
		return 0;
}

void change_fish(int num, int mx, int my)
{
	if (map[mx][my] == 0)
	{
		map[fish[num].x][fish[num].y] = 0;
	}
	else
	{
		map[fish[num].x][fish[num].y] = map[mx][my];
		fish[map[mx][my]].x = fish[num].x;
		fish[map[mx][my]].y = fish[num].y;
	}
	map[mx][my] = num;
	fish[num].x = mx;
	fish[num].y = my;
}

void dfs(int eatsum)
{
	if (eatsum > eatmax)
		eatmax = eatsum;

	for (int i = 1; i < 17; ++i) { //fish moving
		if (fish[i].dir == -1) continue;

		for (int j = 0; j < 8; ++j) {
			int mx = fish[i].x + dirx[fish[i].dir];
			int my = fish[i].y + diry[fish[i].dir];

			if (chk_map(mx, my) < 2) {
				change_fish(i, mx, my);
				break;
			}
			else
			{
				fish[i].dir += 1;
				if (fish[i].dir >= 8) fish[i].dir = 0;
			}
		}

	}
	int memx[17], memy[17], memdir[17], memmap[4][4];
	for (int i = 1; i < 17; ++i) {
		memx[i] = fish[i].x;
		memy[i] = fish[i].y;
		memdir[i] = fish[i].dir;
	}
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			memmap[i][j] = map[i][j];
		}
	}

	for (int i = 0; i < 3; ++i) { //shark moving
		int mx = (shark.x + (dirx[shark.dir] * (i+1)));
		int my = (shark.y + (diry[shark.dir] * (i+1)));

		if (chk_map(mx, my) == 1)
		{
			int eatnum = map[mx][my];
			int sx = shark.x;
			int sy = shark.y;
			int sdir = shark.dir;

			map[shark.x][shark.y] = 0;
			shark.x = mx; shark.y = my; shark.dir = fish[map[mx][my]].dir;
			fish[map[mx][my]].dir = -1;
			map[mx][my] = SN;
			
			dfs(eatsum + eatnum);

			map[mx][my] = eatnum;
			fish[eatnum].dir = shark.dir;
			shark.x = sx, shark.y = sy, shark.dir = sdir;
			map[sx][sy] = SN;

			for (int j = 1; j < 17; ++j) {
				fish[j].dir = memdir[j];
				fish[j].x = memx[j];
				fish[j].y = memy[j];
			}
			for (int k = 0; k < 4; ++k) {
				for (int j = 0; j < 4; ++j) {
					map[k][j] = memmap[k][j];
				}
			}

		}
	}
}


int main() {
	int num, dir;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			cin >> num >> dir;
			fish[num].x = i;
			fish[num].y = j;
			fish[num].dir = (dir-1);
			map[i][j] = (num);
		}
	}

	shark.x = 0; 
	shark.y = 0; 
	shark.dir = fish[map[0][0]].dir;

	num = map[0][0];
	map[0][0] = SN;
	fish[num].dir = -1;

	dfs(num);

	cout << eatmax;
}

