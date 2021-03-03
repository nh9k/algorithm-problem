#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct {
	int number, cnt;
}NUM;
vector <NUM> num_sort;
int r, c, k;
int map[100][100];
int N, M, time, temp, temp2;

bool cmp(NUM a, NUM b)
{
	if (a.cnt == b.cnt)
		return a.number < b.number;
	return a.cnt < b.cnt;
}

bool check_k()
{
	if (map[r - 1][c - 1] == k)
		return true;
	return false;
}

void input_array(int here, bool cond)
{//배열 삽입 후 k검사,
	int index = 0;
	temp = 0;
	if (cond)
	{
		for (int ni = 0; ni < num_sort.size(); ++ni)
		{
			map[here][index] = num_sort[ni].number;
			map[here][index + 1] = num_sort[ni].cnt;
			index += 2;
			if (index >= 100) break;
		}
		if (index > temp)
			temp = index;

	}
	else
	{
		for (int ni = 0; ni < num_sort.size(); ++ni)
		{
			map[index][here] = num_sort[ni].number;
			map[index+1][here] = num_sort[ni].cnt;
			index += 2;
			if (index >= 100) break;
		}
		if (index> temp)
			temp = index;
	}
}

void input_sort()
{
	while (1)
	{
		if (time >= 100)
		{
			time = -1;
			return;
		}
		time++;
		//cout << time << endl;
		if (N >= M)
		{
			for (int i = 0; i < N; ++i)
			{
				for (int j = 0; j < M; ++j)
				{
					if (map[i][j] == 0) continue;
					if (num_sort.size() == 0)
					{
						num_sort.push_back({ map[i][j],1 });
					}
					else
					{
						int vsz = num_sort.size();
						for (int ni = 0; ni < vsz; ++ni)
						{
							if (num_sort[ni].number == map[i][j])
							{
								num_sort[ni].cnt++;
								break;
							}
							else if (ni == vsz - 1)
							{
								num_sort.push_back({ map[i][j],1 });

							}
						}
					}
					map[i][j] = 0;
					
				}
				sort(num_sort.begin(), num_sort.end(), cmp);
				input_array(i, true);
				if (check_k()) break;
				num_sort.clear();
				if (temp2 < temp)
				{
					temp2 = temp;
				}
			}
			M = temp2;
			if (check_k()) break;
		}
		else
		{
			for (int j = 0; j < M; ++j)
			{
				for (int i = 0; i < N; ++i)
				{
					if (map[i][j] == 0) continue;
					if (num_sort.size() == 0)
					{
						num_sort.push_back({ map[i][j],1 });
					}
					else
					{
						int vsz = num_sort.size();
						for (int ni = 0; ni < vsz; ++ni)
						{
							if (num_sort[ni].number == map[i][j])
							{
								num_sort[ni].cnt++;
								break;
							}
							else if (ni == vsz - 1)
							{
								num_sort.push_back({ map[i][j],1 });
							}
						}
					}
					map[i][j] = 0;
				}
				sort(num_sort.begin(), num_sort.end(), cmp);
				input_array(j, false);
				if (check_k()) break;
				num_sort.clear();
				if (temp2 < temp)
				{
					temp2 = temp;

				}
			}
			N = temp2;
			if (check_k()) break;
		}
		temp2 = 0;

	/*for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				cout << map[i][j];
			}cout << endl;
		}cout << endl;
	*/
	}
	//for (int i = 0; i < N; ++i)
	//{
	//	for (int j = 0; j < M; ++j)
	//	{
	//		cout << map[i][j];
	//	}cout << endl;
	//}cout << endl;
}



int main()
{
	cin >> r >> c >> k;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			cin >> map[i][j];
		}
	}
	N = 3, M = 3, time = 0;

	if (check_k())
		cout << time;
	else
	{
		input_sort();
		cout << time;
	}
	return 0;
}