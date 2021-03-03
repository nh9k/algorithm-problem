#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
using namespace std;


int solution(int m, int n, vector<string> board) {
	queue <pair<int, int>> erase_list;
	stack <char> arrange_block;
	int erase_num = 0; //���߿� ������ �� ++�ϱ� //�ʱ�ȭ ���ֱ�: ����!
	bool endflag = false;

	while (!endflag)
	{
		for (int i = 0; i < m - 1; i++) //Ž���ϸ� ������ ����� ����Ʈ�� �ִ� ��
		{
			for (int j = 0; j < n - 1; j++)
			{
				//cout << board[i][j];
				if (board[i][j] == board[i][j + 1] && board[i][j] == board[i + 1][j]
					&& board[i][j] == board[i + 1][j + 1] && board[i][j]!=0)
					erase_list.push({ i,j });
			}
		}
		//��� Ž�� ����

		int qsz = erase_list.size();
		if (qsz == 0) { //������ ����� ������ while���� ������
			endflag = true;
			continue;
		}
		while (!erase_list.empty()) //��� ���ſ� ������ ��� ����++
		{
			int x = erase_list.front().first;
			int y = erase_list.front().second;
			erase_list.pop();
			if (board[x][y] != 0) //�̹� ������ ���1�� �ƴϸ�
			{
				board[x][y] = 0;
				erase_num++;
			}
			if (board[x][y + 1] != 0) //�̹� ������ ���2�� �ƴϸ�
			{
				board[x][y + 1] = 0;
				erase_num++;
			}
			if (board[x + 1][y] != 0) //�̹� ������ ���3�� �ƴϸ�
			{
				board[x + 1][y] = 0;
				erase_num++;
			}
			if (board[x + 1][y + 1] != 0) //�̹� ������ ���4�� �ƴϸ�
			{
				board[x + 1][y + 1] = 0;
				erase_num++;
			}
		}

		
		for (int j = 0; j < n; j++) //�������� ������ stack�� �ְ� ����� �����ϴ� �κ�
		{
			for (int i = 0; i < m - 2; i++)
			{
				if (board[i][j] != 0)
				{
					arrange_block.push(board[i][j]);
					board[i][j] = 0;
				}
			}
			for (int i = m-1; i >= 0; i--) //m-1�� ������ �ε���: ����!
			{
				if (arrange_block.empty()) break;
				if (board[i][j] == 0)
				{
					board[i][j] = arrange_block.top();
					arrange_block.pop(); //pop�����ָ� ���ѷ���, ����!
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