//#include <string>
#include <iostream>
#include <vector>

using namespace std;
vector<vector<int>> cpy_key;
bool visit[20][20];

void rotation()
{
	vector<vector<int>> temp;
	temp.assign(cpy_key.size(), vector<int>(cpy_key.size(), 0));
	for (int i = 0; i < cpy_key.size(); ++i)
		for (int j = 0; j < cpy_key[i].size(); ++j)
			temp[i][j] = cpy_key[j][cpy_key[i].size() - i - 1];

	cpy_key.assign(temp.begin(), temp.end());
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
	
	cpy_key.assign(key.begin(), key.end());

	int n = lock.size();
	int m = key.size();
	for (int rot = 0; rot < 4; ++rot)
	{
		for (int i = -m + 1; i < n; ++i)
		{
			for (int j = -m + 1; j < n; ++j)
			{
				bool c = false;
				for (int ki = 0; ki < m; ++ki)
				{
					for (int kj = 0; kj < m; ++kj)
					{
						if (i + ki < 0 || j + kj < 0 || i + ki >= n || j + kj >= n) continue;
						if (lock[i + ki][j + kj] == cpy_key[ki][kj])
						{//¾ÈµÊ
							c = true;
							break;
						}
						visit[i + ki][j + kj] = true;
					}
					if (c) break;
				}
				if (!c)
				{
					for (int li = 0; li < n; ++li)
					{
						for (int lj = 0; lj < n; ++lj)
						{
							if (lock[li][lj] == 0 && visit[li][lj]==0)
							{//¾ÈµÊ
								c = true;
								break;
							}
						}
						if (c) break;
					}
				}
				if (!c) return true;
				for (int li = 0; li < n; ++li) {
					for (int lj = 0; lj < n; ++lj)
					{
				//		cout << visit[li][lj];
						visit[li][lj] = false;
					}//cout << endl;			
				}//cout << endl;
			}
		}
		rotation();
	}
	return false;
}

int main()
{
	cout << solution({ {0, 0, 0},{1, 0, 0},{0, 1, 1} }, { {1, 1, 1},{1, 1, 0},{1, 0, 1} });
}