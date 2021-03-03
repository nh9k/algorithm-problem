#include <string>
#include <iostream>
using namespace std;

char calstr1[1000][2], calstr2[1000][2];
int ckvisit2[1000];
int csz1, csz2;

int and_oper()
{
	int result = 0;
	for (int i = 0; i < csz1;i++)
	{
		for (int j = 0; j < csz2; j++)
		{
			if (ckvisit2[j] == true) continue;
			if (calstr1[i][0] == calstr2[j][0] && calstr1[i][1] == calstr2[j][1])
			{
				result++;
				ckvisit2[j] = true;
				break;
			}
		}
	}
	return result;
}

int solution(string str1, string str2) {
	int ssz1 = str1.length();
	int ssz2 = str2.length();
	csz1 = 0, csz2 = 0;
	for (int i = 1; i < ssz1; i++)
	{
		if (!(('a' <= str1[i - 1] && str1[i - 1] <= 'z') || ('A' <= str1[i - 1] && str1[i - 1] <= 'Z'))) continue;
		if (!(('a' <= str1[i] && str1[i] <= 'z') || ('A' <= str1[i] && str1[i] <= 'Z'))) continue;
		if ('A' <= str1[i - 1] && str1[i - 1] <= 'Z') {//대문자이면 소문자로 바꾸기
			str1[i - 1] = str1[i - 1] - 'A' + 'a';
		}
		if ('A' <= str1[i] && str1[i] <= 'Z') {//대문자이면 소문자로 바꾸기
			str1[i] = str1[i] - 'A' + 'a';
		}

		calstr1[csz1][0] = str1[i - 1];
		calstr1[csz1][1] = str1[i];
		//printf("%c%c ", calstr1[csz1][0], calstr1[csz1][1]);
		csz1++;	
	}
	//printf("\n");
	for (int i = 1; i < ssz2; i++)
	{
		if (!(('a' <= str2[i - 1] && str2[i - 1] <= 'z') || ('A' <= str2[i - 1] && str2[i - 1] <= 'Z'))) continue;
		if (!(('a' <= str2[i] && str2[i] <= 'z') || ('A' <= str2[i] && str2[i] <= 'Z'))) continue;
		if ('A' <= str2[i - 1] && str2[i - 1] <= 'Z') {//대문자이면 소문자로 바꾸기
			str2[i - 1] = str2[i - 1] - 'A' + 'a';
		}
		if ('A' <= str2[i] && str2[i] <= 'Z') {//대문자이면 소문자로 바꾸기
			str2[i] = str2[i] - 'A' + 'a';
		}

		calstr2[csz2][0] = str2[i - 1];
		calstr2[csz2][1] = str2[i];
		//printf("%c%c ", calstr2[csz2][0], calstr2[csz2][1]);
		csz2++;
	}

	float andoper = and_oper();
	float oroper = csz1 + csz2 - andoper;
	printf("%f %f\n", andoper, oroper);
	if (andoper == 0 || oroper == 0) {
		for (int i = 0; i < str1.size(); i++)
		{
			str1[i] = toupper(str1[i]); //소문자를 대문자로 교환.
		}
		for (int i = 0; i < str2.size(); i++)
		{
			str2[i] = toupper(str2[i]); //소문자를 대문자로 교환.
		}
		if (str1.compare(str2) == 0) return 65536;
		else return 0;
	}
	int answer = andoper / oroper * 65536;	
	return answer;
}

int main()
{
	printf("%d", solution("E=M*C^2", "e=m*c^2"));
	return 0;
}