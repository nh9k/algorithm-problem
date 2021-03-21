//time over!

#include <iostream>
#include <vector>
using namespace std;

int Mmap[51][51], Smap[51][51], Dmap[51][51], Cmap[51][51];
int dr[8] = { -1,-1,0,1,1,1,0,-1 };
int dc[8] = { 0,1,1,1,0,-1,-1,-1 };
int N, K;
typedef struct{
	int r, c, m, s, d;
}ball;
vector<ball> b;
vector <int> erase_list;

bool is_odd(int number) {
	if (number % 2 == 0)
		return false;
	else
		return true;
}

int what_dir(int r, int c, int dir) //¾øÀ½0, È¦1, Â¦2, È¥ÇÕ3
{
	if (Dmap[r][c] == 0) {
		if (is_odd(dir))
			return 1;
		else
			return 2;
	}
	else if (Dmap[r][c] == 3)
		return 3;
	else if (Dmap[r][c] == 1)
	{
		if (is_odd(dir))
			return 1;
		else
			return 3;
	}
	else if (Dmap[r][c] == 2) 
	{
		if (is_odd(dir))
			return 3;
		else
			return 2;
	}
}

void moving() {
	for (int i = 0; i < b.size(); ++i) {
		b[i].r = (b[i].r + (dr[b[i].d] * b[i].s)) % N;
 		b[i].c = (b[i].c + (dc[b[i].d] * b[i].s)) % N;
		if (b[i].r < 0) b[i].r = N + b[i].r;
		if (b[i].c < 0) b[i].c = N + b[i].c;		
		if (b[i].r > N-1) b[i].r = b[i].r - N;
		if (b[i].c > N-1) b[i].c = b[i].c - N;

		Mmap[b[i].r][b[i].c] += b[i].m;
		Smap[b[i].r][b[i].c] += b[i].s;
		Dmap[b[i].r][b[i].c] = what_dir(b[i].r, b[i].c, b[i].d);
		Cmap[b[i].r][b[i].c] += 1;
	}
}

void new_ball() {
	int bsize = b.size();
	for (int i = 0; i < bsize; ++i) {
		if ((Mmap[b[i].r][b[i].c] != b[i].m) && (Mmap[b[i].r][b[i].c] != 0))
		{
			int inputr = b[i].r,
				inputc = b[i].c,
				inputm = Mmap[b[i].r][b[i].c] / 5,
				inputs = Smap[b[i].r][b[i].c] / Cmap[b[i].r][b[i].c];

			if (Dmap[b[i].r][b[i].c] == 3) {
				b.push_back({ inputr,inputc,inputm, inputs, 1 });
				b.push_back({ inputr,inputc,inputm, inputs, 3 });
				b.push_back({ inputr,inputc,inputm, inputs, 5 });
				b.push_back({ inputr,inputc,inputm, inputs, 7 });
			}
			else
			{
				b.push_back({ inputr,inputc,inputm, inputs, 2 });
				b.push_back({ inputr,inputc,inputm, inputs, 4 });
				b.push_back({ inputr,inputc,inputm, inputs, 6 });
				b.push_back({ inputr,inputc,inputm, inputs, 8 });
			}
			erase_list.push_back(i);
		}
		else if ((Mmap[b[i].r][b[i].c] != b[i].m) && (Mmap[b[i].r][b[i].c] == 0))
		{
			erase_list.push_back(i);
		}

		Mmap[b[i].r][b[i].c] = 0;
		Smap[b[i].r][b[i].c] = 0;
		Cmap[b[i].r][b[i].c] = 0;
		Dmap[b[i].r][b[i].c] = 0;
	}
}

int main()
{
	int M;
	cin >> N >> M >> K;

	int tmpr, tmpc, tmpm, tmps, tmpd;
	for (int mi = 0; mi < M; ++mi)
	{
		cin >> tmpr >> tmpc >> tmpm >> tmps >> tmpd;
		b.push_back({ tmpr - 1, tmpc - 1, tmpm, tmps, tmpd });
	}

	for (int ki = 0; ki < K; ++ki)
	{
		moving();
		new_ball();

		int esize = erase_list.size();
		for (int mi = esize-1; mi >= 0; --mi)
		{
			b.erase(b.begin() + erase_list[mi]);
		}

		erase_list.clear();

		//for (int mi = 0; mi < b.size(); ++mi) {
		//	cout << b[mi].r << " " << b[mi].c << " " << b[mi].m << " " << b[mi].s << " " << b[mi].d << endl;
		//}cout << endl;
	}

	int sum_of_m = 0;
	for (int mi = 0; mi < b.size(); ++mi) {
		sum_of_m += b[mi].m;
	}

	cout << sum_of_m;
	return 0;
}