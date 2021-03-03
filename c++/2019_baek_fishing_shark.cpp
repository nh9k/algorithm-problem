#include <iostream>
#include <vector>
using namespace std;

typedef struct {
	int r, c, s, d, z;
}SHARK;
vector <SHARK> s;
int R, C, mx[5] = { 0,-1,1,0,0 }, my[5] = { 0,0,0,1,-1 }, map[102][102];

//bool cmp(SHARK a, SHARK b)
//{
//	return a.s > b.s;
//}

void move_shark()
{
	for (int v = 0; v < s.size(); ++v)
	{
		if (s[v].z == 0) continue; //사람이 잡아서 죽은 상어는 넘어감

		if (s[v].d == 1 || s[v].d == 2)
		{
			for (int m = 0; m < s[v].s; ++m)
			{
				//cout << v << "	상어 이동 x	" << s[v].r << "	상어 이동 y	" << s[v].c << endl;
				if (s[v].r == 1 && s[v].d == 1) s[v].d = 2;
				else if (s[v].r == R && s[v].d == 2) s[v].d = 1;
				s[v].r += mx[s[v].d];
			}
		}
		else
		{
			for (int m = 0; m < s[v].s; ++m)
			{
				//cout << v << "	상어 이동 x	" << s[v].r << "	상어 이동 y	" << s[v].c << endl;
				if (s[v].c == 1 && s[v].d == 4) s[v].d = 3;
				else if (s[v].c == C && s[v].d == 3) s[v].d = 4;
				s[v].c += my[s[v].d];
			}
		}

		//같은 곳에 상어가 있는지 조사(이동을 마친 상어끼리만 있는지 검사)
		//cout << map[s[v].r][s[v].c] - 1 << endl;
		if (map[s[v].r][s[v].c] != 0)
		{
			if (s[map[s[v].r][s[v].c] - 1].z < s[v].z)
			{
				s[map[s[v].r][s[v].c] - 1].z = 0; //원래 있던 상어 잡아먹힘
				map[s[v].r][s[v].c] = (v + 1); //새로온 상어로 채움
			}
			else
			{
				s[v].z = 0; //새로온 상어 잡아먹힘
			}
		}
		else //아무도 없으면
			map[s[v].r][s[v].c] += v+1;
	}
}

void eat_shark() //죽은 상어(사람에게 잡히거나 먹히거나) 모두 지우기
{
	for (auto v = s.begin(); v != s.end();)
	{
		if ((*v).z == 0)
		{
			//죽은 상어
			//cout << (*v).s << endl;
			v = s.erase(v);
		}
		else
			++v;
	}
	//for (int v1 = 0; v1 < s.size(); ++v1)
	//{
	//	for (int v2 = 0; v2 < s.size();)
	//	{
	//		if (v1 == v2) {
	//			++v2;
	//			continue;
	//		}
	//		if (s[v1].r == s[v2].r && s[v1].c == s[v2].c)
	//		{
	//			if (s[v1].z < s[v2].z)
	//			{
	//				s[v1].d = s[v2].d;
	//				s[v1].s = s[v2].s;
	//				s[v1].z = s[v2].z;
	//			}
	//			s.erase(s.begin() + v2);
	//		}
	//		else
	//		{
	//			++v2;
	//		}
	//	}
	//}
}

int timeloop()
{
	int person = 1;
	int person_get = 0;

	while (person < C + 1)
	{
		for (int i = 1; i <= R; i++) //죽은 상어를 지운 이후에 
		{	//상어 벡터의 index가 바뀌므로 아에 map에서 지워버리고 move_shark에서만 인덱스를 적용하여 이동마친 상어만 검사
			for (int j = 1; j <= C; j++) {
				//cout << map[i][j];
				map[i][j] = 0;
			}
			//cout << endl;
		}//cout << endl;

		//***************************상어 잡기
		int vsz = s.size();
		int temp_v = 0, shortest_length = 101;
		for (int v = 0; v < vsz; ++v) //땅과 가까운 상어 탐색
		{
			//cout << v << "	상어 이동	" << s[v].r << " " << s[v].c << endl;
			if (s[v].c == person)
			{
				if (shortest_length > s[v].r)
				{
					shortest_length = s[v].r;
					temp_v = v;
				}
			}
		}//cout << endl;
		if (shortest_length != 101) //잡을 상어가 있음
		{
			//cout << "시간	" << person << "	잡은 상어 index	" << temp_v << "잡은 상어 크기	" << s[temp_v].z<< endl;
			person_get += s[temp_v].z;
			s[temp_v].z = 0; //죽임
			//s.erase(s.begin() + temp_v); //상어 잡음
		}

		//***************************상어 이동
		move_shark();

		//***************************상어 die -> 벡터에서 지우기
		eat_shark();

		++person;
	}

	return person_get;
}

int main()
{
	int s_num;
	cin >> R >> C >> s_num;
	SHARK temp;
	for (int si = 0; si < s_num; ++si)
	{
		cin >> temp.r >> temp.c >> temp.s >> temp.d >> temp.z;

		//불필요한 상어 이동 없애기
		if (temp.d == 1 || temp.d == 2) temp.s = (temp.s % ((R - 1) * 2));
		else if (temp.d == 3 || temp.d == 4) temp.s = (temp.s % ((C - 1) * 2));

		s.push_back(temp);
	}

	if (s_num == 0)
		cout << 0;
	else
		cout << timeloop();

	return 0;
}