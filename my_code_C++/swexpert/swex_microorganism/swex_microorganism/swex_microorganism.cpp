#include <iostream>  //0.00678s // 참고: https://2youngjae.tistory.com/139
#include <vector>

using namespace std;

int n, m, k;
int maxnum, maxdir, sumnum;
int mx[5] = { 0,-1,1,0,0 };
int my[5] = { 0,0,0,-1,1 };
vector<vector<int>> gunzip, map;

void scaning() //세로위치0, 가로위치1, 미생물 수2, 이동방향3
{
	map.assign(n, vector<int>(n, 0));

	for (int i = 0; i < k; i++) //군집의 위치 갱신
	{
		if (gunzip[i][2] != 0) { //미생물을 0으로 한 것은 더이상 이동시키지 말기 !!! 건들지 말기
			gunzip[i][0] += mx[gunzip[i][3]];
			gunzip[i][1] += my[gunzip[i][3]];
			map[gunzip[i][0]][gunzip[i][1]] += 1;
		}
	}

	for (int i = 0; i < k; i++)
	{
		if (gunzip[i][2] != 0) //미생물이 0이 아닌 것만 확인 한다.
		{
			if (gunzip[i][0] >= 1 && gunzip[i][0] <= n - 2 && gunzip[i][1] >= 1 && gunzip[i][1] <= n - 2) //이동 후 테두리가 아닌 경우 
			{
				//같으면 합치는 코드
				//미생물 합치고, 가장 큰 것 따라 방향 갱신, 나머지는 미생물 0
				if (map[gunzip[i][0]][gunzip[i][1]] > 1) //군집이 합쳐지는 경우
				{
					maxnum = 0; maxdir = 0; sumnum = 0;
					for (int j = 0; j < k; j++) //최대 군집을 찾기 위한 for문
					{
						if (gunzip[j][0] == gunzip[i][0] && gunzip[j][1] == gunzip[i][1]) //map에 여러개 있는 군집의 위치와 같을 경우
						{
							sumnum += gunzip[j][2]; //군집을 합침
							if (maxnum < gunzip[j][2])
							{
								maxnum = gunzip[j][2]; //최대 군집을 찾음
								maxdir = gunzip[j][3];
							}
						}
					}
					for (int j = 0; j < k; j++) //최대 군집 외에 나머지는 소멸하기 위한 for문
					{
						if (gunzip[j][0] == gunzip[i][0] && gunzip[j][1] == gunzip[i][1]) //map에 여러개 있는 군집의 위치와 같을 경우
						{
							if (maxnum != gunzip[j][2])
							{
								gunzip[j][2] = 0; //군집 소멸
							}
							else
							{
								gunzip[j][2] = sumnum;
								gunzip[j][3] = maxdir;
							}
						}
					}
				}
			}
			else if (gunzip[i][0] >= 0 && gunzip[i][0] <= n - 1 && gunzip[i][1] >= 0 && gunzip[i][1] <= n - 1) //이동 후 테두리인 경우
			{
				//gunzip[i][2] = floor(float(gunzip[i][2]) / 2.0); // 미생물 수 갱신 //1일 때 0 되는지 보기
				gunzip[i][2] = gunzip[i][2] / 2;
				if (gunzip[i][3] == 1) gunzip[i][3] = 2; //방향 갱신
				else if (gunzip[i][3] == 2) gunzip[i][3] = 1;
				else if (gunzip[i][3] == 3) gunzip[i][3] = 4;
				else if (gunzip[i][3] == 4) gunzip[i][3] = 3;
			}
		}
	}
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
	{
		scanf("%d %d %d", &n, &m, &k);

		gunzip.assign(k, vector<int>(4, 0));
		for (int j = 0; j < k; j++)
			scanf("%d %d %d %d", &gunzip[j][0], &gunzip[j][1], &gunzip[j][2], &gunzip[j][3]);

		for (int j = 0; j < m; j++) //시간 동안
			scaning();

		int ans = 0;
		for (int j = 0; j < k; j++)
			ans += gunzip[j][2];

		printf("#%d %d\n", i + 1, ans);
	}
	return 0;
}