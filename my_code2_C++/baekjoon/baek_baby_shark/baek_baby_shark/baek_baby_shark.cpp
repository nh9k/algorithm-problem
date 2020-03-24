#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int n, map[20][20], visit[20][20], dx[4] = { -1,0,1,0 }, dy[4] = {0,1,0,-1};
typedef struct {
	int x, y, age, cnt;
}SHARK;
SHARK s;

int bfs()
{
	int result_t = 0;
	
	while (1)
	{
		queue <pair<int, int>> search_map; //상어 주변 탐색할 큐
		search_map.push({ s.x, s.y }); //상어 초기 위치
		visit[s.x][s.y] = 1; //상어위치는 방문할 필요가 없음
		vector <pair<int, int>> eating_list; //같은 시간대 방문한 물고기들중 먹을 수 있는 물고기 넣기
		int pt = 1;

		while (!search_map.empty())
		{
			int qsz = search_map.size();//같은 시간대씩 처리
			for (int sz = 0; sz < qsz; ++sz) 
			{
				for (int m = 0; m < 4; ++m)
				{
					int mx = search_map.front().first + dx[m], my = search_map.front().second + dy[m];

					if (mx < 0 || mx >= n || my < 0 || my >= n) continue; // 배열 밖
					else if (map[mx][my] > s.age) continue; // 나이가 높으신 물고기
					else if (visit[mx][my]) continue; //이미 방문

					search_map.push({ mx,my }); // 방문해야함
					visit[mx][my] = pt; //시간 넣기
					if (map[mx][my] < s.age && map[mx][my] != 0) //먹을 리스트 넣기 //나이가 어린 물고기를 넣기
					{//먹을 리스트
						eating_list.push_back({ mx, my });
					}
				}
				search_map.pop();
			}
			if (!eating_list.empty())
			{//먹을 물고기 생기면
				break;
			}
			pt++;
		}
		if (eating_list.empty())
		{//먹을 리스트가 없으면 //while문 다 돌아도 먹을 물고기 없으면
			return result_t;
		}
		else
		{//먹을 리스트가 있으면
			int upper = 20, lefter = 20, target;
			for (int i = 0; i < eating_list.size(); ++i)
			{
				if (upper > eating_list[i].first) //더 위에 있을 경우
				{
					upper = eating_list[i].first, lefter = eating_list[i].second; //갱신
					target = i;
				}
				else if (upper == eating_list[i].first) //같은 위치일 경우
				{
					if (lefter > eating_list[i].second) //더 왼쪽인 경우
					{
						upper = eating_list[i].first, lefter = eating_list[i].second;//갱신
						target = i;
					}

				}
			}
			result_t += visit[eating_list[target].first][eating_list[target].second]; //시간 갱신
			map[eating_list[target].first][eating_list[target].second] = 0; //map 갱신
			s.x = eating_list[target].first, s.y = eating_list[target].second; //상어 위치 갱신
			s.cnt++; //상어 나이 갱신
			if (s.cnt == s.age)
			{
				s.age++;
				s.cnt = 0;
			}
			for (int ni = 0; ni < n; ++ni)
				for (int nj = 0; nj < n; ++nj)
					visit[ni][nj] =  0; //visit 갱신
		}
	}

}

int main()
{
	cin >> n;
	for (int ni = 0; ni < n; ++ni)
	{
		for (int nj = 0; nj < n; ++nj)
		{
			cin >> map[ni][nj];
			if (map[ni][nj] == 9)
			{//상어
				s.x = ni, s.y = nj, s.age = 2;
				map[ni][nj] = 0;
			}
		}
	}
	cout << bfs();
}