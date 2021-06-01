/*
@nh9k
DP 병렬 배열 문제 == 병렬식 풀이
문제 번호
백준 1149 
채점 번호	아이디	문제 번호	결과	메모리	시간	언어	코드 길이
19549050	nh9k	1149	맞았습니다!!2008	0	C++14 / 수정	2034
*/
#include <iostream>
#include <algorithm>
typedef struct {
	int color[3];
}rgb;
rgb cost[1002]; //cost[0], cost[1001] = {0,0,0}
rgb mincost[1002];

int main()
{
	int N;
	std::cin >> N;
	for (int n = 1; n <= N; ++n)
		std::cin >> cost[n].color[0] >> cost[n].color[1] >> cost[n].color[2];
	
	//way1
	//int curcost = 3001, cur_i = 0, pre_i, selectcost = 0, mincost = 9000000;
	//for (int fi = 0; fi < 3; ++fi) {
	//	pre_i = fi;
	//	for (int n = 1; n <= N; ++n) {
	//		for (int si = 0; si < 3; ++si) {
	//			if (si == pre_i) continue; //이전 선택 색상과 같으면 pass
	//			for (int sj = 0; sj < 3; ++sj) {
	//				if (si == sj) continue;
	//				if (curcost > cost[n - 1].color[pre_i] + cost[n].color[si] + cost[n + 1].color[sj]) {
	//					curcost = cost[n - 1].color[pre_i] + cost[n].color[si] + cost[n + 1].color[sj];
	//					cur_i = si;
	//				}
	//			}
	//		}
	//		pre_i = cur_i;
	//		selectcost += cost[n].color[pre_i];
	//		curcost = 3001;
	//	}
	//	if (mincost > selectcost)
	//		mincost = selectcost;
	//	selectcost = 0;
	//}
	//std::cout << mincost;

	//way2
	//for(int si=0; si<3; ++si)
	//	bruteforce(N, 1, 0, si);
	//std::cout << mincost;

	//way3
	for (int i = 1; i <= N; ++i) {
		mincost[i].color[0] = std::min(mincost[i - 1].color[1], mincost[i - 1].color[2]) + cost[i].color[0];
		mincost[i].color[1] = std::min(mincost[i - 1].color[0], mincost[i - 1].color[2]) + cost[i].color[1];
		mincost[i].color[2] = std::min(mincost[i - 1].color[0], mincost[i - 1].color[1]) + cost[i].color[2];
	}

	int result = 10000000;//INT_MAX;
	for (int i = 0; i < 3; ++i) {
		if (result > mincost[N].color[i])
			result = mincost[N].color[i];
	}
	std::cout << result;
}

//way2 //timeover
//int mincost = 9000000;
//
//void bruteforce(int N, int cur, int resultcost, int select) {
//	if (mincost < resultcost) return;
//	if (N < cur) {
//		if (mincost > resultcost)
//			mincost = resultcost;
//		return;
//	}
//	for (int i = 0; i < 3; ++i) {
//		if (select == i) continue;
//		bruteforce(N, cur + 1, resultcost + cost[cur].color[i], i);
//	}
//}