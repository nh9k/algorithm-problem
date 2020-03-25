#include <iostream>
int n, m, c; //ũŰ, ä��ũ��, �ִ� ä���
int honey[10][10], worker[2][5], revenue[2], max_revenue; //����map, �ϲ�1,2�� �����ִ� �迭�� ����, �ϲ�1,2����, �ִ����
bool visit[5];

void result()
{
	if (max_revenue < revenue[0] + revenue[1]) //worker1�� worker2�� ��
		max_revenue = revenue[0] + revenue[1];	//�ִ� ���� ����
}

void small_dfs(int present, int who, int visitnum) //���� c���� �۰� �ִ� ������ �ǵ��� ���� ����
{ //���� �ε���, �ϲ�1or2, ���� ����-1
	if (visitnum >= 1) //�̷��� ���ָ� �迭�� 729�̸� 7->72->729->79->2->29->9 �� ����. 
	{					//�߰��� ���ϵǸ� ����� �� ���ϱ�. �Ʒ��� ������ ���ְ� m���丮��ŭ ������ �� �� ��Ȯ�ϴ�.
		bool flag = false;
		int check = 0;

		for (int i = 0; i < m; i++)
			if (visit[i] == true) 
				check += worker[who][i];	//�ϲ� �Ѹ� ���ؼ� �迭 ��			

		if (check <= c) flag = true; //���� c�纸�� �۾ƾ� 
		else return;
		if (flag)
		{
			check = 0;
			for (int i = 0; i < m; i++)	
				if (visit[i] == true)
					check += worker[who][i] * worker[who][i]; //���� ���� �� ����

			if (check > revenue[who]) //�ϲ� �Ѹ� ���ؼ� �ִ��̸� 
				revenue[who] = check;
		}
		//���⼭ ������ ���ָ� small_dfs(0, 0, 0);�� ���� �� if (visitnum >= 1)���� 1�� �ƴ϶� m���丮��ŭ ���������
	}
	for (int i = present; i < m; i++)
	{
		visit[i] = true;
		small_dfs(i + 1, who, visitnum + 1); //�迭 ���� 729, m�� 3�̸� 7->72->729->79->2->29->9
		visit[i] = false;
	}
}

void big_repeat() //m ũ�⸸ŭ ��� �湮: �� �ϲ��� �迭�� small_dfs�� �Ѱ���
{
	for (int i = 0; i < n; i++) //�ϲ� 1�� ���� �迭: ������
	{
		for (int j = 0; j <= n - m; j++) //�ϲ� 1�� ���� �迭: ������
		{
			for (int k = 0; k < m; k++) //�迭 ������ ���� �ϲ� 1 �迭 ����
				worker[0][k] = honey[i][j + k];

			revenue[0] = 0, revenue[1] = 0; //����!! �ʱ�ȭ �� ���ֱ�: �ϲ�1 ������ ������ �� �� �ʱ�ȭ
			small_dfs(0, 0, 0); //�ϲ� 1 �迭 ������ �Ϳ� ���� �迭 ���� ���� dfs�� ���� �ִ� ������ ����

			for (int i2 = i; i2 < n; i2++) //�ϲ� 2�� ���� �迭: ������
			{
				if (i2 == i) //�ϲ� 1�� ���� �ٿ� ���� ���
				{
					for (int j2 = j + m; j2 <= n - m; j2++) //�ϲ� 2�� ���� �迭: ������
					{
						for (int k = 0; k < m; k++) //�迭 ������ ���� �ϲ� 2 �迭 ����
							worker[1][k] = honey[i2][j2 + k];
							
						small_dfs(0, 1, 0); //�ϲ� 2 �迭 ������ �Ϳ� ���� �迭 ���� ���� dfs�� ���� �ִ� ������ ����
						result(); //�ϲ� 1�� 2�� �ִ� ���� ��
					}
				}
				else //�ϲ� 1�� �ٸ� �ٿ� ���� ���
				{
					for (int j2 = 0; j2 <= n - m; j2++) //�ϲ� 2�� ���� �迭: ������
					{

						for (int k = 0; k < m; k++) //�迭 ������ ���� �ϲ� 2 �迭 ����
							worker[1][k] = honey[i2][j2 + k];
							
						small_dfs(0, 1, 0); //�ϲ� 2 �迭 ������ �Ϳ� ���� �迭 ���� ���� dfs�� ���� �ִ� ������ ����
						result(); //�ϲ� 1�� 2�� �ִ� ���� ��
					}
				}
			}
		}
	}
}
//#1 174
//#2 131
//#3 145
//#4 155
//#5 166
//#6 239
//#7 166
//#8 172
//#9 291
//#10 464
int main()
{
	freopen("sample_input.txt", "r", stdin);
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
	{
		scanf("%d %d %d", &n, &m, &c);
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				scanf("%d", &honey[j][k]);

		revenue[0] = 0, revenue[1] = 0, max_revenue = 0;
		big_repeat(); //��ü ū �ݺ��� Ʋ
		printf("#%d %d\n", i + 1, max_revenue);
	}
}