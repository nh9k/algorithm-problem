#include <iostream>
#include <queue>
using namespace std;
int n, m, k, a, b; //����, ����, ��, ����������, ����������
int at[9], bt[9];
typedef struct map
{
	int map, custom_num;
}map;
map recep_map[9], repai_map[9]; //�� üũ�� map
typedef struct customer
{ //�̿��� ���� â�� ��ȣ, ���� â�� ��ȣ, ����
	int recep_num, repai_num;
	bool end;
}customer;
customer p[1000];
queue <int> kc, waiting2; //���� -> ���� //���� -> ���� //���� �ð�
//���� ���� ��ٸ��� �ִ� ��� ����ȣ�� ���� ������� �켱 �����Ѵ�
priority_queue <int, vector<int>, greater<int>> waiting1; //��������
//���� ��ٸ��� ���� �켱�Ѵ�.
//�� �� �̻��� ������ ���� â������ ���ÿ� ������ �Ϸ��ϰ� ���� â���� �̵��� ���, �̿��ߴ� ���� â����ȣ�� ���� ���� �켱
priority_queue <pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> tempwait2; //key ��������

int who() //������ �Ҿ���� ���� �� ���� â��� ���� â�� ��ȣ�� ���� ��� ������
{
	int sum = 0;
	bool flag = false;
	for (int i = 0; i < k; i++)
	{
		if ((a == p[i].recep_num) && (b == p[i].repai_num))
		{
			sum += (i + 1);
			flag = true;
		}
			
	}
	if (flag == true) return sum;
	else return -1;
}

void working() //�ð��� ���� �� �̵�
{
	int timek = 0, c = 0;
	int checking = false;
	while (!checking) 
	{
		while (!kc.empty()) 
		{
			if (timek == kc.front()) //������� ���� â�� �ֱ�
			{
				kc.pop();
				waiting1.push(c);
				c++; //�� �� ����
			}
			else
				break;
		}

		for (int i = 0; i < n; i++) //���� â���� ���� ��ȣ���� �˻�: ���� �ִ� â���� ��� �ð�++
		{
			if (recep_map[i].map != -1) //���� �ִ� ���� â��
			{
				if (recep_map[i].map == at[i]-1) //���� â�� ó�� �ð��� ������
				{
					recep_map[i].map = -1; //�� ���� â��
					tempwait2.push({ i,recep_map[i].custom_num }); //���� â�� waiting�� ����
				}
				else
				{
					recep_map[i].map++; //���� �ִ� â���� ��� �ð�++
				}
			}
		}

		while (!waiting1.empty()) //���� ���� waiting ó��
		{
			bool flag = false;
			for (int i = 0; i < n; i++) //���� â���� ���� ��ȣ���� �˻�
			{	
				if (waiting1.empty()) break;
				if (recep_map[i].map == -1) //�� ���� â��
				{
					recep_map[i].map = 0; //���� ���� â�� 
					recep_map[i].custom_num = waiting1.top(); //���� â�� �� ��ȣ ����
					p[waiting1.top()].recep_num = i+1; //���� â�� ��ȣ ���� ����
					waiting1.pop();
				}
				if (i == n-1) flag = true; //���� â�� ��� �˻��ص� �� ���� ����
			}
			if (flag == true) break;
		}

		for (int i = 0; i < m; i++) //���� â���� ���� ��ȣ���� �˻�: ���� �ִ� â���� ��� �ð�++
		{
			if (repai_map[i].map != -1) //���� �ִ� ���� â��
			{
				if (repai_map[i].map == bt[i]-1) //���� â�� ó�� �ð��� ������
				{
					repai_map[i].map = -1; //�� ���� â��
					p[repai_map[i].custom_num].end = true;
				}
				else
				{
					repai_map[i].map++; //���� �ִ� â���� ��� �ð�++
				}
			}
		}

		while (!tempwait2.empty())
		{ //���� ��ٸ��� ���� �켱�Ѵ�.: queue�� waiting2���� ����
		  //�� �� �̻��� ������ ���� â������ ���ÿ� ������ �Ϸ��ϰ� ���� â���� �̵��� ���, �̿��ߴ� ���� â����ȣ�� ���� ���� �켱
		  //: priority queue�� tempwait2���� ����
			waiting2.push(tempwait2.top().second);
			tempwait2.pop();
		}

		while (!waiting2.empty()) //���� ���� waiting
		{
			bool flag = false;
			for (int i = 0; i < m; i++) //���� â���� ���� ��ȣ���� �˻�
			{
				if (waiting2.empty()) break;
				if (repai_map[i].map == -1) //�� ���� â��
				{
					repai_map[i].map = 0; //���� ���� â�� 
					repai_map[i].custom_num = waiting2.front(); //���� â�� �� ��ȣ ����
					p[waiting2.front()].repai_num = i+1; //���� â�� ��ȣ ���� ����
					waiting2.pop();
				}
				if (i == m-1) flag = true; //���� â�� ��� �˻��ص� �� ���� ����
			}
			if (flag == true) break;
		}

		checking = true;
		for (int i = 0; i < k; i++) //��� ���� �������� �˻�
			if (p[i].end == false) { checking = false; break; }

		timek++; //�ð� ����
	}
}
/*
#1 3
#2 7
#3 2
#4 22
#5 18
#6 15
#7 - 1
#8 259
#9 100
#10 164*/
int main()
{
	freopen("sample_input.txt", "r", stdin);
	int t, kt;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
	{	
		scanf("%d %d %d %d %d", &n, &m, &k, &a, &b);
		for (int j = 0; j < n; j++) //���� �ð�
			scanf("%d", &at[j]);
		for (int j = 0; j < m; j++) //���� �ð�
			scanf("%d", &bt[j]);
		for (int j = 0; j < k; j++) {//�� ���� �ð�
			scanf("%d", &kt); //�� ��ȣ�� ������ ���� �����ð��� ū��? �ϴ� �׷��ٰ� ����.
			kc.push(kt);
		}
		for (int j = 0; j < n; j++) //���� map �ʱ�ȭ
		{
			recep_map[j].map = -1;
			recep_map[j].custom_num = 0;
		}	
		for (int j = 0; j < m; j++) //���� map �ʱ�ȭ
		{
			repai_map[j].map = -1;
			repai_map[j].custom_num = 0;
		}
		for (int j = 0; j < k; j++) //�� ���� �ʱ�ȭ
		{
			p[j].end = false;
			p[j].recep_num = 0;
			p[j].repai_num = 0;
		}
		//if(i + 1 == 7)
		working();
		if (i + 1 == 7)
		printf("#%d %d\n", i + 1, who());
	}
}