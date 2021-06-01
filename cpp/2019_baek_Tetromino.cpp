#include <iostream>
#include <vector>
using namespace std;
int n, m;
vector <vector<int>> map;
int tx[5][4] = { {0,0,0,0},{0,0,1,1},{0,1,2,2},{0,1,1,2},{0,0,0,1}};
int ty[5][4] = { {0,1,2,3},{0,1,0,1},{0,0,0,1},{0,0,1,1},{0,1,2,1}};
int gatex[5] = { 1,2,3,3,2 }, gatey[5] = { 4,2,2,2,3 };

void rotation()
{
	vector <vector<int>> temp;
	temp.assign(m, vector<int>(n, 0));

	for (int ni = 0; ni < n; ++ni)
	{
		for (int mi = 0; mi < m; ++mi)
		{
			temp[mi][n-ni-1] = map[ni][mi];
		}
	}

	int tmp = n;
	n = m;
	m = tmp;
	map.assign(temp.begin(), temp.end());
}

void mirroring()
{
	vector <vector<int>> temp;
	temp.assign(n, vector<int>(m, 0));

	for (int ni = 0; ni < n; ++ni)
	{
		for (int mi = 0; mi < m; ++mi)
		{
			temp[ni][m-mi-1] = map[ni][mi];
		}
	}
	map.assign(temp.begin(), temp.end());
}

int search_map()
{
	int max_sum = 0;
	for (int rot = 0; rot< 4; ++rot)
	{	
		vector <vector<int>> temp1;
		temp1.assign(map.begin(), map.end());
		for (int mir = 0; mir < 2; ++mir)
		{
			//for (int ni = 0; ni < n; ++ni)
			//{
			//	for (int mi = 0; mi < m; ++mi)
			//	{
			//		cout << map[ni][mi];
			//	}cout << endl;
			//}cout << endl;
			for (int idx = 0; idx < 5; ++idx)
			{
				for (int x = 0; x <= n - gatex[idx]; ++x)
				{
					for (int y = 0; y <= m - gatey[idx]; ++y)
					{
						if (max_sum < map[x + tx[idx][0]][y + ty[idx][0]] + map[x + tx[idx][1]][y + ty[idx][1]]
							+ map[x + tx[idx][2]][y + ty[idx][2]] + map[x + tx[idx][3]][y + ty[idx][3]])
						{
							max_sum = map[x + tx[idx][0]][y + ty[idx][0]] + map[x + tx[idx][1]][y + ty[idx][1]]
								+ map[x + tx[idx][2]][y + ty[idx][2]] + map[x + tx[idx][3]][y + ty[idx][3]];
						}
					}
				}
			}
			mirroring();
		}
		map.assign(temp1.begin(), temp1.end());
		rotation();
	}

	return max_sum;
}

int main()
{
	cin >> n >> m;
	map.assign(n, vector<int>(m, 0));
	for (int ni = 0; ni < n; ++ni)
	{
		for (int mi = 0; mi < m; ++mi)
		{
			cin >> map[ni][mi];
		}
	}

	cout << search_map();
}