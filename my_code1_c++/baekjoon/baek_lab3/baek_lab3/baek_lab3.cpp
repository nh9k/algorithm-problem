#include <iostream>
#include <queue>
using namespace std;

typedef struct {
	int x, y;
}VIRUS;
VIRUS v[10];
bool visit_v[10];

int n, m, map[50][50], dx[4] = { -1,0,1,0 }, dy[4] = {0,1,0,-1}, v_idx, min_t, check_cnt;
int visit[50][50];
queue <VIRUS> v_list;

bool check_map()
{
	for (int ni = 0; ni < n; ++ni)
		for (int nj = 0; nj < n; ++nj) 
			if (map[ni][nj] == 0 && visit[ni][nj] == false) //채우지 못한곳
				return false;
	return true;
}

int spread(int limit_t)
{
	for (int vi = 0; vi < v_idx; ++vi)
	{
		if (visit_v[vi] == true) { //초기 활성 바이러스 input
			v_list.push({ v[vi].x,v[vi].y });
			//visit[v[vi].x][v[vi].y] = true;
		}
	}

	int pre_t = 0, cnt = 0;
	while (pre_t <= limit_t)
	{
		int q = v_list.size();

		if (q == 0) {		//더이상 퍼뜨릴 곳이 없음
			if (check_map()) return pre_t-1;
			else return limit_t;
		}
		else if (check_cnt == cnt) {	//cout << "빨리 리턴";  //무조건 다채울수 있는경우
			if (check_map()) { return pre_t-1; }
		}

		for(int qsz=0; qsz < q; ++qsz)
		{
			if (visit[v_list.front().x][v_list.front().y] > 0) {
				v_list.pop();
				continue;
			}
			visit[v_list.front().x][v_list.front().y] = pre_t;
			if (map[v_list.front().x][v_list.front().y] == 0) cnt++;
			for (int di = 0; di < 4; ++di)
			{
				int mx = v_list.front().x + dx[di], my = v_list.front().y + dy[di];

				if (mx < 0 || mx >= n || my < 0 || my >= n) continue; //범위 밖
				else if (map[mx][my] == 1) continue;				  //벽
				else if (visit[mx][my]) continue;					  //이미 간곳

				v_list.push({ mx,my });
				//visit[mx][my] = true;
			}
			v_list.pop();
		}
		++pre_t; //cout << endl; cout << pre_t << endl;
	}
	return limit_t;
}

void choose_list(int idx, int cnt)
{
	if (cnt == m)
	{
		int temp = spread(min_t);
		if (temp < min_t)
			min_t = temp;

		for (int ni = 0; ni < n; ++ni)
			for (int nj = 0; nj < n; ++nj) visit[ni][nj] = false;

		while (!v_list.empty())v_list.pop();

		return;
	}
	for (int i = idx; i < v_idx; ++i)
	{
		visit_v[i] = true;
		choose_list(i + 1, cnt + 1);
		visit_v[i] = false;
	}
}

int main()
{
	cin >> n >> m;
	for (int ni = 0; ni < n; ++ni)
	{
		for (int nj = 0; nj < n; ++nj)
		{
			cin >> map[ni][nj];
			if (map[ni][nj] == 2)
			{
				v[v_idx].x = ni, v[v_idx].y = nj;
				++v_idx;
			}	
			if (map[ni][nj] == 0)
				++check_cnt;
		}
	}

	min_t = 10000;
	if (check_map())  cout << 0;
	else {
		choose_list(0, 0);

		if (min_t == 10000) cout << -1;
		else cout << min_t;
	}
	return 0;
}