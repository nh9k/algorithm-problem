//���� ��ȣ	���̵�	����	���	�޸�	�ð�	���	�ڵ� ����	������ �ð�
//26855047	nh9k	14890	�¾ҽ��ϴ�!!2056	0	C++17 / ����	1528
//����
//Ǯ�� �ð� ��������
//������ Ǯ���� �˰��� ����� ����� Ǯ��
//���� ����, ���� ���� �˰��� �����ϴ� �Ǽ� ����
//�������� �������� ����ϰ��, ��ٸ��� ���Ҵµ� ������ ��쵵 �����Ƿ� üũ�ϴ� �κ� ����!

#include <iostream>
using namespace std;

int map[101][101];
int L, N, cnt;
//int mem;
//
//void memfunc(int pass)
//{
//	if (mem != pass)
//	{
//		cout << 0;
//	}
//	else
//		cout << 1;
//	mem = pass;
//}

int main() {
	cin >> N >> L;
	for (int ni = 0; ni < N; ++ni) {
		for (int nj = 0; nj < N; ++nj) {
			cin >> map[ni][nj];
		}
	}

	int pass = 2*N;
	//mem = 2 * N;

	for (int ni = 0; ni < N; ++ni) {
		cnt = 1;
		for (int nj = 1; nj < N; ++nj) {
			cnt++;

			if ((map[ni][nj - 1] + 1) == map[ni][nj]) //up
			{
				cnt -= L;
				if (cnt <= 0) {
					pass -= 1;
					cnt = 1;
					break;
				}
			}
			else if ((map[ni][nj - 1] - 1) == map[ni][nj]) //down
			{
				if (cnt <= 0) {
					pass -= 1;
					cnt = 1;
					break;
				}
				cnt = 0;
				cnt -= (L - 1);
			}
			else if (map[ni][nj - 1] != map[ni][nj])
			{
				pass -= 1;
				cnt = 1;
				break;
			}

		}
		if (cnt < 0) {
			pass -= 1;
		}
		//memfunc(pass);
	}

	//cout << endl;
	for (int nj = 0; nj < N; ++nj) {
		cnt = 1;
		for (int ni = 1; ni < N; ++ni) {
			cnt++;

			if ((map[ni - 1][nj] + 1) == map[ni][nj]) //up
			{
				cnt -= L;
				if (cnt <= 0) {
					pass -= 1;
					cnt = 1;
					break;
				}
			}
			else if ((map[ni - 1][nj] - 1) == map[ni][nj]) //down
			{
				if (cnt <= 0) {
					pass -= 1;
					cnt = 1;
					break;
				}
				cnt = 0;
				cnt -= (L - 1);
			}
			else if (map[ni - 1][nj] != map[ni][nj])
			{
				pass -= 1;
				cnt = 1;
				break;
			}
		}
		if (cnt < 0) {
			pass -= 1;
		}

		//memfunc(pass);
	}

	cout << pass << endl;
	return 0;
}
