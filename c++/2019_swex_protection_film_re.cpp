#include <iostream>
using namespace std;
int d, w, k, min_result;
bool film[13][20], cpy_film[13][20];

bool check()
{
	for (int wi = 0; wi < w; ++wi)
	{
		int mem_cnt = 1, mem_num = film[0][wi];
		for (int di = 1; di < d; ++di)
		{
			if (mem_num != film[di][wi])
			{
				mem_cnt = 1;
				mem_num = film[di][wi];
			}
			else
			{
				mem_cnt++;
				if (mem_cnt == k)
					break; //¼¿ Åë°ú
			}
			if (di >= d - k + 1 && mem_cnt <= k - (d-di)) return false;
		}
	}
	return true;
}

void dfs(int cnt, int idx)
{
	if (cnt >= k || cnt >= min_result) return;
	if (check())
	{
		if(min_result > cnt)
			min_result = cnt;
		return;
	}

	for (int di = idx; di < d; ++di)
	{
		for (int ab = 0; ab < 2; ++ab)
		{
			for (int wi = 0; wi < w; ++wi)
				film[di][wi] = ab;			
			dfs(cnt + 1, idx + 1);
		}	
		for (int wi = 0; wi < w; ++wi)
			film[di][wi] = cpy_film[di][wi];
	}
}

int main()
{
	freopen("sample_input.txt", "r", stdin);
	int t;
	cin >> t;
	for (int ti = 0; ti < t; ++ti)
	{
		cin >> d >> w >> k;
		for (int di = 0; di < d; ++di) {
			for (int wi = 0; wi < w; ++wi) {
				cin >> film[di][wi];
				cpy_film[di][wi] = film[di][wi];
			}
				
		}

		if (k == 1)
			cout << "#" << ti + 1 << " " << 0 << endl;
		else
		{
			min_result = 987654321;
			dfs(0, 0);

			if (min_result == 987654321) cout << "#" << ti + 1 << " " << k << endl;
			else cout << "#" << ti + 1 << " " << min_result << endl;
		}
	}
	return 0;
}
