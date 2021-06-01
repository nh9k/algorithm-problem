#include <iostream>
#include <queue>
using namespace std;

int green[6][4], blue[4][6];
int point;
struct block {
	int x1, y1, x2, y2, t;
}b;

void bfs(int x, int y, bool is_green) {
	b.x1 = x;
	b.y1 = y;
	if (is_green == 1) {
		if (((y - 1) > 0) && (green[x][y - 1] == green[x][y])) {
			b.x2 = x;
			b.y2 = y - 1;
			b.t = 2;
			return;
		}
		if (((y + 1) < 4) && (green[x][y + 1] == green[x][y])) {
			b.x2 = x;
			b.y2 = y + 1;
			b.t = 2;
			return;
		}
		if (((x - 1) > 0) && (green[x - 1][y] == green[x][y])) {
			b.x2 = x - 1;
			b.y2 = y;
			b.t = 3;
			return;
		}
		if (((x + 1) < 6) && (green[x + 1][y] == green[x][y])) {
			b.x2 = x + 1;
			b.y2 = y;
			b.t = 3;
			return;
		}
		b.t = 1;
		return;
	}
	else {
		if (((y - 1) > 0) && (blue[x][y - 1] == blue[x][y])) {
			b.x2 = x;
			b.y2 = y - 1;
			b.t = 2;
			return;
		}
		if (((y + 1) < 6) && (blue[x][y + 1] == blue[x][y])) {
			b.x2 = x;
			b.y2 = y + 1;
			b.t = 2;
			return;
		}
		if (((x - 1) > 0) && (blue[x - 1][y] == blue[x][y])) {
			b.x2 = x - 1;
			b.y2 = y;
			b.t = 3;
			return;
		}
		if (((x + 1) < 4) && (blue[x + 1][y] == blue[x][y])) {
			b.x2 = x + 1;
			b.y2 = y;
			b.t = 3;
			return;
		}
		b.t = 1;
		return;
	}
}

void down(bool is_green, int si) {
	if (is_green == 1) {
		for (int xi = 0; xi < 6; ++xi) {
			if ((b.t == 1) && (green[xi][b.y1] != 0))
			{
				green[xi - 1][b.y1] = si;
				break;
			}
			else if ((b.t == 2) && ((green[xi][b.y1] != 0) || (green[xi][b.y2] != 0)))
			{
				green[xi - 1][b.y1] = si;
				green[xi - 1][b.y2] = si;
				break;
			}
			else if ((b.t == 3) && ((green[xi][b.y1] != 0) || (green[xi+1][b.y2] != 0)))
			{
				green[xi - 1][b.y1] = si;
				green[xi][b.y2] = si;
				break;
			}
			else if (xi == 5) { //floor
				if(b.t == 1)
					green[xi][b.y1] = si;
				else if(b.t == 2)
				{
					green[xi][b.y1] = si;
					green[xi][b.y2] = si;
				}
				else {
					green[xi - 1][b.y1] = si;
					green[xi][b.y2] = si;
				}
				break;
			}
		}
	}
	else {
		for (int yi = 0; yi < 6; ++yi) {
			if ((b.t == 1) && (blue[b.x1][yi] != 0))
			{
				blue[b.x1][yi - 1] = si;
				break;
			}
			else if ((b.t == 2) && ((blue[b.x1][yi] != 0) || (blue[b.x2][yi + 1] != 0)))
			{
				blue[b.x1][yi - 1] = si;
				blue[b.x2][yi] = si;
				break;
			}
			else if ((b.t == 3) && ((blue[b.x1][yi] != 0) || (blue[b.x2][yi] != 0)))
			{
				blue[b.x1][yi - 1] = si;
				blue[b.x2][yi - 1] = si;
				break;
			}
			else if (yi == 5) { //floor
				if (b.t == 1)
					blue[b.x1][yi] = si;
				else if (b.t == 2)
				{
					blue[b.x1][yi - 1] = si;
					blue[b.x2][yi] = si;
				}
				else
				{
					blue[b.x1][yi] = si;
					blue[b.x2][yi] = si;
				}
				break;
			}
		}
	}
}

