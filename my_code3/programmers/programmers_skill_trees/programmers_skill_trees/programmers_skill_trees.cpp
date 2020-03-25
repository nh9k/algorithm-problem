//2020.0326
#include <string>
#include <vector>
#include <iostream>

using namespace std;
int alphabet[26];

int solution(string skill, vector<string> skill_trees) {
	int answer = 0;

	for (int i = 0; i < skill.length(); ++i)
	{
		alphabet[(int)skill[i] - 65] = i + 1;
	}

	for (int sti = 0; sti < skill_trees.size(); ++sti)
	{
		string stree = skill_trees[sti];
		int ski = 1;
		for (int stri = 0; stri < stree.length(); ++stri)
		{
			if (alphabet[(int)stree[stri] - 65] == ski)
				ski++;
			else if(alphabet[(int)stree[stri] - 65] != 0)
			{
				answer--;
				break;
			}
		}
	}

	return skill_trees.size() + answer;
}

int main(void)
{
	cout << solution("CBD", { "BACDE", "CBADF", "AECB", "BDA" });
}