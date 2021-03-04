//���� ��ȣ	���̵�	����	���	�޸�	�ð�	���	�ڵ� ����	������ �ð�
//26969914	nh9k	20055	�¾ҽ��ϴ�!!2016	56	C++17 / ����	1051
//Ǯ�� �ð�: 44��
//���� ���趧�� 20�и��� Ǯ���� �����̳�, �� �ʰ� Ǯ�Ե� ������,
//1. �����̾� ��Ʈ�� �̵��� ��, �κ��� �Բ� �̵��ϴ� ���� Ȯ�������� �ʾƼ�
//2. �����̾� ��Ʈ��  �̵��� ��, �κ��� �Բ� �̵���Ű�� ù��° �ڸ��� �κ��� false�� �־��ִ� ��


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector <int> belt;
int N, K;
bool robot[101];

int detectK() {
	int cnt = 0;
	for (int i = 0; i < belt.size(); ++i) {
		if (belt[i] == 0)
		{
			cnt++;
		}
	}
	if (cnt >= K)
		return true;
	return false;
}

int main()
{
	cin >> N >> K;
	int tmp;
	for (int i = 0; i < (N * 2); ++i) {
		cin >> tmp;
		belt.push_back(tmp);
	}

	int step = 0;
	while (!detectK())
	{

		rotate(belt.rbegin(), belt.rbegin() + 1, belt.rend());
		for (int i = N - 1; i > 0; --i) {
			robot[i] = robot[i - 1];
		}
		robot[0] = false;

		for (int i = N - 1; i >= 0; --i) {
			if (robot[i] && (i == N - 1)) {
				robot[i] = false;
				continue;
			}
			if ((robot[i + 1] == false) && (robot[i]) && (belt[i+1] > 0))
			{
				robot[i + 1] = true;
				belt[i + 1] -= 1;
				robot[i] = false;

				if ((i + 1) == (N - 1))
				{
					robot[i + 1] = false;
				}
			}
		}

		if ((robot[0] == false) && (belt[0] > 0))
		{
			robot[0] = true;
			belt[0] -= 1;
		}

		step++;
	}

	cout << step;
	return 0;
}