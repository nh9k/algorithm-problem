#include <iostream>

int sum, cnt;
int target[3] = { 1,2,3 };

void rec(int compare)
{
	if (compare == sum)
	{
		cnt++;
		//printf("compare::%d\n", compare);
		return ;
	}
	else if (compare > sum) return;
	for (int i = 0; i < 3; i++)
	{
		//printf("rec:: %d + %d\n", target[i], compare);
		rec(target[i] + compare);
	}
	return;
}


int main()
{
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
	{ 
		cnt = 0;
		scanf("%d",&sum);
		rec(0);
		printf("%d\n", cnt);
	}

}