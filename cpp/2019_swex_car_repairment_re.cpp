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
		//����-> ����
		for (int ni = 0; ni < n; ++ni)
		{
			if (nvisit[ni] != 0) //á����
			{
				c[nvisit[ni]].t++; //�ð� ����
				if (c[nvisit[ni]].t == nmap[ni])
				{
					wait2.push(nvisit[ni]); //����ȣ �ֱ�
					c[nvisit[ni]].t = 0; //�ð� 0
					nvisit[ni] = 0; //����
				}
			}
		}

		//���-> ����
		bool pass = false;
		while (!wait1.empty())
		{		
			if (wait1.front() <= tc && !pass)
			{
				pass = true;
				for (int ni = 0; ni < n; ++ni)
				{
					if (nvisit[ni] == 0) //�������
					{
						nvisit[ni] = cnum; //���� â�� ä��
						c[cnum].n = ni + 1; //â����ȣ �ְ�
						cnum++; //�� ��ȣ ����
						wait1.pop();
						pass = false;
						break;
					}
				}
			}
			else
				break;
		}
		

		//���-> ���� -> ����
		for (int mi = 0; mi < m; ++mi)
		{
			if (mvisit[mi] != 0) //á����
			{
				c[mvisit[mi]].t++; //�ð� ����
				if (c[mvisit[mi]].t == mmap[mi])
				{
					c[mvisit[mi]].t = -1; //�ð� 0
					mvisit[mi] = 0; //����
				}
			}

			if(mvisit[mi]==0 && !wait2.empty()) //â���� �������
			{
				mvisit[mi] = wait2.front();
				c[mvisit[mi]].m = mi + 1; //â�� ��ȣ �ְ�
				wait2.pop();
			}
		}

		//�������� �˻�
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