void print_gb() {
	for (int xi = 0; xi <= 5; ++xi)
	{
		for (int yi = 0; yi < 4; ++yi)
		{
			cout << green[xi][yi];
		}
		cout << endl;
	}
	cout << endl;

	for (int xi = 0; xi < 4; ++xi)
	{

		for (int yi = 0; yi <= 5; ++yi)
		{
			cout << blue[xi][yi];
		}
		cout << endl;
	}
	cout << endl;
}

int main() {
	int vsize, t, x, y;
	cin >> vsize;

	for (int si = 1; si <= vsize; ++si)
	{
		//input
		cin >> t >> x >> y;
		if (t == 1) b = { x, y, -1, -1, 1};
		else if (t == 2) b = { x, y, x, y+1, 2 };	
		else if (t == 3) b = { x, y, x+1, y, 3 };


		//green push
		down(1, si);
		//blue push
		down(0, si);

		print_gb();

		//green full & over -> erase, down, point
		bool erase_true;
		int f;
		while (1) {
			queue <int> erase_floor;
			for (int xi = 5; xi >= 0; --xi) {
				int erase_true = 1;
				for (int yi = 0; yi < 4; ++yi)
				{
					if (((xi == 0) || (xi == 1)) && green[xi][yi] != 0) //over
					{
						erase_true = 2;
						break;
					}
					if (green[xi][yi] == 0) //no full
					{ 
						erase_true = 0;
						break;
					}
				}
				if (erase_true == 1) { 
					point += 1;
					erase_floor.push(xi);
				}
				else if (erase_true == 2) {
					erase_floor.push(5);
				}
			}

			//erase
			int efs = erase_floor.size();
			if (efs == 0) break;
			for (int qsz = 0; qsz < efs; ++qsz)
			{
				int f = erase_floor.front();
				erase_floor.pop();
				green[f][0] = 0;
				green[f][1] = 0;
				green[f][2] = 0;
				green[f][3] = 0;
			}

			print_gb();

			// down
			for (int xi = 4; xi >= 0; --xi) {
				for (int yi = 0; yi < 4; ++yi) {
					if (green[xi][yi] != 0) {
						bfs(xi, yi, 1);
						cout << b.t << b.x1 << b.x2 << b.y1 << b.y2;
						down(1, green[xi][yi]);
					}
				}
			}
		}
		
		//blue full & over -> erase, down, point
		while (1) {
			queue <int> erase_floor;
			for (int yi = 5; yi >= 0; --yi) {
				erase_true = 1;
				for (int xi = 0; xi < 4; ++xi)
				{
					if (blue[xi][yi] == 0) // no full
					{
						erase_true = 0;
						break;
					}
					if (((yi == 0) || (yi == 1)) && blue[xi][yi] != 0) //over
					{
						erase_true = 2;
						break;
					}

				}
				if (erase_true == 1) {
					point += 1;
					erase_floor.push(yi);
				}
				else if (erase_true == 2) {
					erase_floor.push(5);
				}
			}

			//erase
			int efs = erase_floor.size();
			if (efs == 0) break;
			for (int qsz = 0; qsz < efs; ++qsz)
			{
				int f = erase_floor.front();
				erase_floor.pop();
				blue[0][f] = 0;
				blue[1][f] = 0;
				blue[2][f] = 0;
				blue[3][f] = 0;
			}

			print_gb();

			// down
			for (int yi = 4; yi >= 0; --yi) {
				for (int xi = 0; xi < 4; ++xi)
				{
					if (blue[xi][yi] != 0) {
						bfs(xi, yi, 1);
						down(0, blue[xi][yi]);
					}
				}
			}
		}

		print_gb();
	}

	//°á°ú
	int cnt = 0;
	for (int xi = 0; xi < 6; ++xi) {
		for (int yi = 0; yi < 4; ++yi) {
			if (green[xi][yi] != 0)
				cnt++;
		}
	}	
	for (int xi = 0; xi < 4; ++xi) {
		for (int yi = 0; yi < 6; ++yi) {
			if (blue[xi][yi] != 0)
				cnt++;
		}
	}
	cout << point << endl;
	cout << cnt << endl;
	return 0;
}