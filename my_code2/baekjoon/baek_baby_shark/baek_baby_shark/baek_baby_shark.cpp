#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int n, map[20][20], visit[20][20], dx[4] = { -1,0,1,0 }, dy[4] = {0,1,0,-1};
typedef struct {
	int x, y, age, cnt;
}SHARK;
SHARK s;

int bfs()
{
	int result_t = 0;
	
	while (1)
	{
		queue <pair<int, int>> search_map; //��� �ֺ� Ž���� ť
		search_map.push({ s.x, s.y }); //��� �ʱ� ��ġ
		visit[s.x][s.y] = 1; //�����ġ�� �湮�� �ʿ䰡 ����
		vector <pair<int, int>> eating_list; //���� �ð��� �湮�� �������� ���� �� �ִ� ����� �ֱ�
		int pt = 1;

		while (!search_map.empty())
		{
			int qsz = search_map.size();//���� �ð��뾿 ó��
			for (int sz = 0; sz < qsz; ++sz) 
			{
				for (int m = 0; m < 4; ++m)
				{
					int mx = search_map.front().first + dx[m], my = search_map.front().second + dy[m];

					if (mx < 0 || mx >= n || my < 0 || my >= n) continue; // �迭 ��
					else if (map[mx][my] > s.age) continue; // ���̰� ������ �����
					else if (visit[mx][my]) continue; //�̹� �湮

					search_map.push({ mx,my }); // �湮�ؾ���
					visit[mx][my] = pt; //�ð� �ֱ�
					if (map[mx][my] < s.age && map[mx][my] != 0) //���� ����Ʈ �ֱ� //���̰� � ����⸦ �ֱ�
					{//���� ����Ʈ
						eating_list.push_back({ mx, my });
					}
				}
				search_map.pop();
			}
			if (!eating_list.empty())
			{//���� ����� �����
				break;
			}
			pt++;
		}
		if (eating_list.empty())
		{//���� ����Ʈ�� ������ //while�� �� ���Ƶ� ���� ����� ������
			return result_t;
		}
		else
		{//���� ����Ʈ�� ������
			int upper = 20, lefter = 20, target;
			for (int i = 0; i < eating_list.size(); ++i)
			{
				if (upper > eating_list[i].first) //�� ���� ���� ���
				{
					upper = eating_list[i].first, lefter = eating_list[i].second; //����
					target = i;
				}
				else if (upper == eating_list[i].first) //���� ��ġ�� ���
				{
					if (lefter > eating_list[i].second) //�� ������ ���
					{
						upper = eating_list[i].first, lefter = eating_list[i].second;//����
						target = i;
					}

				}
			}
			result_t += visit[eating_list[target].first][eating_list[target].second]; //�ð� ����
			map[eating_list[target].first][eating_list[target].second] = 0; //map ����
			s.x = eating_list[target].first, s.y = eating_list[target].second; //��� ��ġ ����
			s.cnt++; //��� ���� ����
			if (s.cnt == s.age)
			{
				s.age++;
				s.cnt = 0;
			}
			for (int ni = 0; ni < n; ++ni)
				for (int nj = 0; nj < n; ++nj)
					visit[ni][nj] =  0; //visit ����
		}
	}

}

int main()
{
	cin >> n;
	for (int ni = 0; ni < n; ++ni)
	{
		for (int nj = 0; nj < n; ++nj)
		{
			cin >> map[ni][nj];
			if (map[ni][nj] == 9)
			{//���
				s.x = ni, s.y = nj, s.age = 2;
				map[ni][nj] = 0;
			}
		}
	}
	cout << bfs();
}