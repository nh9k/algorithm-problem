#include <iostream>
#include <queue>
using namespace std;
int n, m, k, a, b; //접수, 정비, 고객, 지갑고객접수, 지갑고객정비
int at[9], bt[9];
typedef struct map
{
	int map, custom_num;
}map;
map recep_map[9], repai_map[9]; //고객 체크용 map
typedef struct customer
{ //이용한 접수 창고 번호, 정비 창고 번호, 끝남
	int recep_num, repai_num;
	bool end;
}customer;
customer p[1000];
queue <int> kc, waiting2; //도착 -> 접수 //접수 -> 정비 //도착 시간
//여러 고객이 기다리고 있는 경우 고객번호가 낮은 순서대로 우선 접수한다
priority_queue <int, vector<int>, greater<int>> waiting1; //오름차순
//먼저 기다리는 고객이 우선한다.
//두 명 이상의 고객들이 접수 창구에서 동시에 접수를 완료하고 정비 창구로 이동한 경우, 이용했던 접수 창구번호가 작은 고객이 우선
priority_queue <pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> tempwait2; //key 오름차순

int who() //지갑을 잃어버린 고객이 간 접수 창고와 정비 창고 번호가 같을 경우 더해줌
{
	int sum = 0;
	bool flag = false;
	for (int i = 0; i < k; i++)
	{
		if ((a == p[i].recep_num) && (b == p[i].repai_num))
		{
			sum += (i + 1);
			flag = true;
		}
			
	}
	if (flag == true) return sum;
	else return -1;
}

void working() //시간에 따라 고객 이동
{
	int timek = 0, c = 0;
	int checking = false;
	while (!checking) 
	{
		while (!kc.empty()) 
		{
			if (timek == kc.front()) //순서대로 접수 창고에 넣기
			{
				kc.pop();
				waiting1.push(c);
				c++; //고객 수 증가
			}
			else
				break;
		}

		for (int i = 0; i < n; i++) //접수 창고의 낮은 번호부터 검사: 고객이 있는 창고의 경우 시간++
		{
			if (recep_map[i].map != -1) //고객이 있는 접수 창고
			{
				if (recep_map[i].map == at[i]-1) //접수 창고 처리 시간과 같으면
				{
					recep_map[i].map = -1; //빈 접수 창고
					tempwait2.push({ i,recep_map[i].custom_num }); //정비 창고 waiting에 넣음
				}
				else
				{
					recep_map[i].map++; //고객이 있는 창고의 경우 시간++
				}
			}
		}

		while (!waiting1.empty()) //접수 관련 waiting 처리
		{
			bool flag = false;
			for (int i = 0; i < n; i++) //접수 창고의 낮은 번호부터 검사
			{	
				if (waiting1.empty()) break;
				if (recep_map[i].map == -1) //빈 접수 창고
				{
					recep_map[i].map = 0; //고객을 접수 창고에 
					recep_map[i].custom_num = waiting1.top(); //접수 창고에 고객 번호 저장
					p[waiting1.top()].recep_num = i+1; //접수 창고 번호 고객에 저장
					waiting1.pop();
				}
				if (i == n-1) flag = true; //접수 창고 모두 검사해도 빈 곳이 없음
			}
			if (flag == true) break;
		}

		for (int i = 0; i < m; i++) //정비 창고의 낮은 번호부터 검사: 고객이 있는 창고의 경우 시간++
		{
			if (repai_map[i].map != -1) //고객이 있는 정비 창고
			{
				if (repai_map[i].map == bt[i]-1) //정비 창고 처리 시간과 같으면
				{
					repai_map[i].map = -1; //빈 정비 창고
					p[repai_map[i].custom_num].end = true;
				}
				else
				{
					repai_map[i].map++; //고객이 있는 창고의 경우 시간++
				}
			}
		}

		while (!tempwait2.empty())
		{ //먼저 기다리는 고객이 우선한다.: queue로 waiting2에서 관리
		  //두 명 이상의 고객들이 접수 창구에서 동시에 접수를 완료하고 정비 창구로 이동한 경우, 이용했던 접수 창구번호가 작은 고객이 우선
		  //: priority queue로 tempwait2에서 관리
			waiting2.push(tempwait2.top().second);
			tempwait2.pop();
		}

		while (!waiting2.empty()) //정비 관련 waiting
		{
			bool flag = false;
			for (int i = 0; i < m; i++) //정비 창고의 낮은 번호부터 검사
			{
				if (waiting2.empty()) break;
				if (repai_map[i].map == -1) //빈 정비 창고
				{
					repai_map[i].map = 0; //고객을 정비 창고에 
					repai_map[i].custom_num = waiting2.front(); //정비 창고에 고객 번호 저장
					p[waiting2.front()].repai_num = i+1; //정비 창고 번호 고객에 저장
					waiting2.pop();
				}
				if (i == m-1) flag = true; //접수 창고 모두 검사해도 빈 곳이 없음
			}
			if (flag == true) break;
		}

		checking = true;
		for (int i = 0; i < k; i++) //모든 고객이 끝났는지 검사
			if (p[i].end == false) { checking = false; break; }

		timek++; //시간 증가
	}
}
/*
#1 3
#2 7
#3 2
#4 22
#5 18
#6 15
#7 - 1
#8 259
#9 100
#10 164*/
int main()
{
	freopen("sample_input.txt", "r", stdin);
	int t, kt;
	scanf("%d", &t);
	for (int i = 0; i < t; i++)
	{	
		scanf("%d %d %d %d %d", &n, &m, &k, &a, &b);
		for (int j = 0; j < n; j++) //접수 시간
			scanf("%d", &at[j]);
		for (int j = 0; j < m; j++) //정비 시간
			scanf("%d", &bt[j]);
		for (int j = 0; j < k; j++) {//고객 도착 시간
			scanf("%d", &kt); //고객 번호가 높아질 수록 도착시간이 큰가? 일단 그렇다고 가정.
			kc.push(kt);
		}
		for (int j = 0; j < n; j++) //접수 map 초기화
		{
			recep_map[j].map = -1;
			recep_map[j].custom_num = 0;
		}	
		for (int j = 0; j < m; j++) //정비 map 초기화
		{
			repai_map[j].map = -1;
			repai_map[j].custom_num = 0;
		}
		for (int j = 0; j < k; j++) //고객 정보 초기화
		{
			p[j].end = false;
			p[j].recep_num = 0;
			p[j].repai_num = 0;
		}
		//if(i + 1 == 7)
		working();
		if (i + 1 == 7)
		printf("#%d %d\n", i + 1, who());
	}
}