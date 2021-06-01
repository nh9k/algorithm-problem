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

int calresult() //초당 최대처리량을 계산하는 함수
{
	int temp1, max_num = 0;
	//minitemp = 2001;
	for (auto during = timelist.begin(); during != timelist.end(); during++) //시간 초과가 나는 이유 때문에 시작점과 끝점만 리스트로 만들어 체크
	{ //어차피 값이 변하는 구간은 시작점 아니면 끝점밖에 없음
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
		//* 입력을 unsigned int 형으로 변환
		int hours = stoi(lines[i].substr(11, 2)); //12~13자리 첫번째는 0부터시작
		int mins = stoi(lines[i].substr(14, 2));
		int secs = stoi(lines[i].substr(17, 2)); //float으로 받을 경우 제대로 안받아짐: msec따로 받음
		int msecs = stoi(lines[i].substr(20, 3)); //ex. 4.002 -> 4.001999 ->(int) -> 4.001
		string s_traffic = lines[i].substr(24);
		//cout << hours << " " << mins << " " << secs << " " << s_traffic << endl;

		char c_traffic[7]; //7사이즈로 할 것: 조심!
		strcpy(c_traffic, s_traffic.c_str());
		char *tok = strtok(c_traffic, "s");
		float f_traffic = stof(tok);

		//* 끝시간을 계산하면 -> msec로 환산: 제대로 하지 않으면 정답 안나옴!
		//왜 환산하냐, 시분초를 증가시키고 뺄때 하나하나 계산하면 복잡하고 오래걸림 msec로 사용시 편하게 가능 
		traffic[tidx][1] = (hours * 3600)*sec + (mins * 60)*sec + secs * sec + msecs; //끝 시간

		//* 트래픽 시작시간 계산
		traffic[tidx][0] = traffic[tidx][1] - (int)(f_traffic * sec) + 1; //시작 시간
		if (traffic[tidx][0] > 24 * hour) traffic[tidx][0] = 0; //unsigned int는 음수 없음 -> 이것 때문에 계속 59.1점 맞음..

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