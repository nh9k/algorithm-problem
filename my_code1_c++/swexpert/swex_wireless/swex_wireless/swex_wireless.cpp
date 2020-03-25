#include<iostream>

using namespace std;

int m, a, tm; //이동시간, bc수, 실시간 이동시간
int a1[101], a2[101]; //사용자 2명의 이동 정보
int dy[5] = { 0,-1,0,1,0 }; //멈춤 상 우 하 좌
int dx[5] = { 0,0,1,0,-1 };
int bcin[2][8], bcidx1, bcidx2;

typedef struct users
{
	int x, y;
}users;
users user[2];

typedef struct ap
{
	int x, y, c, p;
}ap;
ap bc[8];

void dist() //거리를 계산해서 사용자가 어디에 & 몇개에 속하는지 계산하는 함수
{
	user[0].x += dx[a1[tm]];  user[1].x += dx[a2[tm]];
	user[0].y += dy[a1[tm]];  user[1].y += dy[a2[tm]];	
	tm++;

	bcidx1 = 0, bcidx2 = 0;
	for (int i = 0; i < a; i++)
	{
		if (abs(user[0].x - bc[i].x) + abs(user[0].y - bc[i].y) <= bc[i].c) //사용자 1이 bc 안이면
		{
			bcin[0][bcidx1] = i; //bc의 번호를 넣고
			bcidx1++; 
		}
		if (abs(user[1].x - bc[i].x) + abs(user[1].y - bc[i].y) <= bc[i].c)
		{
			bcin[1][bcidx2] = i;
			bcidx2++;
		}			
	}
}

int maxresult() //위치마다 두 사용자가 접속한 bc에서 최댓값 계산하는 함수 + 최댓값의 총합
{
	int maximum=0, present, result = 0;
	for (int i = 0; i < m + 1; i++) // 시간증가, 이동
	{
		dist();
		
		if (bcidx1 == 0 && bcidx2 != 0) //사용자2만 접속한 경우
		{
			maximum = 0;
			for (int k = 0; k < bcidx2; k++) //사용자 2
			{
				 present = bc[bcin[1][k]].p;

				if (maximum < present)
				{
					maximum = present;
				}
			}
		}
		else if (bcidx1 != 0 && bcidx2 == 0) //사용자1만 접속한 경우
		{
			maximum = 0;
			for (int j = 0; j < bcidx1; j++) //사용자 1
			{
				present = bc[bcin[0][j]].p;

				if (maximum < present)
				{
					maximum = present;
				}
			}
		}
		else { //둘다 접속한 경우
			maximum = 0;
			for (int j = 0; j < bcidx1; j++) //사용자 1이 접속한 bc 모두
			{
				for (int k = 0; k < bcidx2; k++) //사용자 2가 접속한 bc 모두
				{
					if (bcin[0][j] == bcin[1][k]) //같은 bc안
					{
						present = bc[bcin[0][j]].p; //같으면 절반씩이므로 그대로 들어감
					}
					else
					{
						present = bc[bcin[0][j]].p + bc[bcin[1][k]].p;
					}
					if (maximum < present)
					{
						maximum = present;
					}
				}
			}
		}
		result += maximum;
	}
	return result;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("sample_input.txt", "r", stdin);
	cin >> T;

	for (test_case = 1; test_case <= T; ++test_case)
	{
		scanf("%d %d", &m, &a);

		a1[0] = 0; //처음은 멈춰 있음
		for (int i = 1; i < m+1; i++)
			scanf("%d", &a1[i]);

		a2[0] = 0;
		for (int i = 1; i < m+1; i++)
			scanf("%d", &a2[i]);

		for (int i = 0; i < a; i++)
			scanf("%d %d %d %d", &bc[i].x, &bc[i].y, &bc[i].c, &bc[i].p);

		user[0].x = 1; user[0].y = 1;  //사용자 1 처음 시작
		user[1].x = 10; user[1].y = 10; //사용자 2 처음 시작
		tm = 0; //사용자 움직임 시간

		printf("#%d %d\n", test_case, maxresult());
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}