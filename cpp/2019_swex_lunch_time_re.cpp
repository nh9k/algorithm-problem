#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef struct {
	int x, y, dist, ss;
	bool finish;
}PERSON;
typedef struct {
	int x, y, length;
}STAIR;
vector <PERSON> p;
vector <STAIR> s;
int min_time;

int simulation()
{
	priority_queue <pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> push_p[2];	
	for (int v = 0; v < p.size(); ++v) //계단까지의 거리 측정
	{
		p[v].dist = abs(p[v].x - s[p[v].ss].x) + abs(p[v].y - s[p[v].ss].y);
		push_p[p[v].ss].push({ p[v].dist, v }); //dist와 index 저장할 min_heap 큐
	}

	vector <pair<int, int>> sq[2]; //인덱스와 시간, 계단에서의 시간 측정해줄 벡터
	int t = 1;
	while (1)
	{
		for (int idx = 0; idx <= 1; ++idx) //계단에 넣어주기
		{
			while (!push_p[idx].empty()) //대기 리스트가 있으면
			{
				if (t >= push_p[idx].top().first)  //계단 입구 도착
				{
					if (sq[idx].size() < 3) //계단에 3명보다 작게 있음
					{
						if(t == push_p[idx].top().first) //도착했으니 1분 후 내려감
							sq[idx].push_back({ push_p[idx].top().second, -1 }); //계단에 넣어주고
						else  //대기 중이었다 곧장 내려감
							sq[idx].push_back({ push_p[idx].top().second, 0 }); //계단에 넣어주고
						push_p[idx].pop(); //대기 리스트에서 제외
					}
					else //3명 있음
						break;
				}
				else //아무도 도착 x
					break;
			}
		}
	
		for (int idx = 0; idx <= 1; ++idx) //계단에서 시간 측정하기
		{
			for (auto v = sq[idx].begin(); v != sq[idx].end();)
			{
				(*v).second++;
				if ((*v).second == s[idx].length)
				{
					p[(*v).first].finish = true; //계단 탈출
					v = sq[idx].erase(v); 
				}
				else
					++v;
			}
		}

		bool pass = true;
		for (int v = 0; v < p.size(); ++v)
		{
			if (p[v].finish == false)
			{
				pass = false;
				break;
			}
		}
		if (pass) break;
		++t;	
		if (t > min_time) return t;
	}
	return t;
}

void dfs(int idx)
{
	if (idx == p.size())
	{
		int temp = simulation();
		for (int v = 0; v < p.size(); ++v)
		{
			p[v].finish = false;
		}
		if (min_time > temp)
			min_time = temp;
		return;
	}
	for (int select_stair = 0; select_stair <= 1; ++select_stair)
	{
		p[idx].ss = select_stair;
		dfs(idx + 1);
	}
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	int t, n, temp;
	cin >> t;
	for (int ti = 0; ti < t; ++ti)
	{
		cin >> n;
		for (int ni = 0; ni < n; ++ni)
		{
			for (int nj = 0; nj < n; ++nj)
			{
				cin >> temp;
				if (temp == 1)
				{//사람
					p.push_back({ ni, nj });
				}
				else if(temp != 0)
				{//계단
					s.push_back({ ni,nj,temp });
				}
			}
		}
		min_time = 1e9;
		dfs(0);
		cout << "#" << ti + 1 << " " << min_time << endl;
		p.clear();
		s.clear();
	}
	return 0;
}