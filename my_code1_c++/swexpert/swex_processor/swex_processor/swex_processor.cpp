#include <iostream>

int n, map[12][12], cn, maxcore, minleng, chkcore, chkleng;
typedef struct pos
{
	int x, y, minimum[4];
	bool dir[4], no; //상우하좌, 가장자리 프로세서
}pos;
pos core[12];

void fcheckdir()
{
	for (int i = 0; i < cn; i++)
	{
		//상우하좌 순으로 거리 계산해서 우선적으로 체크할 방향 minimum[4]에 순서대로 넣어주기
		int calx = core[i].x;
		int caly = core[i].y;
		
		if (calx >= n / 2) calx = n - 1 - calx;
		if (caly >= n / 2) caly = n - 1 - caly;

		if (calx <= caly) //더 작은 값이 가장자리로 부터 거리가 더 가까움
		{ //x가 더 작은 경우
			if (core[i].x >= n / 2)
			{//[먼저탐색]=방향
				core[i].minimum[0] = 2;
				core[i].minimum[3] = 0;
			}
			else
			{
				core[i].minimum[0] = 0;
				core[i].minimum[3] = 2;
			}
			if (core[i].y >= n / 2)
			{
				core[i].minimum[1] = 1;
				core[i].minimum[2] = 3;
			}
			else
			{
				core[i].minimum[1] = 3;
				core[i].minimum[2] = 1;
			}
		}
		else { //y가 더 작은 경우
			if (core[i].x >= n / 2)
			{//[먼저탐색]=방향
				core[i].minimum[1] = 2;
				core[i].minimum[2] = 0;
			}
			else
			{
				core[i].minimum[1] = 0;
				core[i].minimum[2] = 2;
			}
			if (core[i].y >= n / 2)
			{
				core[i].minimum[0] = 1;
				core[i].minimum[3] = 3;
			}
			else
			{
				core[i].minimum[0] = 3;
				core[i].minimum[3] = 1;
			}
		}

		for (int j = 0; j < cn; j++)
		{
			if (core[i].x == 0 || core[i].x == n - 1 || core[i].y == 0 || core[i].y == n - 1) 
			{//가장자리에 있는 경우
				core[i].no = true;
				break;
			}	
			if (i == j) continue; //같은 코어는 계산하면 안됨
			else 
			{
				if (core[i].y == core[j].y) //같은 세로줄에 있는 경우
				{
					if (core[i].x > core[j].x) core[i].dir[0] = false; //상 방향 불가
					else core[i].dir[2] = false; //하 방향 불가
				}
				else if (core[i].x == core[j].x) //같은 가로줄에 있는 경우
				{
					if (core[i].y > core[j].y) core[i].dir[3] = false; //좌 방향 불가
					else core[i].dir[1] = false; //우 방향 불가
				}
			}
		}
	}
	for (int i = 0; i < cn; i++)
	{
		if (core[i].dir[0] == false && core[i].dir[1] == false && core[i].dir[2] == false && core[i].dir[3] == false)
		{//모든 방향이 다른 코어로 막힌 경우
			core[i].no = true;
		}
	}
}

