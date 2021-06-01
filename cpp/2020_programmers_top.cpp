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


//채점을 시작합니다.
//정확성  테스트
//테스트 1 〉	통과(0.00ms, 3.91MB)
//테스트 2 〉	통과(0.01ms, 3.9MB)
//테스트 3 〉	통과(0.01ms, 3.74MB)
//테스트 4 〉	통과(0.01ms, 3.88MB)
//테스트 5 〉	통과(0.00ms, 3.89MB)
//테스트 6 〉	통과(0.00ms, 3.75MB)
//테스트 7 〉	통과(0.01ms, 3.77MB)
//테스트 8 〉	통과(0.01ms, 3.75MB)
//채점 결과
//정확성 : 100.0
//	합계 : 100.0 / 100.0