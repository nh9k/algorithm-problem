#include<iostream>

using namespace std;

int m, a, tm; //�̵��ð�, bc��, �ǽð� �̵��ð�
int a1[101], a2[101]; //����� 2���� �̵� ����
int dy[5] = { 0,-1,0,1,0 }; //���� �� �� �� ��
int dx[5] = { 0,0,1,0,-1 };
int bcin[2][8], bcidx1, bcidx2;

typedef struct users
{
	int x, y;
}users;
users user[2];

typedef struct ap
{
	int x, y, c, p;
}ap;
ap bc[8];

void dist() //�Ÿ��� ����ؼ� ����ڰ� ��� & ��� ���ϴ��� ����ϴ� �Լ�
{
	user[0].x += dx[a1[tm]];  user[1].x += dx[a2[tm]];
	user[0].y += dy[a1[tm]];  user[1].y += dy[a2[tm]];	
	tm++;

	bcidx1 = 0, bcidx2 = 0;
	for (int i = 0; i < a; i++)
	{
		if (abs(user[0].x - bc[i].x) + abs(user[0].y - bc[i].y) <= bc[i].c) //����� 1�� bc ���̸�
		{
			bcin[0][bcidx1] = i; //bc�� ��ȣ�� �ְ�
			bcidx1++; 
		}
		if (abs(user[1].x - bc[i].x) + abs(user[1].y - bc[i].y) <= bc[i].c)
		{
			bcin[1][bcidx2] = i;
			bcidx2++;
		}			
	}
}

int maxresult() //��ġ���� �� ����ڰ� ������ bc���� �ִ� ����ϴ� �Լ� + �ִ��� ����
{
	int maximum=0, present, result = 0;
	for (int i = 0; i < m + 1; i++) // �ð�����, �̵�
	{
		dist();
		
		if (bcidx1 == 0 && bcidx2 != 0) //�����2�� ������ ���
		{
			maximum = 0;
			for (int k = 0; k < bcidx2; k++) //����� 2
			{
				 present = bc[bcin[1][k]].p;

				if (maximum < present)
				{
					maximum = present;
				}
			}
		}
		else if (bcidx1 != 0 && bcidx2 == 0) //�����1�� ������ ���
		{
			maximum = 0;
			for (int j = 0; j < bcidx1; j++) //����� 1
			{
				present = bc[bcin[0][j]].p;

				if (maximum < present)
				{
					maximum = present;
				}
			}
		}
		else { //�Ѵ� ������ ���
			maximum = 0;
			for (int j = 0; j < bcidx1; j++) //����� 1�� ������ bc ���
			{
				for (int k = 0; k < bcidx2; k++) //����� 2�� ������ bc ���
				{
					if (bcin[0][j] == bcin[1][k]) //���� bc��
					{
						present = bc[bcin[0][j]].p; //������ ���ݾ��̹Ƿ� �״�� ��
					}
					else
					{
						present = bc[bcin[0][j]].p + bc[bcin[1][k]].p;
					}
					if (maximum < present)
					{
						maximum = present;
					}
				}
			}
		}
		result += maximum;
	}
	return result;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("sample_input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		scanf("%d %d", &m, &a);

		a1[0] = 0; //ó���� ���� ����
		for (int i = 1; i < m+1; i++)
			scanf("%d", &a1[i]);

		a2[0] = 0;
		for (int i = 1; i < m+1; i++)
			scanf("%d", &a2[i]);

		for (int i = 0; i < a; i++)
			scanf("%d %d %d %d", &bc[i].x, &bc[i].y, &bc[i].c, &bc[i].p);

		user[0].x = 1; user[0].y = 1;  //����� 1 ó�� ����
		user[1].x = 10; user[1].y = 10; //����� 2 ó�� ����
		tm = 0; //����� ������ �ð�

		printf("#%d %d\n", test_case, maxresult());
	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}