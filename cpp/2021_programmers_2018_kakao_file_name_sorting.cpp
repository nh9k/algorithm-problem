//python 으로 짜면 더짧게 가능
//참고: https://github.com/thisisiron/Algorithm/blob/master/Programmers/kakao_blind/2018/3_file_name.py

#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;
typedef struct {
	string head;
	int number;
	int idx;
}my_file;

struct cmp {
	bool operator()(my_file &file_a, my_file &file_b) {
		if (file_a.head == file_b.head) {
			if (file_a.number == file_b.number) {
				return file_a.idx > file_b.idx;
			}
			else
				return file_a.number > file_b.number;
		}
		else
			return file_a.head > file_b.head;
	}
};


vector<string> solution(vector<string> files) {
	priority_queue<my_file, vector<my_file>, cmp> my_files;

	for (int i = 0; i < files.size(); ++i) {
		int start_num = 0;
		string head = "";
		string num = "";

		int check_size = my_files.size();
		for (int j = 0; j < files[i].size(); ++j) {
			if (files[i][j] >= '0' && files[i][j] <= '9') { //number
				if (start_num == 0) start_num = 1;
				num += files[i][j];
			}
			else if (start_num == 0) {//head
				head += toupper(files[i][j]);
			}
			else { //tail
				my_files.push({ head, stoi(num), i });
				break;
			}
		}
		if (check_size == my_files.size()) //실수
			my_files.push({ head, stoi(num), i });
	}

	vector<string> answer;
	while (!my_files.empty())
	{
		answer.push_back(files[my_files.top().idx]);
		my_files.pop();
	}
	return answer;
}