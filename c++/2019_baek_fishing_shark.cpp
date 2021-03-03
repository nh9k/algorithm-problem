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
		if (s[v].z == 0) continue; //����� ��Ƽ� ���� ���� �Ѿ

		if (s[v].d == 1 || s[v].d == 2)
		{
			for (int m = 0; m < s[v].s; ++m)
			{
				//cout << v << "	��� �̵� x	" << s[v].r << "	��� �̵� y	" << s[v].c << endl;
				if (s[v].r == 1 && s[v].d == 1) s[v].d = 2;
				else if (s[v].r == R && s[v].d == 2) s[v].d = 1;
				s[v].r += mx[s[v].d];
			}
		}
		else
		{
			for (int m = 0; m < s[v].s; ++m)
			{
				//cout << v << "	��� �̵� x	" << s[v].r << "	��� �̵� y	" << s[v].c << endl;
				if (s[v].c == 1 && s[v].d == 4) s[v].d = 3;
				else if (s[v].c == C && s[v].d == 3) s[v].d = 4;
				s[v].c += my[s[v].d];
			}
		}

		//���� ���� �� �ִ��� ����(�̵��� ��ģ ������ �ִ��� �˻�)
		//cout << map[s[v].r][s[v].c] - 1 << endl;
		if (map[s[v].r][s[v].c] != 0)
		{
			if (s[map[s[v].r][s[v].c] - 1].z < s[v].z)
			{
				s[map[s[v].r][s[v].c] - 1].z = 0; //���� �ִ� ��� ��Ƹ���
				map[s[v].r][s[v].c] = (v + 1); //���ο� ���� ä��
			}
			else
			{
				s[v].z = 0; //���ο� ��� ��Ƹ���
			}
		}
		else //�ƹ��� ������
			map[s[v].r][s[v].c] += v+1;
	}
}

void eat_shark() //���� ���(������� �����ų� �����ų�) ��� �����
{
	for (auto v = s.begin(); v != s.end();)
	{
		if ((*v).z == 0)
		{
			//���� ���
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
		for (int i = 1; i <= R; i++) //���� �� ���� ���Ŀ� 
		{	//��� ������ index�� �ٲ�Ƿ� �ƿ� map���� ���������� move_shark������ �ε����� �����Ͽ� �̵���ģ �� �˻�
			for (int j = 1; j <= C; j++) {
				//cout << map[i][j];
				map[i][j] = 0;
			}
			//cout << endl;
		}//cout << endl;

		//***************************��� ���
		int vsz = s.size();
		int temp_v = 0, shortest_length = 101;
		for (int v = 0; v < vsz; ++v) //���� ����� ��� Ž��
		{
			//cout << v << "	��� �̵�	" << s[v].r << " " << s[v].c << endl;
			if (s[v].c == person)
			{
				if (shortest_length > s[v].r)
				{
					shortest_length = s[v].r;
					temp_v = v;
				}
			}
		}//cout << endl;
		if (shortest_length != 101) //���� �� ����
		{
			//cout << "�ð�	" << person << "	���� ��� index	" << temp_v << "���� ��� ũ��	" << s[temp_v].z<< endl;
			person_get += s[temp_v].z;
			s[temp_v].z = 0; //����
			//s.erase(s.begin() + temp_v); //��� ����
		}

		//***************************��� �̵�
		move_shark();

		//***************************��� die -> ���Ϳ��� �����
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

		//���ʿ��� ��� �̵� ���ֱ�
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