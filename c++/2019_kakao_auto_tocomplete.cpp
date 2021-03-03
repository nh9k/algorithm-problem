#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

int solution(vector<string> words) {
	sort(words.begin(), words.end());

	int temp = 1, answer = 0;
	for (int i = 0; i < words.size(); ++i)
	{
		if (i == 0)
		{
			for (int k = 0; k < min(words[i].length(), words[i + 1].length()); ++k)
			{
				if (words[i][k] == words[i + 1][k])
					++temp;
				else
					break;
			}
			if (temp > words[i].length())
			{
				--temp;
			}
		}
		else if (i == words.size() - 1)
		{
			for (int k = 0; k < min(words[i].length(), words[i - 1].length()); ++k)
			{
				if (words[i][k] == words[i - 1][k])
					++temp;
				else
					break;
			}
			if (temp > words[i].length())
			{
				--temp;
			}
		}
		else
		{
			int temp2 = 1;
			for (int k = 0; k < min(words[i].length(), words[i - 1].length()); ++k)
			{
				if (words[i][k] == words[i - 1][k])
					++temp;
				else
					break;
			}
			if (temp > words[i].length())
			{
				--temp;
			}
			for (int k = 0; k < min(words[i].length(), words[i + 1].length()); ++k)
			{
				if (words[i][k] == words[i + 1][k])
					++temp2;
				else
					break;
			}
			if (temp2 > words[i].length())
			{
				--temp2;
			}

			if (temp < temp2)
				temp = temp2;
		}

		cout << temp << endl;
		answer += temp;
		temp = 1;
	}
	return answer;
}

int main()
{
	cout << solution({ "go", "gone", "guild" }) << endl << endl;
	cout << solution({ "abc", "def", "ghi" , "jklm" }) << endl << endl;
	cout << solution({ "word", "war", "warrior","world" }) << endl << endl;
}