#include <iostream>
//#include <sstream>
#include <string>
#include <vector>
#include <cstring>

#define sec 1000
#define hour 10000000

using namespace std;
unsigned int traffic[2000][2];// , minitime, maxitime;// , minitemp;
vector <unsigned int> timelist;
int tidx;

int checking(unsigned int first, unsigned int last)
{
	int temp2 = 0;
	for (int idx = 0; idx < tidx; idx++) {
		if (!(traffic[idx][1] < first || traffic[idx][0] > last))
		{
			temp2++;
			//if (minitemp < temp2) return 0;
		}

	}
	//if (minitemp > temp2)
	//{
	//	minitemp = temp2;
	//}
	return temp2;
}

int calresult() //�ʴ� �ִ�ó������ ����ϴ� �Լ�
{
	int temp1, max_num = 0;
	//minitemp = 2001;
	for (auto during = timelist.begin(); during != timelist.end(); during++) //�ð� �ʰ��� ���� ���� ������ �������� ������ ����Ʈ�� ����� üũ
	{ //������ ���� ���ϴ� ������ ������ �ƴϸ� �����ۿ� ����
		temp1 = checking(*during, *during + sec - 1);
		if (temp1) {
			if (max_num < temp1)
				max_num = temp1;
		}
	}
	return max_num;
}

int solution(vector<string> lines) {

	int vsz = lines.size();
	tidx = 0;
	//minitime = 24 * hour;
	//maxitime = 0;
	for (int i = 0; i < vsz; i++)
	{
		//* �Է��� unsigned int ������ ��ȯ
		int hours = stoi(lines[i].substr(11, 2)); //12~13�ڸ� ù��°�� 0���ͽ���
		int mins = stoi(lines[i].substr(14, 2));
		int secs = stoi(lines[i].substr(17, 2)); //float���� ���� ��� ����� �ȹ޾���: msec���� ����
		int msecs = stoi(lines[i].substr(20, 3)); //ex. 4.002 -> 4.001999 ->(int) -> 4.001
		string s_traffic = lines[i].substr(24);
		//cout << hours << " " << mins << " " << secs << " " << s_traffic << endl;

		char c_traffic[7]; //7������� �� ��: ����!
		strcpy(c_traffic, s_traffic.c_str());
		char *tok = strtok(c_traffic, "s");
		float f_traffic = stof(tok);

		//* ���ð��� ����ϸ� -> msec�� ȯ��: ����� ���� ������ ���� �ȳ���!
		//�� ȯ���ϳ�, �ú��ʸ� ������Ű�� ���� �ϳ��ϳ� ����ϸ� �����ϰ� �����ɸ� msec�� ���� ���ϰ� ���� 
		traffic[tidx][1] = (hours * 3600)*sec + (mins * 60)*sec + secs * sec + msecs; //�� �ð�

		//* Ʈ���� ���۽ð� ���
		traffic[tidx][0] = traffic[tidx][1] - (int)(f_traffic * sec) + 1; //���� �ð�
		if (traffic[tidx][0] > 24 * hour) traffic[tidx][0] = 0; //unsigned int�� ���� ���� -> �̰� ������ ��� 59.1�� ����..

		timelist.push_back(traffic[tidx][0]);
		timelist.push_back(traffic[tidx][1]);
		tidx++;
	}
	return calresult();
}

int main()
{
	printf("%d\n", solution({ "2016-09-15 00:00:00.000 3s" }));
	printf("%d\n", solution({ "2016-09-15 01:00:04.001 2.0s", "2016-09-15 01:00:07.000 2s" }));

	printf("%d\n", solution({ "2016-09-15 01:00:04.002 2.0s", "2016-09-15 01:00:07.000 2s" }));

	printf("%d\n", solution({
		"2016-09-15 20:59:57.421 0.351s",
		"2016-09-15 20:59:58.233 1.181s",
		"2016-09-15 20:59:58.299 0.8s",
		"2016-09-15 20:59:58.688 1.041s",
		"2016-09-15 20:59:59.591 1.412s",
		"2016-09-15 21:00:00.464 1.466s",
		"2016-09-15 21:00:00.741 1.581s",
		"2016-09-15 21:00:00.748 2.31s",
		"2016-09-15 21:00:00.966 0.381s",
		"2016-09-15 21:00:02.066 2.62s"
		}));

	return 0;
}