int chkvisit(int whatcore, int idx)//0: 갈 수 없는 곳, 1: 갈 수 있는 곳, 2: 체크할 필요가 없는 코어
{    
	idx = core[whatcore].minimum[idx];
	if (core[whatcore].no) return 2; //체크할 필요가 없는 코어이면
	if (!core[whatcore].dir[idx]) return 0; //다른 코어로 인해 못가는 지역이면

	if (idx == 0) {//상방향 체크 + 길이 체크
		for (int x = core[whatcore].x - 1; x >= 0; x--)
		{
			if (map[x][core[whatcore].y] == 0){ //아무것도 없는 길
				map[x][core[whatcore].y] = whatcore; 
				chkleng++;
			}
			else if (map[x][core[whatcore].y] == whatcore) { //자기가 이미 왔다 간 길
				map[x][core[whatcore].y] = 0; 
				chkleng--;
			}
			else { //이미 다른 코어가 온길
				for (int xr = x + 1; xr < core[whatcore].x; xr++) { //다시 되돌려 놓기
					map[xr][core[whatcore].y] = 0; chkleng--;
				}
				return 0; //0반환
			}
		}
	}
	else if (idx == 1) { //우방향 체크 + 길이 체크
		for (int y = core[whatcore].y + 1; y <= n-1; y++)
		{
			if (map[core[whatcore].x][y] == 0) {
				map[core[whatcore].x][y] = whatcore; //아무것도 없는 길
				chkleng++;
			}
			else if (map[core[whatcore].x][y] == whatcore) {
				map[core[whatcore].x][y] = 0; //자기가 이미 왔다 간 길
				chkleng--;
			}
			else { //이미 다른 코어가 온길
				for (int yr = y - 1; yr > core[whatcore].y; yr--) { //다시 되돌려 놓기
					map[core[whatcore].x][yr] = 0; chkleng--;
				}
				return 0; //0반환
			}
		}
	}
	else if (idx == 2) { //하 방향 체크
		for (int x = core[whatcore].x + 1; x <=n-1 ; x++)
		{
			if (map[x][core[whatcore].y] == 0) { //아무것도 없는 길
				map[x][core[whatcore].y] = whatcore; 
				chkleng++;
			}
			else if (map[x][core[whatcore].y] == whatcore) { //자기가 이미 왔다 간 길
				map[x][core[whatcore].y] = 0; 
				chkleng--;
			}
			else { //이미 다른 코어가 온길
				for (int xr = x - 1; xr > core[whatcore].x; x--) { //다시 되돌려 놓기
					map[xr][core[whatcore].y] = 0; chkleng--;
				}
				return 0;//0반환
			}
		}
	}
	else { //좌 방향 체크
		for (int y = core[whatcore].y - 1; y >= 0; y--)
		{
			if (map[core[whatcore].x][y] == 0) { //아무것도 없는 길
				map[core[whatcore].x][y] = whatcore; 
				chkleng++;
			}
			else if (map[core[whatcore].x][y] == whatcore) { //자기가 이미 왔다 간 길
				map[core[whatcore].x][y] = 0; 
				chkleng--;
			}
			else { //이미 다른 코어가 온길
				for (int yr = y + 1; yr < core[whatcore].y; yr++) { //다시 되돌려 놓기
					map[core[whatcore].x][yr] = 0; chkleng--;
				}
				return 0;//0반환
			}
		}
	}
	return 1;//1반환
}

void dfs(int cnt)
{
	if (cnt >= cn)
	{
		if (maxcore <= chkcore)
		{
			maxcore = chkcore;
			if (minleng > chkleng)
				minleng = chkleng;			
		}
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		int chk = chkvisit(cnt, i);
		if(chk!=2 &&chk!=1) continue; //0반환한 경우  //이미 다른 코어가 온길이거나 다른 코어로 막힌경우
		chkcore++;
		dfs(cnt + 1); //각 코어에 들어가서 4방향에 대해서 dfs 시행 후를 어떻게 할 것 인가
		chkvisit(cnt, i); chkcore--;
	}
}
int main()
{
	freopen("sample_input.txt", "r", stdin);
	int t;
	scanf("%d", &t);
	for (int tc = 0; tc < t; tc++)
	{
		scanf("%d", &n);
		cn = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				scanf("%d", &map[i][j]);
				if (map[i][j])
				{
					core[cn].x = i;  core[cn].y = j;
					cn++;
				}
			}
		}
		for (int i = 0; i < cn; i++)
		{
			core[i].dir[0] = true; core[i].dir[1] = true; core[i].dir[2] = true; core[i].dir[3] = true;
			core[i].no = false;
		}
		fcheckdir(); //처음으로 상우하좌 방향에 대해서 갈 수 있는지 체크해줌
		maxcore = 0, minleng = 144, chkcore = 0, chkleng = 0;
		dfs(0);

		printf("#%d %d\n", tc + 1, minleng);
	}
	return 0;
}