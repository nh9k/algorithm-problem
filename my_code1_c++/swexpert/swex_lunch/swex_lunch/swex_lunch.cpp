#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int n, pn, minitime;
typedef struct {
	int x, y, t;
	bool select;
}object;
object p[10], s[2];

int simulate() //�ð��� ���� ���� �Ŀ� ������ ����� �ð��� �����ϴ� �Լ�
{
	vector<pair<int, int>> sorted_p;
	for (int i = 0; i < pn; i++) //�Ÿ� ���
	{
		int whatstair = p[i].select;
		p[i].t = abs(p[i].x - s[whatstair].x) + abs(p[i].y - s[whatstair].y); //��ܱ����� �Ÿ� ����
		sorted_p.push_back({ p[i].t + 1, i }); //�Ÿ�, ���idx ����
	}
	sort(sorted_p.begin(), sorted_p.end()); //�Ÿ��� ���� �������� ����

	queue<int> waiting_s1, waiting_s2;
	int simul_t = 0;
	bool end_flag = false;
	while (!end_flag)
	{
		if (simul_t > minitime) return -1;
		simul_t++;
		int vsz = sorted_p.size();

		bool pp = 0;
		for (auto i = sorted_p.begin(); i != sorted_p.end();)
		{		
			if ((*i).first <= simul_t)//�ð��� �ٵ� ģ���� push //1�� ����� push�� �ȵǳ� 2���� �� �� �� ������ idx�� �ݺ���
			{
				if (p[(*i).second].select == 0) { //1�� ��� ����
					if (waiting_s1.size() >= 3) {
						i++;
						continue; //3�� �̻��� ��� push no
					}

					p[(*i).second].t += s[0].t + (simul_t - (*i).first); //��� �ð� + ��� �ð�
					waiting_s1.push((*i).second);
					i = sorted_p.erase(i);
					pp = 1; //�����
				}
				else { //2�� ��� ����
					if (waiting_s2.size() >= 3) {
						i++;
						continue; //3�� �̻��� ��� push no
					}

					p[(*i).second].t += s[1].t + (simul_t - (*i).first); //��� �ð� + ��� �ð�
					waiting_s2.push((*i).second);
					i = sorted_p.erase(i);
					pp = 1; //�����
				}	
			}
			else
				break;

			if (pp != 1) { //�� ������
				i++;
			}
			else pp = 0; //������
		}

		int q1sz = waiting_s1.size();
		int q2sz = waiting_s2.size();

		for (int i = 0; i < q1sz; i++)
		{
			if (p[waiting_s1.front()].t == simul_t)
				waiting_s1.pop(); //���� ����
			else break;
		}
		for (int i = 0; i < q2sz; i++)
		{
			if (p[waiting_s2.front()].t == simul_t)
				waiting_s2.pop(); //���� ����
			else break;
		}

		if (vsz == 0 && q1sz == 0 && q2sz == 0)
			end_flag = true;
	}
	return simul_t;
}

void dfs(int cnt) //�ִ� ����� 10���� 2�׷�(��� 1,2)���� ������ �Լ�
{
	if (cnt >= pn)
	{
		int tempt = simulate();
		if (minitime > tempt && (tempt != -1))
			minitime = tempt;
		return;
	}
	for (int i = 0; i < 2; i++)
	{
		p[cnt].select = i;
		dfs(cnt + 1);
	}
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	int t;
	scanf("%d", &t);
	for (int tc = 0; tc < t; tc++)
	{
		scanf("%d", &n);
		int temp, sn = 0;
		pn = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				scanf("%d", &temp);
				if (temp == 1) { //��� �Է�
					p[pn].x = i;
					p[pn].y = j;
					p[pn].t = 0;
					pn++;
				}
				else if (temp != 0) { //��� �Է�
					s[sn].x = i;
					s[sn].y = j;
					s[sn].t = temp;
					sn++;
				}
			}
		}
		minitime = 10000;
		dfs(0);
		printf("#%d %d\n", tc + 1, minitime);
	}
	return 0;
}