#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> heights) {
	vector<int> answer(heights.size());

	for (int vsz = heights.size() - 1; vsz > 0; --vsz)
	{
		for (int vi = vsz - 1; vi >= 0; --vi)
		{
			if (heights[vi] > heights[vsz])
			{
				answer[vsz] = vi + 1;
				break;
			}
			if (vi == 0 && (heights[vi] < heights[vsz]))
			{
				answer[vsz] = 0;
			}
		}
	}
	answer[0] = 0;

	return answer;
}


//ä���� �����մϴ�.
//��Ȯ��  �׽�Ʈ
//�׽�Ʈ 1 ��	���(0.00ms, 3.91MB)
//�׽�Ʈ 2 ��	���(0.01ms, 3.9MB)
//�׽�Ʈ 3 ��	���(0.01ms, 3.74MB)
//�׽�Ʈ 4 ��	���(0.01ms, 3.88MB)
//�׽�Ʈ 5 ��	���(0.00ms, 3.89MB)
//�׽�Ʈ 6 ��	���(0.00ms, 3.75MB)
//�׽�Ʈ 7 ��	���(0.01ms, 3.77MB)
//�׽�Ʈ 8 ��	���(0.01ms, 3.75MB)
//ä�� ���
//��Ȯ�� : 100.0
//	�հ� : 100.0 / 100.0