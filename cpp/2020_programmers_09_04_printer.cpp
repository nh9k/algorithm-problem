#include <string>
#include <vector>
#include <iostream>
using namespace std;


int solution(vector<int> priorities, int location) {
	int answer = 0;

	while (1) {
		int find_max = 0;
		for (int i = 1; i < priorities.size(); ++i)
		{
			if (find_max < priorities[i])
			{
				find_max = priorities[i];
			}
		}

		if (priorities.front() < find_max) {
			priorities.push_back(priorities.front());
			if (location == 0)
				location = priorities.size() - 1;	
		}
		else //print
		{
			answer += 1;
			if (location == 0)
				return answer;
		}
		location -= 1;
		priorities.erase(priorities.begin());
	}


	return answer;
}

int main(void) {
	cout << solution({ 1,1,9,1,1,1 }, 0);
}