/*
����: ����9461, �ĵ��ݼ���
N=100�� ��� OVERFLOW, s[100]�� ���� longlong�� ����
ä�� ��ȣ	���̵�	���� ��ȣ	���	�޸�	�ð�	���	�ڵ� ����
19545394	nh9k	9461	�¾ҽ��ϴ�!!1984	4	C++14 / ����	369
*/

#include <iostream>
long long s[101]; //sequence  //��������:s[0] = 0

int main()
{
	int T, N;
	std::cin >> T;

	s[1] = 1;
	s[2] = 1;
	for (int c = 0; c < T; ++c)
	{
		std::cin >> N;

		if (s[N] != 0) {
			std::cout << s[N] << std::endl;
		}
		else {
			for (int i = 3; i <= N; ++i) {
				s[i] = s[i - 3] + s[i - 2];
			}
			std::cout << s[N] << std::endl;
		}
	}
}