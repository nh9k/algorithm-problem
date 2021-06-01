#include <iostream>
#include <queue>
using namespace std;
int n, m, k, a, b, sum, nmap[9], mmap[9], nvisit[9], mvisit[9];
typedef struct {
	int n, m, t;
}CUSTOMER;
CUSTOMER c[1001];
queue <int> wait1, wait2;

void simulation()
{
	int tc = 0,  cnum=1;
	while (1)
	{
		//접수-> 정비
		for (int ni = 0; ni < n; ++ni)
		{
			if (nvisit[ni] != 0) //찼으면
			{
				c[nvisit[ni]].t++; //시간 증가
				if (c[nvisit[ni]].t == nmap[ni])
				{
					wait2.push(nvisit[ni]); //고객번호 넣기
					c[nvisit[ni]].t = 0; //시간 0
					nvisit[ni] = 0; //비우기
				}
			}
		}

		//출발-> 접수
		bool pass = false;
		while (!wait1.empty())
		{		
			if (wait1.front() <= tc && !pass)
			{
				pass = true;
				for (int ni = 0; ni < n; ++ni)
				{
					if (nvisit[ni] == 0) //비었으면
					{
						nvisit[ni] = cnum; //접수 창구 채움
						c[cnum].n = ni + 1; //창구번호 넣고
						cnum++; //고객 번호 증가
						wait1.pop();
						pass = false;
						break;
					}
				}
			}
			else
				break;
		}
		

		//대기-> 정비 -> 비우기
		for (int mi = 0; mi < m; ++mi)
		{
			if (mvisit[mi] != 0) //찼으면
			{
				c[mvisit[mi]].t++; //시간 증가
				if (c[mvisit[mi]].t == mmap[mi])
				{
					c[mvisit[mi]].t = -1; //시간 0
					mvisit[mi] = 0; //비우기
				}
			}

			if(mvisit[mi]==0 && !wait2.empty()) //창구가 비었으면
			{
				mvisit[mi] = wait2.front();
				c[mvisit[mi]].m = mi + 1; //창구 번호 넣고
				wait2.pop();
			}
		}

		//끝났는지 검사
		bool finish = true;
		for (int ki = 1; ki <= k; ++ki)
		{
			if (c[ki].t != -1)
			{
				finish = false;
				break;
			}
		}
		if (finish) break;
		tc++;
	}

	for (int ki = 1; ki <= k; ++ki)
	{
		if (c[ki].n==a && c[ki].m == b)
		{
			sum += ki;
		}
	}
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	int t;
	cin >> t;
	for (int ti = 0; ti < t; ++ti)
	{
		cin >> n >> m >> k >> a >> b;
		int temp;
		for (int ni = 0; ni < n; ++ni)
		{
			cin >> temp;
			nmap[ni] = temp;
		}
		for (int mi = 0; mi < m; ++mi)
		{
			cin >> temp;
			mmap[mi] = temp;
		}
		for (int ki = 1; ki <= k; ++ki)
		{
			cin >> temp;
			wait1.push(temp);
			c[ki].t = 0, c[ki].t = 0;
		}
		sum = 0;
		simulation();
		if(sum==0)
			cout << "#" << ti + 1 << " " << -1 << endl;
		else
			cout << "#" << ti + 1 << " " << sum << endl;
	}
	return 0;
}
