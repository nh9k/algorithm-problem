/*
@nh9k
1) 4�� for������ x, y, d1, d2 ����
2) 5���ű� ��輱 ����
3) ������ ���ű� �� ���ϱ�
  �迭���� y�� ���� ���ʿ��� �߽����� �̵��ϸ鼭 5���ű� ��迡 ������ break
  5���ű��� ó���� �迭 �Է½� �α��� ���� ���ؼ� (�α��� ����) - (������ ���ű� ��) => 5���ű��� ����� ������ ���� ������ Ʋ��
4) �ִ�, �ּҸ� ���� �� �ִ� - �ּҰ� �ּ��� ���� result �� ����

����         ä�� ��ȣ	���̵�	���� ��ȣ	���	        �޸�	�ð�	���	        �ڵ� ����	������ �ð�
���� 17779�� 19404549	nh9k	17779	    �¾ҽ��ϴ�!!	1984kb	12ms->8ms	C++14 / ����	3079	    5�� ��

���� ����	�ڵ� �ۼ�	�����
1�ð�		1�ð�		1�ð�

5���ű� ���ߴ� �ҽ�
	for (int i = x; i <= x + d1 + d2; ++i)
	{
		for (int j = y - d1; j <= y + 2; ++j) //���⼭ y+2�� �� ������.. 2->d2�� �ϸ� ����, ���� �ҽ��� �ð��� �Һ�
		{
			if (checkmap[i][j] == true) continue;
			checkmap[i][j] = true;
			sum[4] += realmap[i][j];
		}
	}
*/

#include <iostream>
using namespace std;

int N;
int realmap[20][20];
bool checkmap[20][20];
int sum[5], allsum;
int result;

//void printmap()
//{
//	for (int i = 0; i < N; ++i)
//	{
//		for (int j = 0; j < N; ++j)
//		{
//			cout << checkmap[i][j];
//		}
//		cout << endl;
//	}
//	cout << endl;
//}

void check5sum(int x, int y, int d1, int d2) //5���ű� ��� ����
{
	for (int i = x, j = y; (i <= x + d1)&&(j >= y - d1); ++i, --j)
	{
		checkmap[i][j] = true;
	}
	for (int i = x, j = y; (i <= x + d2) && (j <= y + d2); ++i, ++j)
	{
		//if (checkmap[i][j] == true) continue; //����� 4ms ����(12->8ms)
		checkmap[i][j] = true;
	}
	for (int i = x + d1, j = y - d1; (i <= x + d1 + d2) && (j <= y - d1 + d2); ++i, ++j)
	{
		//if (checkmap[i][j] == true) continue; //����� 4ms ����(12->8ms)
		checkmap[i][j] = true;
	}
	for (int i = x + d2, j = y + d2; (i <= x + d1 + d2) && (j >= y +d2 - d1); ++i, --j)
	{
		//if (checkmap[i][j] == true) continue; //����� 4ms ����(12->8ms)
		checkmap[i][j] = true;
	}
}

void checkallsum(int x, int y, int d1, int d2) //������ ���ű� sum ���
{
	for (int i = 0; i < x + d1; ++i) //1���ű�
	{
		for (int j = 0; j <= y; ++j)
		{
			if (checkmap[i][j] == true) break;
			checkmap[i][j] = true;
			sum[0] += realmap[i][j];
		}
	}
	//printmap();
	for (int i = 0; i <= x + d2; ++i) //2���ű�
	{
		for (int j = N - 1; j > y; --j)
		{
			if (checkmap[i][j] == true) break;
			checkmap[i][j] = true;
			sum[1] += realmap[i][j];
		}
	}
	//printmap();
	for (int i = x+d1; i < N; ++i) //3���ű�
	{
		for (int j = 0; j < y - d1 + d2; ++j)
		{
			if (checkmap[i][j] == true) break;
			checkmap[i][j] = true;
			sum[2] += realmap[i][j];
		}
	}
	//printmap();
	for (int i = x + d2 + 1; i < N; ++i) //4���ű�
	{
		for (int j = N - 1; j >= y - d1 + d2; --j)
		{
			if (checkmap[i][j] == true) break;
			checkmap[i][j] = true;
			sum[3] += realmap[i][j];
		}
	}
	//printmap();
	//5���ű�
	sum[4] = allsum - (sum[0] + sum[1] + sum[2] + sum[3]);
	//printmap();
}

void isresult()
{
	int minvalue = 40000;
	int maxvalue = 0;
	for (int chk = 0; chk < 5; ++chk)
	{
		if (sum[chk] < minvalue)
			minvalue = sum[chk];
		if (sum[chk] > maxvalue)
			maxvalue = sum[chk];
		//initialize
		//cout << sum[chk] << " ";
		sum[chk] = 0;
	}
	if (result > (maxvalue - minvalue))
		result = maxvalue - minvalue;

	//cout << endl << maxvalue - minvalue << endl;
	//initialize
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			checkmap[i][j] = false;
		}
	}
}



int main()
{
	cin >> N;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cin >> realmap[i][j];
			allsum += realmap[i][j];
		}
	}

	result = 40000;
	//determine x, y, d1, d2
	for (int x = 0; x < N; ++x)
	{
		for (int y = 0; y < N; ++y)
		{
			//if (((x == 0) && (y == 0)) || ((x == N - 1) && (y == 0)) || ((x == 0) && (y == N - 1)) || ((x == N - 1) && (y == N - 1))) continue;
			for (int d1 = 1; (x + d1 < N - 1)&&(y - d1 >= 0); ++d1)
			{
				for (int d2 = 1; (x + d1 + d2 < N) && (y + d2 < N); ++d2)
				{
					//printmap();
					check5sum(x, y, d1, d2);
					//printmap();
					checkallsum(x, y, d1, d2);
					isresult();
				}
			}
		}
	}

	cout << result;
}
