/*
@nh9k
���� ��ȣ	ä�� ��ȣ	���̵�	���� ��ȣ	���			�޸�	�ð�	���			�ڵ� ����	������ �ð�		Ǯ�� �ð�
����17837	19433328	nh9k	17837		�¾ҽ��ϴ�!!	1984KB	0ms		C++14 / ����	2882		17�� ��			01:52:24.07

Ǯ�� ���
1. �Է�
	��(x,y, ����, ���� ��ġ�� ���� �ش��ϴ� ����), realmap, checkmap(���� ����map)
2. ���� Ȯ��
  - �Ķ���/outof�迭
	�̵����� ���� �ݴ�� �� �ٽ� Ȯ��
  - ��/��(���� �̵����� �̵��� �� ����)
	1) �̵��� ���� �� check
	2) �̵��� ���� ���� 1���� ��� 
		�̵����� x,y,����(�̵��� ��ġ�� checkmap+1)
	2.1)�̵��� ���� ���� 1�� �ʰ��� ���
		�̵����� x, y, ����(��: �̵����� ���� - ���� �̵��� ���� + �̵��� ��ġ�� checkmap + 1)
						   (��: �̵��� ��ġ�� checkmap - �̵����� ���� + �̵��� ��ġ�� checkmap + 1)
	3) ��� �̵��� map ����
		�̵��� map: �̵��� map - (�̵��� ���� ����)
		�̵��� map: �̵��� map + (�̵��� ���� ����)

������
�˰����� ����� + �ڵ� ������ �����ɸ�, ������� �ʿ���� �ٷ� pass
*/

#include <iostream>
using namespace std;

typedef struct {
	int x, y, m, f;
}horse;
horse h[10];
int N, K, realmap[12][12], checkmap[12][12], memBO;
int mx[5] = { 0, 0, 0, -1, 1 }, my[5] = { 0, 1, -1, 0, 0 };
int reverse_[5] = { 0, 2, 1, 4, 3 };

void printmap()
{
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cout << checkmap[i][j];
		}cout << endl;
	}cout << endl;
}

bool isOut(int x, int y)
{
	if ((x < 0) || (x >= N) || (y < 0) || (y >= N))
	{
		return true;
	}
	return false;
}

int isBlueOrOut(int ki)
{
	int movex = h[ki].x + mx[h[ki].m], movey = h[ki].y + my[h[ki].m];

	if (isOut(movex, movey) || (realmap[movex][movey] == 2)) //�� / out
	{
		if (memBO == ki) //2��°
		{
			//memBO = ki;
			return 2;
		}
		else //1��°
		{
			h[ki].m = reverse_[h[ki].m]; //���� ��ȯ
			memBO = ki;
			return 1;
		}
	}
	else //�� //��
	{
		memBO = ki;
		return 0;
	}
}

void moving(int ki) {
	int beforex = h[ki].x, beforey = h[ki].y; //�̵��� ���� ��ġ
	int beforef = h[ki].f;
	int movex = beforex + mx[h[ki].m], movey = beforey + my[h[ki].m]; //�̵��� ���� ��ġ
	int moving_h_num = checkmap[beforex][beforey] - h[ki].f + 1; //�̵��� ���� ��

	if (moving_h_num == 1) {
		h[ki].x = movex, h[ki].y = movey;
		h[ki].f = checkmap[movex][movey] + 1;
	}
	else {
		if (realmap[movex][movey] == 0) {//��
			for (int kj = 0; kj < K; ++kj) {
				if ((beforex == h[kj].x) && (beforey == h[kj].y) && (beforef <= h[kj].f))
				{
					h[kj].x = movex, h[kj].y = movey;
					h[kj].f += (checkmap[movex][movey] + 1 - beforef);
				}
			}
		}
		else {//��
			for (int kj = 0; kj < K; ++kj) {
				if ((beforex == h[kj].x) && (beforey == h[kj].y) && (beforef <= h[kj].f))
				{
					h[kj].x = movex, h[kj].y = movey;
					h[kj].f = (checkmap[movex][movey] + 1 + checkmap[beforex][beforey] - h[kj].f);
				}
			}
		}
	}

	checkmap[beforex][beforey] -= moving_h_num; //�̵��� map�� �� ���� ����
	checkmap[movex][movey] += moving_h_num; //�̵��� map�� �� ���� ����
}

bool isHorse4() {
	for (int ki = 0; ki < K; ++ki)
	{
		if (checkmap[h[ki].x][h[ki].y] >= 4)
			return true;
	}
	return false;
}

int main()
{
	cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> realmap[i][j];
		}
	}
	int inputx, inputy;
	for (int ki = 0; ki < K; ++ki)
	{

		cin >> inputx >> inputy >> h[ki].m;
		h[ki].x = inputx - 1, h[ki].y = inputy - 1;
		h[ki].f = 1; //1��
		checkmap[h[ki].x][h[ki].y] = 1;
	}

	memBO = -1;
	for (int turn = 1; turn <= 1000; ++turn)
	{
		for (int ki = 0; ki < K;)
		{
			//printmap();
			int replay = isBlueOrOut(ki); //0: ��/��, 1:��/Out, 2:��/out 2��°
			if (replay == 1) { 
				continue;
			}
			else if (replay == 2) {
				++ki;
				continue;
			}

			//��/��
			moving(ki);

			if (isHorse4())
			{
				cout << turn;
				return 0;
			}
			++ki;
		}
	}
	cout << -1;
	return 0;
}
