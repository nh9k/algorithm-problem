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
	//*id�� �г��� �Է��ϱ� & enter �̳� change�� ����Ǹ� �г��� �ٲ��ֱ�
	for (int i = 0; i < idx; i++)
	{
		char* tok[3]; //����, id, �г���
		char recordcpy[30];
		strcpy(recordcpy, record[i].c_str()); //char�� ����

		tok[0] = strtok(recordcpy, " ");
		tok[1] = strtok(NULL, " ");

		if (strcmp("Leave", tok[0])) { //Leave�̸� �г��� ���� ����: �� enter �̳� change�ϰ��
			tok[2] = strtok(NULL, " "); 
			user[tok[1]] = tok[2];
		}
		//cout << tok[0] <<"	"<< tok[1] << "		" << tok[2] << "	" << endl;
	}

	//reverse(user.begin(), user.end());

	//for (auto j = user.begin(); j != user.end(); j++)// ���� id�� ����
	//{
	//	for (auto k = user.begin(); k != user.end();)
	//	{
	//		if (j == k) {
	//			k++; continue;
	//		}
	//		if (!(*j).id.compare((*k).id)) //id�� ������ ����
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

	for (int i = 0; i < idx; i++) //�ѹ��� ���鼭 enter, leave�� ���� id�� �´�  �г����� answer�� �ֱ�
	{
		char* tok[3]; //����, id, �г���
		char recordcpy[30];
		strcpy(recordcpy, record[i].c_str()); //char�� ����

		tok[0] = strtok(recordcpy, " ");
		tok[1] = strtok(NULL, " ");
		string tok1(tok[1]);

		if (strcmp("Leave", tok[0])) //enter �̳� change�ϰ��
		{ 
			if (!strcmp("Enter", tok[0])) //enter �� ���
			{
				//for (int j = user.size() - 1; j >= 0; j--)
				//{
				//	if (!user[j].id.compare(tok1))
				//	{
						answer.push_back(user[tok1] + "���� ���Խ��ϴ�.");
				//		break;
				//	}
				//}
			}
		}
		else //leave �ΰ��
		{
			//for (int j = user.size() - 1; j >= 0; j--)
			//{
			//	if (!user[j].id.compare(tok1))
			//	{
					answer.push_back(user[tok1] + "���� �������ϴ�.");
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