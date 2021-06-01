#include <iostream>
using namespace std;
int map[4][4];
struct fish {
	int x, y, dir;
	bool live;
}f[17];
int max_eating;
int mx[] = { 0,-1,-1,0,1,1,1,0,-1 };
int my[] = { 0,0,-1,-1,-1,0,1,1,1 };


void printmap() {
	for (int xi = 0; xi < 4; ++xi) {
		for (int yi = 0; yi < 4; ++yi) {
			cout << map[xi][yi] << " ";
		}cout << endl;
	}cout << endl;
}

int fish_room(int x, int y) { //물고기 번호 리턴
	if (map[x][y] != 0)
		return map[x][y];
	return 0;
}

bool shark_room(int x, int y) {
	if (map[x][y] == 100)
		return true;
	return false;
}

bool empty_room(int x, int y) {
	if (map[x][y] == 0)
		return true;
	return false;
}

bool out_range(int x, int y) {
	if ((x < 0 )|| (y < 0) || (x>3) || (y>3))
		return true;
	return false;
}

void fish_switch(int f1, int f2) {
	map[f[f1].x][f[f1].y] = f2;
	map[f[f2].x][f[f2].y] = f1;
	int tempx, tempy, tempd;
	tempx = f[f1].x, tempy = f[f1].y; //tempd = f[f1].dir;
	f[f1].x = f[f2].x, f[f1].y = f[f2].y; // , f[f1].dir = f[f2].dir;
	f[f2].x = tempx, f[f2].y = tempy;//, f[f2].dir = tempd;
}

void fishmoving(int fn) {
	//이동할 때까지 방향 탐색 없으면 그냥 리턴
	//방향을 인풋으로 여러 함수에 넣어주기
	int fmx, fmy;
	int fd = f[fn].dir;
	for (int i = 0; i < 8; ++i) {
		fmx = f[fn].x + mx[f[fn].dir];
		fmy = f[fn].y + my[f[fn].dir];
		if (out_range(fmx, fmy) || shark_room(fmx, fmy)) {
			f[fn].dir += 1;
			if (f[fn].dir > 8) {
				f[fn].dir = 1;
			}
		}
		else if (int switch_fn = fish_room(fmx, fmy)) {
			fish_switch(fn, switch_fn);
			return;
		}
		else { //빈방
			map[f[fn].x][f[fn].y] = 0;
			map[fmx][fmy] = fn;
			f[fn].x = fmx;
			f[fn].y = fmy;
			return;
		}
	}
	f[fn].dir = fd;
}



void dfs(int sx, int sy, int sd, int point) {
	//이 위치에 물고기 먹기 
	f[map[sx][sy]].live = 0; //물고기 죽음
	point += map[sx][sy]; // 상어 점수 ++ 
	sd = f[map[sx][sy]].dir; //상어 방향 갱신
	map[sx][sy] = 100; //상어 위치
	
	//물고기 이동 번호순 죽은애 빼고 16마리
	for (int i = 1; i < 17; ++i) {
		if (f[i].live == 0) continue;
		fishmoving(i);
	}
	printmap();
	//상어가 갈 수있는 모든곳 // 상어가 갈 수 있는 모든 곳이 없으면 max 갱신 후 집으로
	int smx = sx, smy = sy;
	while (1) {
		smx += mx[sd];
		smy += my[sd];

		if (out_range(smx, smy)) {
			if (point > max_eating)
				max_eating = point;
			return;
		}
		if (fish_room(smx, smy)) {
			map[sx][sy] = 0; //원래 위치 지우기
			fish mem_f[17];
			for (int i = 1; i < 17; ++i) {
				mem_f[i].live = f[i].live;
				mem_f[i].x = f[i].x;
				mem_f[i].y = f[i].y;
				mem_f[i].dir = f[i].dir;
			}
			dfs(smx, smy, sd, point);
			for (int xi = 0; xi < 4; ++xi) {
				for (int yi = 0; yi < 4; ++yi) {
					map[xi][yi] = 0;
				}
			}
			for (int i = 1; i < 17; ++i) {
				f[i].live = mem_f[i].live;
				f[i].x = mem_f[i].x;
				f[i].y = mem_f[i].y;
				f[i].dir = mem_f[i].dir;
				map[f[i].x][f[i].y] = i;
			}
			map[sx][sy] = 100;
		}
	}
		
}



int main() {

	int a, b, xi, yi;
	xi = 0; yi = 0;
	for (int i = 1; i < 17; ++i) {
		cin >> a >> b;
		f[a].dir = b;
		f[a].live = 1;
		f[a].x = xi;
		f[a].y = yi;
		map[xi][yi] = a;
		yi++;
		if (yi == 4) {
			yi = 0;
			xi++;
		}
	}
	//printmap();
	//[0,0] 물고기 번호의 dir 던져주기
	max_eating = 0;
	dfs(0, 0, f[map[0][0]].dir, 0);

	cout << max_eating;
	return 0;
}