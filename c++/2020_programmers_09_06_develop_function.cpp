#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
	vector<int> answer;

	for (int i = 0; i < progresses.size(); ++i) {
		speeds[i] = ceil(float(100 - progresses[i]) / float(speeds[i]));
	}

	int mem_val = 0;
	int cnt = 0;
	for (int i = 0; i < speeds.size(); ++i) {
		if (mem_val == 0) {
			mem_val = speeds[i];
			cnt = 1;
		}
		else if(mem_val < speeds[i]) {
			answer.push_back(cnt);
			mem_val = 0;
			--i;
		}
		else {
			cnt++;
		}
	}
	answer.push_back(cnt);
	return answer;
}

int main(void) {
	vector<int> return_val;
	return_val = solution({ 95, 90, 99, 99, 80, 99 }, { 1, 1, 1, 1, 1, 1 });
	for (int i = 0; i < return_val.size(); ++i)
		cout << return_val[i] << endl;
	return 0;
}