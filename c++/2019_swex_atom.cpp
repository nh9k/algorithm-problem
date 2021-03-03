#include<iostream>
#include<vector>
using namespace std;

typedef struct atoms
{
	int x, y, dir, k; //x,y,�̵�����, ������
}atoms;
//atoms atom[1001]; //1~1000���̹Ƿ�
int n, energy, map[4001][4001]; //���� ���� //energy ��ü //������ ������ �̵��ϸ� (-1000~1000) + 0.5�κп��� �ε����� �� ó�� (*2)
int dx[4] = { 0,0, -1,1 }, dy[4] = { 1,-1,0,0 };//�����¿� //��ǥ�� �ȳ���
vector <atoms> atom;

int move() //���ڵ��� �����̸鼭 �Ҹ��ϰ� �������� �����ϴ� �Լ�
{
	energy = 0;
	while (!atom.empty()) //��� ���ڰ� �Ҹ��� ������
	{
		int vsize = (int)atom.size();
		for (int i = 0; i < vsize; i++) //���� �̵�
		{
			map[atom[i].x][atom[i].y] = 0; //������ ���� 0���� ������
			atom[i].x += dx[atom[i].dir];
			atom[i].y += dy[atom[i].dir];

			//������ �����, ��Ӱ��� �ٸ� ���ڿ� ���� �� ����: ���� üũ
			if (atom[i].x > 4000 || atom[i].x < 0 || atom[i].y> 4000 || atom[i].y < 0)
				atom[i].k = 0; //�׳� �Ҹ� //���� �������� ������ �ʿ����

			else //�ʿ� ǥ��
				map[atom[i].x][atom[i].y] += atom[i].k;
		}

		for (int i = 0; i < vsize; i++) //���ڰ� �ε��� �� ó��
		{
			if (!atom[i].k) continue; //�̹� ������ ����� ���� ���ڴ� �Ѿ

			if (map[atom[i].x][atom[i].y] != atom[i].k) //���ڰ� 2�� �̻����� �� ��ġ�� ���� ��
			{ //���� �˻����� ���� ���ڵ鵵 �̸� energy�� �߰��� �� ������ !=�� �Ѵ�
				energy += map[atom[i].x][atom[i].y];
				map[atom[i].x][atom[i].y] = 0; //�߰��� ���� 0���� �ʱ�ȭ
				atom[i].k = 0; //�Ҹ�
			}
		}

		//�ð� �ʰ��� ���ϱ� ���� �ٽ��� vector�� queue�� �����ؼ� ������ ���ڵ��� �����ϰ� ������ ó���ϴ� ��
		//�ӽ� ���͸� �����Ͽ� ���ο� �־��ְ� �ٽ� ������ ���Ϳ� ���� ���ڸ� �����ϰ� �־���
		vector <atoms> temp;
		temp.assign(atom.begin(), atom.end()); //���� ���� ����
		atom.clear(); //���� ���� ������

		for (int i = 0; i < vsize; i++)
			if (temp[i].k != 0) //�Ҹ����� ���� �����̸�
				atom.push_back(temp[i]); //�ٽ� ���� index�� �־���
	}
	return energy;
}

int main(int argc, char** argv)
{
	int test_case, T;
	freopen("sample_input - ���纻.txt", "r", stdin);
	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case)
	{
		scanf("%d", &n);

		atoms input;
		for (int i = 0; i < n; i++)
		{
			scanf("%d %d %d %d", &input.x, &input.y, &input.dir, &input.k);
			input.x *= 2;
			input.y *= 2;
			input.x += 2000;
			input.y += 2000;
			atom.push_back(input);
		}
		printf("#%d %d\n", test_case, move());
	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}