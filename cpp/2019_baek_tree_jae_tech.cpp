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
				die_sz = qsz - ti; //���� ���� ���� ���� �� break
				break;
			}
			map[(*vsz).x][(*vsz).y] -= (*vsz).tree[ti]; //��� ����
			(*vsz).tree[ti]++; //���� ����
		}
		for (int ti = 0; ti < die_sz; ++ti) //��� ���� ���� ������ die //������ ���� ������ ����
		{
			map[(*vsz).x][(*vsz).y] += (*vsz).tree.back() / 2; //���� : ���� ����/2�� ����� ��
			(*vsz).tree.pop_back();
		}

		if (die_sz == qsz) { //�� �ڸ� ��� ������ ���� //clear
			isempty[(*vsz).x][(*vsz).y] = false; //���� ����� ���� map�� ǥ�� ����!!
			vsz = t.erase(vsz);
		}
		else
			vsz++;
	}
}
void fall()
{
	int tsz = t.size(); //�̰� �����ָ� ������(����1) ������ �ٽ� ���� ��. ���ʿ� ���� - �ð� �ʰ� ����1
	for (int vsz = 0; vsz < tsz; ++vsz)
	{
		for (int ti = 0; ti < t[vsz].tree.size(); ++ti)
		{
			if (t[vsz].tree[ti] % 5 == 0) //5���
			{
				for (int ri = t[vsz].x - 1; ri <= t[vsz].x + 1; ++ri) //���� 8�� ���� �ɱ�
				{
					for (int ci = t[vsz].y - 1; ci <= t[vsz].y + 1; ++ci)
					{
						if (ri < 0 || ci < 0 || ri >= n || ci >= n) continue; //���� ���� ���� �� ����
						else if (ri == t[vsz].x && ci == t[vsz].y) continue; //�߰� �ڸ��� �� ����

						if (isempty[ri][ci])
						{
							for (int vsz2 = 0; vsz2 < t.size(); ++vsz2) //���� ��ġ x, y ã��
							{
								if (t[vsz2].x == ri && t[vsz2].y == ci)
								{
									t[vsz2].tree.push_front(1); //������ �� ��ġ�� ���� ����
									break;
								}
							}
						}
						else
						{ //������ ���� ����
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

		t.push_back({ temp_x-1, temp_y-1 }); //�Է����� �־����� ������ ��ġ�� ��� �ٸ�
		t[mi].tree.push_front(temp_old);
		isempty[temp_x - 1][temp_y - 1] = true; //���⵵ temp_x -1, temp_y -1 �� �������!! ����
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