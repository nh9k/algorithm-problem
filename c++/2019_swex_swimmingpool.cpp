//수업때 배운 동전 최소 개수와 비슷한 문제,
//재귀로 그리디 or dp 알고리즘을 짠다.
#include <iostream>
#include <algorithm>//min 헤더파일
using namespace std;//for min function
int month[12], cost[4];
int minimum; //최소결과값

void topdown(int now, int s){//https://m.blog.naver.com/PostView.nhn?blogId=gngh0101&logNo=221239238120&proxyReferer=https%3A%2F%2Fwww.google.com%2F
	if (now >= 12) {
		minimum = min(minimum, s);
		return;
	}
	if (s > minimum)
		return;
	topdown(now + 1, s + month[now] * cost[0]);
	topdown(now + 1, s + cost[1]);
	topdown(now + 3, s + cost[2]);
	//topdown(now + 12, s + cost[3]);
}

int cal[12];
int bottomup() //https://2youngjae.tistory.com/72
{
	for (int i = 0; i < 12; i++) //1일과 한달의 최소값을 저장함, 0일인 달 기준은 0가 들어감
		cal[i] = min(month[i] * cost[0], cost[1]);

	for (int i = 0; i < 12; i++)
	{
		if(i>0)
			cal[i] += cal[i - 1];
		if (i >= 2)
			cal[i] = min(cal[i - 3] + cost[2], cal[i]);
	}
	
	if (cal[11] > cost[3])
		cal[11] = cost[3];

	return cal[11];
}
//1. dMonth[1] + dMonth[2] + dMonth[3] + dMonth[4]
//2. (1, 2, 3 3달이용권) + dMonth[4];
//3. dMonth[1] + (2, 3, 4 3달 이용권)
//d[n]=min( d[n-1] + dMonth[n] ,  d[n-3] + 3달이용권 ) 
//for (int i = 1; i <= 12; i++) {
//	d[i] = d[i - 1] + dMonth[i];
//	if (i - 3 >= 0) {
//		if (d[i] > d[i - 3] + price[2]) {
//			d[i] = d[i - 3] + price[2];
//		}
//	}
//}

int main()
{
	int t;
	freopen("sample_input.txt", "r", stdin);
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
	{
		scanf("%d %d %d %d", &cost[0], &cost[1], &cost[2], &cost[3]);
		minimum = cost[3]; //1년치 끊은 것이 minimum으로 시작

		for (int j = 0; j < 12; j++)
			scanf("%d", &month[j]);

		//topdown(0, 0);
		//printf("#%d %d\n", i + 1, minimum);
		printf("#%d %d\n", i + 1, bottomup());
	}
	return 0;
}