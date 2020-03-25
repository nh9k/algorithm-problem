#include <iostream>
//#include <vector>
using namespace std;
int n, m, h, result;
bool ladder[30][10];

bool check_i()
{
	for (int p = 0; p < n; ++p)
	{
		int ni = p;
		for (int hi = 0; hi < h; ++hi)
		{
			if (ladder[hi][ni]) ni++;
			else if (ni > 0) {
				if (ladder[hi][ni - 1]) ni--;
			}
		}
		if (ni != p) return false;
	}
	return true;
}

void make_line(int cnt, int obj_cnt,int h_idx, int n_idx)
{
	if (result != -1) return;
	if (cnt == obj_cnt)
	{
		//for (int hi = 0; hi < h; ++hi)
		//{
		//	for (int ni = 0; ni < n; ++ni)
		//	{
		//		cout << ladder[hi][ni] << " ";
		//	} cout << endl;
		//}cout << endl << endl;

		if (check_i())
			result = cnt;
		return;
	}
	for (int hi = h_idx; hi < h; ++hi)
	{
		for (int ni = n_idx; ni < n - 1; ++ni)
		{
			if (ladder[hi][ni]) continue;
			else if (ni > 0)
			{
				if (ladder[hi][ni - 1]) continue;
				else if (ni < n - 2)
					if (ladder[hi][ni + 1]) continue;
			}
			else if (ni < n - 2)
				if (ladder[hi][ni + 1]) continue;

			ladder[hi][ni] = true;
			make_line(cnt + 1, obj_cnt, hi, ni+1);
			ladder[hi][ni] = false;
		}
		n_idx = 0;
	}
}

int main()
{
	cin >> n >> m >> h;
	int a, b;
	for (int mi = 0; mi < m; ++mi)
	{
		cin >> a >> b;
		ladder[a - 1][b - 1] = true;
	}

	if (m == 0) {
		cout << 0;
		return 0;
	}

	result = -1;
	for (int c = 0; c <= 3; ++c)
	{
		//cout << "c " << c << endl;
		//if (c == 3) 
		//	printf("debug");
		make_line(0, c ,0 ,0);
		if (result != -1) break;
	}
	cout << result;

	return 0;
}