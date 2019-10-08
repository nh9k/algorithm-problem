#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int n, m, k;
int honey[10][10], map[10][10];
bool isempty[10][10];
typedef struct {
	int x, y;
	deque <int> tree;
}T;
vector <T> t;

void ss() //spring and summer
{
	for (auto vsz = t.begin(); vsz != t.end();)
	{
		int die_sz = 0, qsz = (*vsz).tree.size();

		for (int ti = 0; ti < qsz; ++ti)
		{
			if (map[(*vsz).x][(*vsz).y] - (*vsz).tree[ti] < 0) {
				die_sz = qsz - ti; //죽은 나무 개수 저장 후 break
				break;
			}
			map[(*vsz).x][(*vsz).y] -= (*vsz).tree[ti]; //양분 섭취
			(*vsz).tree[ti]++; //나이 증가
		}
		for (int ti = 0; ti < die_sz; ++ti) //양분 섭취 못한 나무들 die //끝에서 부터 덱에서 빼냄
		{
			map[(*vsz).x][(*vsz).y] += (*vsz).tree.back() / 2; //여름 : 땅에 나이/2가 양분이 됨
			(*vsz).tree.pop_back();
		}

		if (die_sz == qsz) { //이 자리 모든 나무가 죽음 //clear
			isempty[(*vsz).x][(*vsz).y] = false; //벡터 지우기 전에 map에 표시 조심!!
			vsz = t.erase(vsz);
		}
		else
			vsz++;
	}
}
void fall()
{
	int tsz = t.size(); //이걸 안해주면 번식한(나이1) 나무도 다시 보게 됨. 볼필요 없음 - 시간 초과 원인1
	for (int vsz = 0; vsz < tsz; ++vsz)
	{
		for (int ti = 0; ti < t[vsz].tree.size(); ++ti)
		{
			if (t[vsz].tree[ti] % 5 == 0) //5배수
			{
				for (int ri = t[vsz].x - 1; ri <= t[vsz].x + 1; ++ri) //인접 8개 나무 심기
				{
					for (int ci = t[vsz].y - 1; ci <= t[vsz].y + 1; ++ci)
					{
						if (ri < 0 || ci < 0 || ri >= n || ci >= n) continue; //범위 밖은 나무 안 심음
						else if (ri == t[vsz].x && ci == t[vsz].y) continue; //중간 자리는 안 심음

						if (isempty[ri][ci])
						{
							for (int vsz2 = 0; vsz2 < t.size(); ++vsz2) //같은 위치 x, y 찾음
							{
								if (t[vsz2].x == ri && t[vsz2].y == ci)
								{
									t[vsz2].tree.push_front(1); //있으면 그 위치의 나무 심음
									break;
								}
							}
						}
						else
						{ //없으면 새로 심음
							int pre_idx = t.size();
							t.push_back({ ri,ci });
							t[pre_idx].tree.push_front(1);
							isempty[ri][ci] = true;
						}
					}
				}
			}
		}
	}
}
void winter()
{
	for (int ni = 0; ni < n; ++ni)
	{
		for (int nj = 0; nj < n; ++nj)
		{
			map[ni][nj] += honey[ni][nj];
		}
	}
}

int main()
{
	cin >> n >> m >> k;
	for (int ni = 0; ni < n; ++ni)
	{
		for (int nj = 0; nj < n; ++nj)
		{
			cin >> honey[ni][nj];
			map[ni][nj] = 5; 			
		}
	}

	int temp_x, temp_y, temp_old;
	for (int mi = 0; mi < m; ++mi)
	{
		cin >> temp_x >> temp_y >> temp_old;

		t.push_back({ temp_x-1, temp_y-1 }); //입력으로 주어지는 나무의 위치는 모두 다름
		t[mi].tree.push_front(temp_old);
		isempty[temp_x - 1][temp_y - 1] = true; //여기도 temp_x -1, temp_y -1 을 해줘야함!! 조심
	}
		
	for (int ki = 0; ki < k; ++ki)
	{
		ss();
		fall();
		if (t.size() == 0) {
			cout << 0;
			return 0;
		}
		winter();
	}

	int live_tree = 0;
	for (int mi = 0; mi < t.size(); ++mi)
	{
		live_tree += t[mi].tree.size();
	}
	cout << live_tree;
}