#include <iostream>
#include <vector>
using namespace std;

int r, c, dr[4] = { -1,1,0,0 }, dc[4] = { 0,0,1,-1 }, cross[4] = {1,0,3,2}, map[101][101];
typedef struct {
	int r, c, s, d, z;
	bool live;
}SHARK;
vector <SHARK> s;
typedef struct {
	int c, sum_z;
}PERSON;
PERSON p;

void fishing()
{
	while (p.c <= c)
	{
		//낚시왕 낚시
		int min_r = r, min_idx = -1;
		for (int m = 0; m < s.size(); ++m)
		{
			if (s[m].c == p.c && s[m].r <= min_r)
			{
				min_idx = m;
				min_r = s[m].r;
			}
		}
		if (min_idx != -1)
		{
			s[min_idx].live = false;
			p.sum_z += s[min_idx].z;
		}

		//상어 이동
		for (int m = 0; m < s.size(); ++m)
		{
			if (s[m].live == false) continue;

			for (int dir = 0; dir < s[m].s; ++dir) //이동
			{
				if ((s[m].r == 1 && s[m].d ==0)
					|| (s[m].c == 1 && s[m].d == 3) 
					|| (s[m].r == r && s[m].d == 1) 
					|| (s[m].c == c && s[m].d == 2) )
				{
					s[m].d = cross[s[m].d];
				}
				s[m].r += dr[s[m].d], s[m].c += dc[s[m].d];
			}

			if (map[s[m].r][s[m].c]) //이미 상어 있다
			{
				if (s[map[s[m].r][s[m].c]-1].z < s[m].z)
				{
					s[map[s[m].r][s[m].c]-1].live = false;
					map[s[m].r][s[m].c] = m + 1;
				}
				else
				{
					s[m].live = false;
				}
			}
			else //없으면 인덱스
				map[s[m].r][s[m].c] = m + 1;
		}

		//상어 죽인 애 erase
		for (auto m = s.begin(); m != s.end();)
		{
			if ((*m).live == false) {
				m = s.erase(m);
			}
			else
			{
				//cout << (*m).r << " "<< (*m).c << endl;
				map[(*m).r][(*m).c] = 0;
				++m;
			}

		}//cout << endl;

		p.c++;
	}
}

int main()
{
	int m;
	cin >> r >> c >> m;
	if (m == 0) cout << 0;
	else
	{
		int temp_r, temp_c, temp_s, temp_d, temp_z;
		for (int mi = 0; mi < m; ++mi)
		{
			cin >> temp_r >> temp_c >> temp_s >> temp_d >> temp_z;
			if ((temp_d == 1 || temp_d == 2))
			{
				temp_s %= ((r * 2) - 2);
			}
			else
			{
				temp_s %= ((c * 2) - 2);
			}
			s.push_back({ temp_r, temp_c, temp_s, temp_d - 1, temp_z });
			s[mi].live = true;
		}
		p.c = 1;
		fishing();
		cout << p.sum_z;
	}
	
	return 0;
}