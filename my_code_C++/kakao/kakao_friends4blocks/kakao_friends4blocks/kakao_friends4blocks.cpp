#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
using namespace std;


int solution(int m, int n, vector<string> board) {
	queue <pair<int, int>> erase_list;
	stack <char> arrange_block;
	int erase_num = 0; //나중에 제거할 때 ++하기 //초기화 해주기: 조심!
	bool endflag = false;

	while (!endflag)
	{
		for (int i = 0; i < m - 1; i++) //탐색하며 제거할 블록의 리스트를 넣는 곳
		{
			for (int j = 0; j < n - 1; j++)
			{
				//cout << board[i][j];
				if (board[i][j] == board[i][j + 1] && board[i][j] == board[i + 1][j]
					&& board[i][j] == board[i + 1][j + 1] && board[i][j]!=0)
					erase_list.push({ i,j });
			}
		}
		//모두 탐색 종료

		int qsz = erase_list.size();
		if (qsz == 0) { //제거할 블록이 없으면 while문을 종료함
			endflag = true;
			continue;
		}
		while (!erase_list.empty()) //블록 제거와 제거한 블록 개수++
		{
			int x = erase_list.front().first;
			int y = erase_list.front().second;
			erase_list.pop();
			if (board[x][y] != 0) //이미 지워진 블록1이 아니면
			{
				board[x][y] = 0;
				erase_num++;
			}
			if (board[x][y + 1] != 0) //이미 지워진 블록2이 아니면
			{
				board[x][y + 1] = 0;
				erase_num++;
			}
			if (board[x + 1][y] != 0) //이미 지워진 블록3이 아니면
			{
				board[x + 1][y] = 0;
				erase_num++;
			}
			if (board[x + 1][y + 1] != 0) //이미 지워진 블록4이 아니면
			{
				board[x + 1][y + 1] = 0;
				erase_num++;
			}
		}

		
		for (int j = 0; j < n; j++) //세로줄을 읽으며 stack에 넣고 블록을 정리하는 부분
		{
			for (int i = 0; i < m - 2; i++)
			{
				if (board[i][j] != 0)
				{
					arrange_block.push(board[i][j]);
					board[i][j] = 0;
				}
			}
			for (int i = m-1; i >= 0; i--) //m-1이 마지막 인덱스: 조심!
			{
				if (arrange_block.empty()) break;
				if (board[i][j] == 0)
				{
					board[i][j] = arrange_block.top();
					arrange_block.pop(); //pop안해주면 무한루프, 조심!
				}
					
			}
		}
	}

	//int answer = 0;
	return erase_num;
}
int main()
{
	cout << solution(4, 5, { "CCBDE", "AAADE", "AAABF", "CCBBF" }) << endl;
	return 0;
}