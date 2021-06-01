#include <string>
#include <vector>
#include <iostream>
using namespace std;
typedef struct {
	int x[4], y[4], idx, shape; //원하는 모양이 없으면 0넣기
}block;
block b[201];
int cpyboard[50][50];
int n;
int bx[5][3] = { {1,1,1},{1,2,2},{1,2,2},{1,1,1} ,{1,1,1} }; //shape와 index
int by[5][3] = { {0,1,2},{0,-1,0},{0,0,1},{-2,-1,0},{-1,0,1} };
int blank[5][2] = { {2,3},  {2,0}, {3,0}, {1,2}, {1,3} }; //shape와 index

void check_shape()
{
	for (int ni = 1; ni <= n; ni++)
	{
		for (int shape5 = 0; shape5 < 5; shape5++)
		{
			bool pass = true;
			for (int three = 0; three < 3; three++)
			{
				if (!((b[ni].x[0] + bx[shape5][three] == b[ni].x[three+1])
					&& (b[ni].y[0] + by[shape5][three] == b[ni].y[three + 1])))
				{
					pass = false;
					break;
				}
			}
			if (pass) {
				b[ni].shape = shape5 + 1;
				break;
			}
		}
	}
	return;
}

int remove_block()
{
	int cnt_result = 0;
	int mem = 100;
	while (cnt_result != mem)
	{
		mem = cnt_result;

		for (int ni = 1; ni <= n; ni++)
		{
			if (!b[ni].shape) continue;

			bool no = false;
			for (int cnt = 0; cnt < 2; cnt++)
			{
				if (!blank[b[ni].shape - 1][cnt]) continue;
				int y = b[ni].y[0] + by[b[ni].shape - 1][blank[b[ni].shape - 1][cnt]-1];
				for (int x = b[ni].x[0] + bx[b[ni].shape - 1][blank[b[ni].shape - 1][cnt]-1] - 1; x >= 0; x--)
				{
					if (cpyboard[x][y] != 0)
					{
						no = true;
						break;
					}					
				}
				if (no) break;
			}
			if (!no) {
				cpyboard[b[ni].x[0]][b[ni].y[0]] = 0, cpyboard[b[ni].x[1]][b[ni].y[1]] = 0,
					cpyboard[b[ni].x[2]][b[ni].y[2]] = 0, cpyboard[b[ni].x[3]][b[ni].y[3]] = 0;
				cnt_result++;
				b[ni].shape = 0;
			}
		}
	}
	return cnt_result;
}

int solution(vector<vector<int>> board) {
	n = 0;
	for (int x = 0; x < board.size(); x++)
	{
		for (int y = 0; y < board[x].size(); y++)
		{
			cpyboard[x][y] = board[x][y];
			if (board[x][y] != 0)
			{
				b[board[x][y]].x[b[board[x][y]].idx] = x;
				b[board[x][y]].y[b[board[x][y]].idx] = y;
				b[board[x][y]].idx++;
				if (n < board[x][y]) n = board[x][y]; //전체 블록 개수 파악
			}
		}
	}
	check_shape();
	return remove_block();
}
int main()
{
	cout << solution({ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
		,{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},{0, 0, 0, 0, 0, 0, 4, 0, 0, 0},{0, 0, 0, 0, 0, 4, 4, 0, 0, 0},{0, 0, 0, 0, 3, 0, 4, 0, 0, 0}
		,{0, 0, 0, 2, 3, 0, 0, 0, 5, 5},{1, 2, 2, 2, 3, 3, 0, 0, 0, 5},{1, 1, 1, 0, 0, 0, 0, 0, 0, 5} });
	return 0;
}