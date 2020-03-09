#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int r, c, k, arr[100][100], max_r, max_c;
vector <pair<int, int>> numbering; //first: 등장횟수, second: 수

bool cmp(pair<int, int> a, pair<int, int> b)
{
	if (a.first == b.first)
		return a.second < b.second;
	return a.first < b.first;
}

int simulation()
{
	int t = 0;
	while (t <= 100)
	{
		//for (int ni = 0; ni < max_r; ++ni)
		//{
		//	for (int nj = 0; nj < max_c; ++nj)
		//	{
		//		cout << arr[ni][nj];
		//	}cout << endl;
		//}cout << endl;
		if (arr[r][c] == k) return t;

		int temp_cal = 0;
		if (max_r >= max_c) //r행 연산
		{
			for (int ni = 0; ni < max_r; ++ni)
			{
				for (int nj = 0; nj < max_c; ++nj)
				{
					if (arr[ni][nj] == 0) continue;
					if (numbering.empty())
						numbering.push_back({ 1,arr[ni][nj] });
					else
					{
						bool insert_ = false;
						for (int i = 0; i < numbering.size(); ++i)
						{
							if (numbering[i].second == arr[ni][nj])
							{
								numbering[i].first++;
								insert_ = true;
								break;
							}
						}
						if (!insert_)
						{
							numbering.push_back({ 1,arr[ni][nj] });
						}
					}
					arr[ni][nj] = 0;
				}

				sort(numbering.begin(), numbering.end(), cmp);

				int idx = 0;
				for (int nj = 0; nj < numbering.size(); ++nj)
				{
					arr[ni][idx] = numbering[nj].second; idx++;
					arr[ni][idx] = numbering[nj].first; idx++;
					if (idx >= 100) break;
				}
				if (idx > temp_cal)
				{
					temp_cal = idx;
				}

				numbering.clear();
			}
			max_c = temp_cal;
		}
		else //c열 연산
		{
			for (int nj = 0; nj < max_c; ++nj)
			{
				for (int ni = 0; ni < max_r; ++ni)
				{
					if (arr[ni][nj] == 0) continue;
					if (numbering.empty())
						numbering.push_back({ 1,arr[ni][nj] });
					else
					{
						bool insert_ = false;
						for (int i = 0; i < numbering.size(); ++i)
						{
							if (numbering[i].second == arr[ni][nj])
							{
								numbering[i].first++;
								insert_ = true;
								break;
							}
						}
						if (!insert_)
						{
							numbering.push_back({ 1,arr[ni][nj] });
						}
					}
					arr[ni][nj] = 0;
				}

				sort(numbering.begin(), numbering.end(), cmp);

				int idx = 0;
				for (int ni = 0; ni < numbering.size(); ++ni)
				{
					arr[idx][nj] = numbering[ni].second; idx++;
					arr[idx][nj] = numbering[ni].first; idx++;
					if (idx >= 100) break;
				}
				if (idx > temp_cal)
				{
					temp_cal = idx;
				}

				numbering.clear();
			}
			max_r = temp_cal;
		}

		++t;
	}
	return -1;
}

int main()
{
	cin >> r >> c >> k;
	r -= 1, c -= 1;
	for (int ni = 0; ni < 3; ++ni)
	{
		for (int nj = 0; nj < 3; ++nj)
		{
			cin >> arr[ni][nj];
		}
	}
	max_r = 3, max_c = 3;
	cout << simulation();
}
