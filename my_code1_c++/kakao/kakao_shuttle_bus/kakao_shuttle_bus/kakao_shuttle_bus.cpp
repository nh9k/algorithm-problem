#include <string>
#include <vector>
#include <queue>
#include <cstring> //까먹지 말기
#include <iostream>
using namespace std;

string solution(int n, int t, int m, vector<string> timetable) {
	//*input
	priority_queue <int, vector<int>, greater<int>> pq;
	int vsz = timetable.size();
	for(int i=0; i<vsz; i++)
	{
		char cpy[6];
		strcpy(cpy, timetable[i].c_str());

		char *split = strtok(cpy, ":"); //시
		int present = stoi(split) * 100;

		split = strtok(NULL, " ");//분
		present += stoi(split);

		printf("%dㅎㅎ\n", present);
		pq.push(present);
	}
	//*
	int temp = 0, lastm = 0, lastni = 0;
	for (int ni = 1; ni <= n; ni++)
	{
		if (pq.empty())
			break;
		
		int timeni = (ni - 1)*t; //시간 계산1
		//0:01~09:00 + //09:01~
		if (timeni >= 60) { //시간 계산1-1
			int temp2 = timeni / 60;
			timeni %= 60;
			timeni += temp2 * 100;
		}

		for (int p = 1; p <= m; p++)
		{
			if (pq.empty()) 
				break;			
			temp = pq.top();

			if (temp <= 900 + timeni)
			{
				lastni = ni;
				lastm = p;
				pq.pop();
			}
			else //더이상 탈사람이 없음
			{
				break;
			}
		}
	}
	//마지막으로 저장한 temp가 마지막 사람, lastm이 마지막 사람의 순서
	if (lastm < m || lastni < n) //콘이 마지막으로 타면됨
	{
		int timeni = (n - 1)*t;
		if (timeni >= 60) {
			int temp2 = timeni / 60; //시각
			timeni %= 60; //분
			timeni += temp2 * 100;
		}
		temp = 900 + timeni; //마지막 출근 버스 시간
	}
	else if (lastm == m) //콘이 마지막 사람보다 일찍 타야함
	{
		if (temp % 100 == 0) //시간이 정각이면
		{
			temp = temp - 100 + 59;
		}
		else 
		{
			temp = temp - 1; //1분 일찍타야함
		}
	}
	
	//*int형을 string 형식으로
	printf("%d\n", temp);
	string answer;
	if (temp > 959)
	{
		int floating = temp % 100; //분
		temp /= 100; //시
		if(floating<10)
			answer = to_string(temp) + ":0" + to_string(floating);
		else
			answer = to_string(temp) + ":" + to_string(floating);
	}
	else
	{
		int floating = temp % 100; //분
		temp /= 100; //시
		if (floating < 10)
			answer = "0" + to_string(temp) + ":0" + to_string(floating);
		else
			answer =  "0" + to_string(temp) + ":" + to_string(floating);
	}
	cout << answer << endl;
	return answer;
}

int main()
{
	solution(1, 1, 5, { "08:00", "08:01", "08:02", "08:03"});
	solution(2, 10, 2, { "09:10", "09:09", "08:00" });
	return 0;
}