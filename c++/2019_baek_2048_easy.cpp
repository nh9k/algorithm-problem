#include <iostream>
#include <stack>
using namespace std;
int map[20][20], n, max_value;
stack <int> block;

void stack_block(int dir)
{
	if (dir == 0)//╩С
	{
		for (int y = 0; y < n; y++)
		{
			for (int x = n-1; x >= 0; x--)
			{
				if (map[x][y] != 0)
				{
					block.push(map[x][y]);
					map[x][y] = 0;
				}
			}
			int x = 0;
			while (!block.empty())
			{
				int temp = block.top();
				block.pop();
				if (!block.empty())
				{
					if (block.top() == temp)
					{
						map[x][y] = temp * 2;
						block.pop();
					}
					else
					{
						map[x][y] = temp;
					}
				}
				else
				{
					map[x][y] = temp;
				}
				x++;
			}
		}
	}
	else if (dir == 1)//го
	{
		for (int y = 0; y < n; y++)
		{
			for (int x = 0; x < n; x++)
			{
				if (map[x][y] != 0) {
					block.push(map[x][y]);
					map[x][y] = 0;
				}
			}
			int x = n-1;
			while (!block.empty())
			{
				int temp = block.top();
				block.pop();
				if (!block.empty())
				{
					if (block.top() == temp)
					{
						map[x][y] = temp * 2;
						block.pop();
					}
					else
					{
						map[x][y] = temp;
					}
				}
				else
				{
					map[x][y] = temp;
				}
				x--;
			}
		}
	}
	else if (dir == 2)//аб
	{
		for (int x = 0; x < n; x++)
		{
			for (int y = n-1; y >= 0; y--)
			{
				if (map[x][y] != 0) {
					block.push(map[x][y]);
					map[x][y] = 0;
				}
			}
			int y = 0;
			while (!block.empty())
			{
				int temp = block.top();
				block.pop();
				if (!block.empty())
				{
					if (block.top() == temp)
					{
						map[x][y] = temp * 2;
						block.pop();
					}
					else
					{
						map[x][y] = temp;
					}
				}
				else
				{
					map[x][y] = temp;
				}
				y++;
			}
		}
	}
	else if (dir == 3)//©Л
	{
		for (int x = 0; x < n; x++)
		{
			for (int y = 0; y <n; y++)
			{
				if (map[x][y] != 0) {
					block.push(map[x][y]);
					map[x][y] = 0;
				}
			}
			int y = n-1;
			while (!block.empty())
			{
				int temp = block.top();
				block.pop();
				if (!block.empty())
				{
					if (block.top() == temp)
					{
						map[x][y] = temp * 2;
						block.pop();
					}
					else
					{
						map[x][y] = temp;
					}
				}
				else
				{
					map[x][y] = temp;
				}
				y--;
			}
		}
	}
}

void dfs(int cnt)
{
	if (cnt == 5)
	{
		for (int x = 0; x < n; x++)
		{
			for (int y = 0; y < n; y++)
			{
				//cout << map[x][y];
				if (max_value < map[x][y])
					max_value = map[x][y];
			}//cout << endl;
		}//cout << endl;
		return;
	}
	for (int dir = 0; dir < 4; dir++)
	{
		int cpymap[20][20];
		for (int x = 0; x < n; x++)
			for (int y = 0; y < n; y++)
					cpymap[x][y] = map[x][y];

		stack_block(dir);
		dfs(cnt + 1);

		for (int x = 0; x < n; x++)
			for (int y = 0; y < n; y++)
				map[x][y] = cpymap[x][y];
	}
}

int main()
{
	cin >> n;
	for (int x = 0; x < n; x++)
		for (int y = 0; y < n; y++)
			cin >> map[x][y];

	max_value = 0;
	dfs(0);
	cout << max_value;
	return 0;
}