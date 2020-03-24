//#include <string>
#include <vector>
#include <iostream>
using namespace std;
int n, min_t, dx[4] = { -1,0,1,0 }, dy[4] = { 0,1,0,-1 };
int rot_x1[4][4] = { {0,0,-1,1},{0,0,1,-1},{0,0,-1,-1},{0,0,1,1} },
rot_y1[4][4] = { {0,0,1,1},{0,0,-1,-1},{0,0,-1,1},{0,0,1,-1} },
rot_x2[4][4] = { {1,-1,0,0},{-1,1,0,0},{1,1,0,0},{-1,-1,0,0} },
rot_y2[4][4] = { {-1,-1,0,0},{1,1,0,0},{1,-1,0,0},{-1,1,0,0} },
rot_num[4][4] = { {3,2,3,2},{2,3,2,3},{0,1,0,1},{1,0,1,0} },
rot_chk_x[4][4] = { {1,-1,-1,1},{-1,1,1,-1},{-1,-1,0,0},{1,1,0,0} },
rot_chk_y[4][4] = { {1,1,0,0},{-1,-1,0,0},{1,-1,-1,1},{-1,1,1,-1} };
//no_go[8] = {2,3,0,1,5,4,7,6};
int visit[100][100];
vector<vector<int>> cpy_board;

void dfs(int x1, int y1, int t_cnt, int rot)
{
	//cout << rot << "   " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
	int x2, y2;
	if (rot == 0) { x2 = x1;  y2 = y1 + 1; }
	else if(rot==1) { x2 = x1;  y2 = y1 - 1; }
	else if(rot==2) { y2 = y1;  x2 = x1 - 1; }
	else if(rot==3) { y2 = y1;  x2 = x1 + 1; }

	if (min_t < t_cnt) return;
	if ((x1 == n - 1 && y1 == n - 1) || (x2 == n - 1 && y2 == n - 1))
	{
		//cout << t_cnt << endl;
		if (min_t > t_cnt)
			min_t = t_cnt;
		return;
	}
	for (int i = 0; i < 8; ++i)
	{
		//if (no_go[idx]==i) continue;

		if (i < 4)
		{
			int mx1 = x1 + dx[i], my1 = y1 + dy[i],
				mx2 = x2 + dx[i], my2 = y2 + dy[i];
			if (mx1 < 0 || my1 < 0 || mx2 < 0 || my2 < 0 || mx1 >= n || my1 >= n || mx2 >= n || my2 >= n) continue;
			else if (cpy_board[mx1][my1] == 1 || cpy_board[mx2][my2] == 1) continue;
			else if (visit[mx1][my1] && visit[mx2][my2]) continue;

			visit[mx1][my1]++, visit[mx2][my2]++;
			dfs(mx1, my1, t_cnt + 1, rot);
			visit[mx1][my1]--, visit[mx2][my2]--;
		}
		else
		{
			int mx1 = x1 + rot_x1[rot][i - 4], my1 = y1 + rot_y1[rot][i - 4],
				mx2 = x2 + rot_x2[rot][i - 4], my2 = y2 + rot_y2[rot][i - 4];
			if (mx1 < 0 || my1 < 0 || mx2 < 0 || my2 < 0 || mx1 >= n || my1 >= n || mx2 >= n || my2 >= n) continue;
			else if (cpy_board[mx1][my1] == 1 || cpy_board[mx2][my2] == 1 
				|| cpy_board[x1 + rot_chk_x[rot][i - 4]][y1 + rot_chk_y[rot][i - 4]]==1) continue;
			else if (visit[mx1][my1] && visit[mx2][my2]) continue;

			visit[mx1][my1]++, visit[mx2][my2]++;
			dfs(mx1, my1, t_cnt + 1, rot_num[rot][i - 4]);
			visit[mx1][my1]--, visit[mx2][my2]--;
		}
	}
}

int solution(vector<vector<int>> board) {
	n = board.size();
	cpy_board.assign(board.begin(), board.end());
	min_t = 100000;
	visit[0][0] = true; visit[0][1] = true;
	dfs(0, 0, 0, 0);
	return min_t;
}

int main()
{
	cout << solution({ {0, 0, 0, 1, 1},{0, 0, 0, 1, 0},{0, 1, 0, 1, 1},{1, 1, 0, 0, 1},{0, 0, 0, 0, 0} });
}