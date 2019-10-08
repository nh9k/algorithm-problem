#include <iostream>
#include <vector>
using namespace std;

int n, x;
int map[20][20];
int map2[20][20];

int scanner()
{
	int mem, sum = 0;
	int cnt, f1, ff;
	for (int i = 0; i < n; i++) //세로로 스캔
	{
		mem = map[0][i];
		f1 = 0, ff = 0; //얘네 언제 초기화 할지 고민
		cnt = 0;
		for (int j = 0; j < n; j++)
		{
			if (mem == map[j][i])
			{
				cnt++;
				if (f1 == 1)
				{
					if (cnt >= x) {
						ff = 1;
						f1 = 0; cnt = 0;
					}
				}
				if (cnt == n) ff = 1;
			}
			else
			{
				if (mem > map[j][i] && mem <= map[j][i] + 1) //다음이 작은 수 일때 //두개 작은 수이면 실패임.
				{
					if (f1 == 1) //하강 경사로 설치하려 했으나 또 하강일때
					{
						ff = 0; break;
					}
					else f1 = 1; ///처음으로 작은 수가 나왔을 때
				}
				else if (mem < map[j][i] && mem >= map[j][i] - 1) //다음이 큰 수 일때 //두개 큰수이면 실패임.
				{
					if (f1 == 1) { //하강 경사로 설치하려 했으나 상승일때 
						ff = 0; break;
					}
					else if (cnt >= x)
					{
						if (j - x - 1 < 0) ff = 1; //배열 밖이면
						else {					   //배열 안이면
							if (map[j - x - 1][i] == map[j - x][i])
							{
								ff = 1; map[j - 1][i] = map[j][i]; //경사로 설치
							}
						}
					}
					else //연속으로 큰수가 나올때
					{
						ff = 0;
						break;
					}
				}
				else { //두개 이상 띄워질 경우
					ff = 0;
					break;
				}
				cnt = 1;
				mem = map[j][i];
			}
		}
		if (f1 == 1) ff = 0;
		if (ff == 1) {
			//printf("1");
			sum += 1;
		}
		//else
			//printf("0");
	}
	//printf("세로:: %d    ", sum);

	for (int i = 0; i < n; i++) //가로로 스캔.
	{
		mem = map2[i][0];
		f1 = 0, ff = 0; //얘네 언제 초기화 할지 고민
		cnt = 0;
		//printf("i::%d\n", i);
		for (int j = 0; j < n; j++)
		{
			if (mem == map2[i][j])
			{
				cnt++;
				if (f1 == 1)
				{
					if (cnt >= x) {
						ff = 1;
						f1 = 0; cnt = 0;
					}
				}
				if (cnt == n) ff = 1;
			}
			else
			{
				if (mem > map2[i][j] && mem <= map2[i][j] + 1) //다음이 작은 수 일때 //두개 작은 수이면 실패임.
				{
					if (f1 == 1) { // 하강 경사로 설치해야하는 데 연속이 아닌 경우
						ff = 0;
						break;
					}
					else f1 = 1; ///처음으로 작은 수가 나왔을 때
				}
				else if (mem < map2[i][j] && mem >= map2[i][j] - 1) //다음이 큰 수 일때 //두개 큰수이면 실패임.
				{
					if (f1 == 1) { //하강 경사로 설치하려 했으나 상승일때 
						ff = 0; break;
					}
					else if (cnt >= x)
					{
						if (j - x - 1 < 0) ff = 1; //배열 밖이면
						else {					   //배열 안이면
							if (map2[i][j - x - 1] == map2[i][j - x])
							{
								ff = 1; map2[i][j - 1] = map2[i][j];
							}
						}
					}
					else //연속으로 큰수가 나올때
					{
						ff = 0;
						break;
					}
				}
				else { //두개 이상 띄워질 경우 고려해야 함
					ff = 0;
					break;
				}
				cnt = 1;
				mem = map2[i][j];
			}
		}
		if (f1 == 1) ff = 0;
		if (ff == 1) {
			//printf("1");
			sum += 1;
		}
		//else
			//printf("0");
	}
	//printf("가로:: %d    ", sum);

	return sum;
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
	{
		scanf("%d %d", &n, &x);

		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
			{
				scanf("%d", &map[j][k]);
				map2[j][k] = map[j][k];
			}

		//visit.assign(n, 0);
		printf("#%d %d\n", i + 1, scanner());
	}
	return 0;
}