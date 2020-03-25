//������ ��� ���� �ּ� ������ ����� ����,
//��ͷ� �׸��� or dp �˰����� §��.
#include <iostream>
#include <algorithm>//min �������
using namespace std;//for min function
int month[12], cost[4];
int minimum; //�ּҰ����

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
	for (int i = 0; i < 12; i++) //1�ϰ� �Ѵ��� �ּҰ��� ������, 0���� �� ������ 0�� ��
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
//2. (1, 2, 3 3���̿��) + dMonth[4];
//3. dMonth[1] + (2, 3, 4 3�� �̿��)
//d[n]=min( d[n-1] + dMonth[n] ,  d[n-3] + 3���̿�� ) 
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
		minimum = cost[3]; //1��ġ ���� ���� minimum���� ����

		for (int j = 0; j < 12; j++)
			scanf("%d", &month[j]);

		//topdown(0, 0);
		//printf("#%d %d\n", i + 1, minimum);
		printf("#%d %d\n", i + 1, bottomup());
	}
	return 0;
}