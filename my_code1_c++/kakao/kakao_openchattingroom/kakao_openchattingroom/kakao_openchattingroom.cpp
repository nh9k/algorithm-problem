#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;
typedef struct {
	string id;
	string nick;
}INFO;

vector<string> solution(vector<string> record) {
	map <string, string> user;
	//vector <INFO> user;
	vector<string> answer;

	int idx = record.size();
	//*id와 닉네임 입력하기 & enter 이나 change로 변경되면 닉네임 바꿔주기
	for (int i = 0; i < idx; i++)
	{
		char* tok[3]; //상태, id, 닉네임
		char recordcpy[30];
		strcpy(recordcpy, record[i].c_str()); //char로 복사

		tok[0] = strtok(recordcpy, " ");
		tok[1] = strtok(NULL, " ");

		if (strcmp("Leave", tok[0])) { //Leave이면 닉네임 받지 않음: 즉 enter 이나 change일경우
			tok[2] = strtok(NULL, " "); 
			user[tok[1]] = tok[2];
		}
		//cout << tok[0] <<"	"<< tok[1] << "		" << tok[2] << "	" << endl;
	}

	//reverse(user.begin(), user.end());

	//for (auto j = user.begin(); j != user.end(); j++)// 같은 id는 제거
	//{
	//	for (auto k = user.begin(); k != user.end();)
	//	{
	//		if (j == k) {
	//			k++; continue;
	//		}
	//		if (!(*j).id.compare((*k).id)) //id가 같으면 제거
	//		{
	//			k = user.erase(k);
	//		}
	//		else
	//		{
	//			k++;
	//		}
	//	}
	//}

	//for (auto k = user.begin(); k != user.end(); k++)
	//{
	//	cout << (*k).first << " " << (*k).second << endl;
	//}

	for (int i = 0; i < idx; i++) //한번더 돌면서 enter, leave에 따라 id에 맞는  닉네임을 answer에 넣기
	{
		char* tok[3]; //상태, id, 닉네임
		char recordcpy[30];
		strcpy(recordcpy, record[i].c_str()); //char로 복사

		tok[0] = strtok(recordcpy, " ");
		tok[1] = strtok(NULL, " ");
		string tok1(tok[1]);

		if (strcmp("Leave", tok[0])) //enter 이나 change일경우
		{ 
			if (!strcmp("Enter", tok[0])) //enter 인 경우
			{
				//for (int j = user.size() - 1; j >= 0; j--)
				//{
				//	if (!user[j].id.compare(tok1))
				//	{
						answer.push_back(user[tok1] + "님이 들어왔습니다.");
				//		break;
				//	}
				//}
			}
		}
		else //leave 인경우
		{
			//for (int j = user.size() - 1; j >= 0; j--)
			//{
			//	if (!user[j].id.compare(tok1))
			//	{
					answer.push_back(user[tok1] + "님이 나갔습니다.");
			//		break;
			//	}
			//}
		}
	}
	
	//for (int i = 0; i < answer.size(); i++)
	//	cout << answer[i] << endl;
	return answer;
}

int main()
{
	solution({ "Enter uid1234 Muzi", "Enter uid4567 Prodo","Leave uid1234","Enter uid1234 Prodo","Change uid4567 Ryan" });
}