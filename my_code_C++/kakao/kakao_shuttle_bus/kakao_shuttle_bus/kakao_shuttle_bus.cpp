#include <string>
#include <vector>
#include <queue>
#include <cstring> //����� ����
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

		char *split = strtok(cpy, ":"); //��
		int present = stoi(split) * 100;

		split = strtok(NULL, " ");//��
		present += stoi(split);

		printf("%d����\n", present);
		pq.push(present);
	}
	//*
	int temp = 0, lastm = 0, lastni = 0;
	for (int ni = 1; ni <= n; ni++)
	{
		if (pq.empty())
			break;
		
		int timeni = (ni - 1)*t; //�ð� ���1
		//0:01~09:00 + //09:01~
		if (timeni >= 60) { //�ð� ���1-1
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
			else //���̻� Ż����� ����
			{
				break;
			}
		}
	}
	//���������� ������ temp�� ������ ���, lastm�� ������ ����� ����
	if (lastm < m || lastni < n) //���� ���������� Ÿ���
	{
		int timeni = (n - 1)*t;
		if (timeni >= 60) {
			int temp2 = timeni / 60; //�ð�
			timeni %= 60; //��
			timeni += temp2 * 100;
		}
		temp = 900 + timeni; //������ ��� ���� �ð�
	}
	else if (lastm == m) //���� ������ ������� ���� Ÿ����
	{
		if (temp % 100 == 0) //�ð��� �����̸�
		{
			temp = temp - 100 + 59;
		}
		else 
		{
			temp = temp - 1; //1�� ����Ÿ����
		}
	}
	
	//*int���� string ��������
	printf("%d\n", temp);
	string answer;
	if (temp > 959)
	{
		int floating = temp % 100; //��
		temp /= 100; //��
		if(floating<10)
			answer = to_string(temp) + ":0" + to_string(floating);
		else
			answer = to_string(temp) + ":" + to_string(floating);
	}
	else
	{
		int floating = temp % 100; //��
		temp /= 100; //��
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