/*
@nh9k
1) 4중 for문으로 x, y, d1, d2 설정
2) 5선거구 경계선 설정
3) 나머지 선거구 합 구하기
  배열에서 y에 대해 양쪽에서 중심으로 이동하면서 5선거구 경계에 닿으면 break
  5선거구는 처음에 배열 입력시 인구수 총합 구해서 (인구수 총합) - (나머지 선거구 합) => 5선거구를 제대로 구하지 못해 문제를 틀림
4) 최대, 최소를 구한 후 최대 - 최소가 최소인 수를 result 에 저장

문제         채점 번호	아이디	문제 번호	결과	        메모리	시간	언어	        코드 길이	제출한 시간
백준 17779번 19404549	nh9k	17779	    맞았습니다!!	1984kb	12ms->8ms	C++14 / 수정	3079	    5분 전

문제 이해	코드 작성	디버깅
1시간		1시간		1시간

5선거구 구했던 소스
	for (int i = x; i <= x + d1 + d2; ++i)
	{
		for (int j = y - d1; j <= y + 2; ++j) //여기서 y+2를 왜 했을까.. 2->d2로 하면 정답, 현재 소스와 시간은 불변
		{
			if (checkmap[i][j] == true) continue;
			checkmap[i][j] = true;
			sum[4] += realmap[i][j];
		}
	}
*/

#include <iostream>
using namespace std;

int N;
int realmap[20][20];
bool checkmap[20][20];
int sum[5], allsum;
int result;

//void printmap()
//{
//	for (int i = 0; i < N; ++i)
//	{
//		for (int j = 0; j < N; ++j)
//		{
//			cout << checkmap[i][j];
//		}
//		cout << endl;
//	}
//	cout << endl;
//}

void check5sum(int x, int y, int d1, int d2) //5선거구 경계 설정
{
	for (int i = x, j = y; (i <= x + d1)&&(j >= y - d1); ++i, --j)
	{
		checkmap[i][j] = true;
	}
	for (int i = x, j = y; (i <= x + d2) && (j <= y + d2); ++i, ++j)
	{
		//if (checkmap[i][j] == true) continue; //지우면 4ms 단축(12->8ms)
		checkmap[i][j] = true;
	}
	for (int i = x + d1, j = y - d1; (i <= x + d1 + d2) && (j <= y - d1 + d2); ++i, ++j)
	{
		//if (checkmap[i][j] == true) continue; //지우면 4ms 단축(12->8ms)
		checkmap[i][j] = true;
	}
	for (int i = x + d2, j = y + d2; (i <= x + d1 + d2) && (j >= y +d2 - d1); ++i, --j)
	{
		//if (checkmap[i][j] == true) continue; //지우면 4ms 단축(12->8ms)
		checkmap[i][j] = true;
	}
}

void checkallsum(int x, int y, int d1, int d2) //나머지 선거구 sum 계산
{
	for (int i = 0; i < x + d1; ++i) //1선거구
	{
		for (int j = 0; j <= y; ++j)
		{
			if (checkmap[i][j] == true) break;
			checkmap[i][j] = true;
			sum[0] += realmap[i][j];
		}
	}
	//printmap();
	for (int i = 0; i <= x + d2; ++i) //2선거구
	{
		for (int j = N - 1; j > y; --j)
		{
			if (checkmap[i][j] == true) break;
			checkmap[i][j] = true;
			sum[1] += realmap[i][j];
		}
	}
	//printmap();
	for (int i = x+d1; i < N; ++i) //3선거구
	{
		for (int j = 0; j < y - d1 + d2; ++j)
		{
			if (checkmap[i][j] == true) break;
			checkmap[i][j] = true;
			sum[2] += realmap[i][j];
		}
	}
	//printmap();
	for (int i = x + d2 + 1; i < N; ++i) //4선거구
	{
		for (int j = N - 1; j >= y - d1 + d2; --j)
		{
			if (checkmap[i][j] == true) break;
			checkmap[i][j] = true;
			sum[3] += realmap[i][j];
		}
	}
	//printmap();
	//5선거구
	sum[4] = allsum - (sum[0] + sum[1] + sum[2] + sum[3]);
	//printmap();
}

void isresult()
{
	int minvalue = 40000;
	int maxvalue = 0;
	for (int chk = 0; chk < 5; ++chk)
	{
		if (sum[chk] < minvalue)
			minvalue = sum[chk];
		if (sum[chk] > maxvalue)
			maxvalue = sum[chk];
		//initialize
		//cout << sum[chk] << " ";
		sum[chk] = 0;
	}
	if (result > (maxvalue - minvalue))
		result = maxvalue - minvalue;

	//cout << endl << maxvalue - minvalue << endl;
	//initialize
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			checkmap[i][j] = false;
		}
	}
}



int main()
{
	cin >> N;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			cin >> realmap[i][j];
			allsum += realmap[i][j];
		}
	}

	result = 40000;
	//determine x, y, d1, d2
	for (int x = 0; x < N; ++x)
	{
		for (int y = 0; y < N; ++y)
		{
			//if (((x == 0) && (y == 0)) || ((x == N - 1) && (y == 0)) || ((x == 0) && (y == N - 1)) || ((x == N - 1) && (y == N - 1))) continue;
			for (int d1 = 1; (x + d1 < N - 1)&&(y - d1 >= 0); ++d1)
			{
				for (int d2 = 1; (x + d1 + d2 < N) && (y + d2 < N); ++d2)
				{
					//printmap();
					check5sum(x, y, d1, d2);
					//printmap();
					checkallsum(x, y, d1, d2);
					isresult();
				}
			}
		}
	}

	cout << result;
}
