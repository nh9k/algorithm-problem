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

int simulate() //시간에 따라 동작 후에 마지막 사람의 시간을 리턴하는 함수
{
	vector<pair<int, int>> sorted_p;
	for (int i = 0; i < pn; i++) //거리 계산
	{
		int whatstair = p[i].select;
		p[i].t = abs(p[i].x - s[whatstair].x) + abs(p[i].y - s[whatstair].y); //계단까지의 거리 대입
		sorted_p.push_back({ p[i].t + 1, i }); //거리, 사람idx 대입
	}
	sort(sorted_p.begin(), sorted_p.end()); //거리에 따라 오름차순 정렬

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
			if ((*i).first <= simul_t)//시간이 다된 친구들 push //1번 계단은 push가 안되나 2번은 될 수 도 있으니 idx로 반복문
			{
				if (p[(*i).second].select == 0) { //1번 계단 선택
					if (waiting_s1.size() >= 3) {
						i++;
						continue; //3명 이상일 경우 push no
					}

					p[(*i).second].t += s[0].t + (simul_t - (*i).first); //계단 시간 + 대기 시간
					waiting_s1.push((*i).second);
					i = sorted_p.erase(i);
					pp = 1; //지우면
				}
				else { //2번 계단 선택
					if (waiting_s2.size() >= 3) {
						i++;
						continue; //3명 이상일 경우 push no
					}

					p[(*i).second].t += s[1].t + (simul_t - (*i).first); //계단 시간 + 대기 시간
					waiting_s2.push((*i).second);
					i = sorted_p.erase(i);
					pp = 1; //지우면
				}	
			}
			else
				break;

			if (pp != 1) { //안 지웠다
				i++;
			}
			else pp = 0; //지웠다
		}

		int q1sz = waiting_s1.size();
		int q2sz = waiting_s2.size();

		for (int i = 0; i < q1sz; i++)
		{
			if (p[waiting_s1.front()].t == simul_t)
				waiting_s1.pop(); //빠져 나감
			else break;
		}
		for (int i = 0; i < q2sz; i++)
		{
			if (p[waiting_s2.front()].t == simul_t)
				waiting_s2.pop(); //빠져 나감
			else break;
		}

		if (vsz == 0 && q1sz == 0 && q2sz == 0)
			end_flag = true;
	}
	return simul_t;
}

void dfs(int cnt) //최대 사람수 10명을 2그룹(계단 1,2)으로 나누는 함수
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
				if (temp == 1) { //사람 입력
					p[pn].x = i;
					p[pn].y = j;
					p[pn].t = 0;
					pn++;
				}
				else if (temp != 0) { //계단 입력
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