#include <iostream>
#include <stdlib.h>
#include <vector>
#define MAX 30000

using namespace std;

//extern int makeBlock(int module[][4][4]);

int makeBlock(int module[][4][4])
{
	bool cnt[30000] = { false, };
	int height = 0, number = 0;
	bool flag = true;
	for (int c1 = 0; c1 < 30000; c1++)
	{
		if (cnt[c1] == true) continue;
		for (int c2 = c1 + 1; c2 < 30000; c2++)
		{
			if (cnt[c2] == true) continue;
			for (int rotate = 0; rotate < 4; rotate++)
			{
				flag = true;
				for (int y = 0; y < 4; y++)
				{
					for (int x = 0; x < 4; x++)
					{
						if (rotate == 0)
						{
							if (y == 0 && x == 0)
								height = module[c1][y][x] + module[c2][y][3 - x];
							else
							{
								if (height != (module[c1][y][x] + module[c2][y][3 - x]))
								{
									flag = false; break;
								}
							}
						}
						else if (rotate == 1)
						{
							if (y == 0 && x == 0)
								height = module[c1][y][x] + module[c2][x][y];
							else
							{
								if (height != (module[c1][y][x] + module[c2][x][y]))
								{
									flag = false; break;
								}
							}
						}
						else if (rotate == 2)
						{
							if (y == 0 && x == 0)
								height = module[c1][y][x] + module[c2][3 - y][x];
							else
							{
								if (height != (module[c1][y][x] + module[c2][3 - y][x]))
								{
									flag = false; break;
								}
							}
						}
						else
						{
							if (y == 0 && x == 0)
								height = module[c1][y][x] + module[c2][3 - x][3 - y];
							else
							{
								if (height != (module[c1][y][x] + module[c2][3 - x][3 - y]))
								{
									flag = false; break;
								}
							}
						}
					}
					if (flag == false) break;
				}
				if (flag == true) break;
			}
			if (flag == true) {
				cnt[c1] = true;
				cnt[c2] = true;
				number += height;
				break;
			}
		}

	}
	return number;
}

int main(void)
{
	static int module[MAX][4][4];

	srand(3); // 3 will be changed

	for (int tc = 1; tc <= 10; tc++)
	{
		for (int c = 0; c < MAX; c++)
		{
			int base = 1 + (rand() % 6);
			for (int y = 0; y < 4; y++)
			{
				for (int x = 0; x < 4; x++)
				{
					module[c][y][x] = base + (rand() % 3);
				}
			}
		}
		cout << "#" << tc << " " << makeBlock(module) << endl;
	}

	return 0;
}