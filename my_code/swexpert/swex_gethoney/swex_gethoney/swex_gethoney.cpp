#include <iostream>
int n, m, c; //크키, 채취크기, 최대 채취양
int honey[10][10], worker[2][5], revenue[2], max_revenue; //벌꿀map, 일꾼1,2에 보고있는 배열을 저장, 일꾼1,2수익, 최대수익
bool visit[5];

void result()
{
	if (max_revenue < revenue[0] + revenue[1]) //worker1과 worker2의 합
		max_revenue = revenue[0] + revenue[1];	//최대 수익 갱신
}

void small_dfs(int present, int who, int visitnum) //합이 c보다 작고 최대 수익이 되도록 수익 저장
{ //현재 인덱스, 일꾼1or2, 숫자 개수-1
	if (visitnum >= 1) //이렇게 해주면 배열에 729이면 7->72->729->79->2->29->9 로 돈다. 
	{					//중간에 리턴되면 제대로 못 도니까. 아래에 리턴을 해주고 m팩토리얼만큼 돌리는 게 더 정확하다.
		bool flag = false;
		int check = 0;

		for (int i = 0; i < m; i++)
			if (visit[i] == true) 
				check += worker[who][i];	//일꾼 한명에 대해서 배열 합			

		if (check <= c) flag = true; //합이 c양보다 작아야 
		else return;
		if (flag)
		{
			check = 0;
			for (int i = 0; i < m; i++)	
				if (visit[i] == true)
					check += worker[who][i] * worker[who][i]; //값을 구할 수 있음

			if (check > revenue[who]) //일꾼 한명에 대해서 최댓값이면 
				revenue[who] = check;
		}
		//여기서 리턴을 해주면 small_dfs(0, 0, 0);를 돌릴 때 if (visitnum >= 1)에서 1이 아니라 m팩토리얼만큼 돌려줘야함
	}
	for (int i = present; i < m; i++)
	{
		visit[i] = true;
		small_dfs(i + 1, who, visitnum + 1); //배열 값이 729, m이 3이면 7->72->729->79->2->29->9
		visit[i] = false;
	}
}

void big_repeat() //m 크기만큼 모두 방문: 두 일꾼의 배열을 small_dfs에 넘겨줌
{
	for (int i = 0; i < n; i++) //일꾼 1에 대한 배열: 세로축
	{
		for (int j = 0; j <= n - m; j++) //일꾼 1에 대한 배열: 가로축
		{
			for (int k = 0; k < m; k++) //배열 개수에 따른 일꾼 1 배열 지정
				worker[0][k] = honey[i][j + k];

			revenue[0] = 0, revenue[1] = 0; //조심!! 초기화 잘 해주기: 일꾼1 지정을 새로이 할 때 초기화
			small_dfs(0, 0, 0); //일꾼 1 배열 지정한 것에 대해 배열 내부 값을 dfs로 돌려 최대 수익을 얻음

			for (int i2 = i; i2 < n; i2++) //일꾼 2에 대한 배열: 세로축
			{
				if (i2 == i) //일꾼 1과 같은 줄에 있을 경우
				{
					for (int j2 = j + m; j2 <= n - m; j2++) //일꾼 2에 대한 배열: 가로축
					{
						for (int k = 0; k < m; k++) //배열 개수에 따른 일꾼 2 배열 지정
							worker[1][k] = honey[i2][j2 + k];
							
						small_dfs(0, 1, 0); //일꾼 2 배열 지정한 것에 대해 배열 내부 값을 dfs로 돌려 최대 수익을 얻음
						result(); //일꾼 1과 2의 최대 수익 합
					}
				}
				else //일꾼 1과 다른 줄에 있을 경우
				{
					for (int j2 = 0; j2 <= n - m; j2++) //일꾼 2에 대한 배열: 가로축
					{

						for (int k = 0; k < m; k++) //배열 개수에 따른 일꾼 2 배열 지정
							worker[1][k] = honey[i2][j2 + k];
							
						small_dfs(0, 1, 0); //일꾼 2 배열 지정한 것에 대해 배열 내부 값을 dfs로 돌려 최대 수익을 얻음
						result(); //일꾼 1과 2의 최대 수익 합
					}
				}
			}
		}
	}
}
//#1 174
//#2 131
//#3 145
//#4 155
//#5 166
//#6 239
//#7 166
//#8 172
//#9 291
//#10 464
int main()
{
	freopen("sample_input.txt", "r", stdin);
	int t;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
	{
		scanf("%d %d %d", &n, &m, &c);
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				scanf("%d", &honey[j][k]);

		revenue[0] = 0, revenue[1] = 0, max_revenue = 0;
		big_repeat(); //전체 큰 반복문 틀
		printf("#%d %d\n", i + 1, max_revenue);
	}
}