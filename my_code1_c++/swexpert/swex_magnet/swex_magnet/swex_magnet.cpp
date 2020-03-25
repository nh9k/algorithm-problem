#include <iostream>
//using namespace std;

int magnet[4][8], mrot[4], mleft[4], mright[4];
int k, km[20], krot[20];

void checkrot(int j) //km(�ڼ� ��ȣ), krot(�̵� ����)�� ���� mright, mleft�� ����, mrot�� �����ϴ� �κ�
{
	mrot[km[j] - 1] = krot[j];

	if (km[j] != 4)
	{
		for (int h = km[j] - 1; h < 3; h++)
		{
			if (magnet[h][mright[h]] == magnet[h + 1][mleft[h + 1]])
				mrot[h + 1] = 0;
			else
				mrot[h + 1] = mrot[h] * (-1);
		}
	}
	if (km[j] != 1)
	{
		for (int h = km[j] - 1; h > 0; h--)
		{
			if (magnet[h][mleft[h]] == magnet[h - 1][mright[h - 1]])
				mrot[h - 1] = 0;
			else
				mrot[h - 1] = mrot[h] * (-1);
		}
	}
}

void rot() //mrot�� ���� mright, mleft�� �̵���Ű�� �κ�
{
	for (int i = 0; i < 4; i++)
	{
		if (mrot[i] == (-1)) //�ݽð� ȸ��
		{
			mright[i] += 1;
			mleft[i] += 1;
		}
		else if (mrot[i] == 1) //�ð� ȸ��
		{
			mright[i] -= 1;
			mleft[i] -= 1;
		}
		// �� �� 0�� ȸ������ ����

		if (mright[i] < 0) mright[i] += 8;
		else if (mright[i] > 7) mright[i] -= 8;
		
		if (mleft[i] < 0) mleft[i] += 8;
		else if (mleft[i] > 7) mleft[i] -= 8;		
	}
}

int point() //mleft�� ���� [0]�� ���� ȭ��ǥ �κ��� ���� ������ �ű�� �Լ�
{
	int sum = 0;
	for (int j = 0; j < 4; j++)
	{
		if (mright[j] - 2 < 0)
		{
			if (magnet[j][mright[j] + 6] == 1)
			{
				if (j == 0) sum += 1;
				else if (j == 1) sum += 2;
				else if (j == 2)sum += 4;
				else if(j == 3) sum += 8;
			}
		}
		else
		{
			if (magnet[j][mright[j] - 2] == 1)
			{
				if (j == 0) sum += 1;
				else if (j == 1) sum += 2;
				else if (j == 2)sum += 4;
				else if (j == 3) sum += 8;
			}
		}
	}
	return sum;
}

int main()
{
	freopen("sample_input.txt", "r", stdin);

	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
	{
		scanf("%d", &k);
		for (int j = 0; j < 4; j++)
				scanf("%d %d %d %d %d %d %d %d", &magnet[j][0], &magnet[j][1], &magnet[j][2], &magnet[j][3], 
					&magnet[j][4], &magnet[j][5], &magnet[j][6], &magnet[j][7]);

		for (int j = 0; j < k; j++)
			scanf("%d %d", &km[j], &krot[j]);

		for (int j = 0; j < 4; j++)
		{
			mright[j] = 2; mleft[j] = 6;
		}

		for (int j = 0; j < k; j++)
		{
			checkrot(j);
			rot();
		}

		printf("#%d %d\n", i + 1, point());
	}
	return 0;
}