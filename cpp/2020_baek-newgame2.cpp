/*
@nh9k
문제 번호	채점 번호	아이디	문제 번호	결과			메모리	시간	언어			코드 길이	제출한 시간		풀이 시간
백준17837	19433328	nh9k	17837		맞았습니다!!	1984KB	0ms		C++14 / 수정	2882		17초 전			01:52:24.07

풀이 방법
1. 입력
	말(x,y, 방향, 현재 위치의 말이 해당하는 층수), realmap, checkmap(말의 개수map)
2. 색상 확인
  - 파란색/outof배열
	이동말의 방향 반대로 후 다시 확인
  - 흰/빨(본래 이동말이 이동할 곳 색상)
	1) 이동할 말의 수 check
	2) 이동할 말의 수가 1개일 경우 
		이동말의 x,y,층수(이동할 위치의 checkmap+1)
	2.1)이동할 말의 수가 1개 초과일 경우
		이동말의 x, y, 층수(흰: 이동말의 층수 - 본래 이동말 층수 + 이동할 위치의 checkmap + 1)
						   (빨: 이동전 위치의 checkmap - 이동말의 층수 + 이동할 위치의 checkmap + 1)
	3) 모두 이동후 map 갱신
		이동전 map: 이동전 map - (이동한 말의 개수)
		이동후 map: 이동후 map + (이동한 말의 개수)

느낀점
알고리즘을 세우고 + 코드 구현이 오래걸림, 디버깅할 필요없이 바로 pass
*/

#include <iostream>
using namespace std;

typedef struct {
	int x, y, m, f;
}horse;
horse h[10];
int N, K, realmap[12][12], checkmap[12][12], memBO;
int mx[5] = { 0, 0, 0, -1, 1 }, my[5] = { 0, 1, -1, 0, 0 };
int reverse_[5] = { 0, 2, 1, 4, 3 };

void printmap()
{
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cout << checkmap[i][j];
		}cout << endl;
	}cout << endl;
}

bool isOut(int x, int y)
{
	if ((x < 0) || (x >= N) || (y < 0) || (y >= N))
	{
		return true;
	}
	return false;
}

int isBlueOrOut(int ki)
{
	int movex = h[ki].x + mx[h[ki].m], movey = h[ki].y + my[h[ki].m];

	if (isOut(movex, movey) || (realmap[movex][movey] == 2)) //파 / out
	{
		if (memBO == ki) //2번째
		{
			//memBO = ki;
			return 2;
		}
		else //1번째
		{
			h[ki].m = reverse_[h[ki].m]; //방향 전환
			memBO = ki;
			return 1;
		}
	}
	else //흰 //빨
	{
		memBO = ki;
		return 0;
	}
}

void moving(int ki) {
	int beforex = h[ki].x, beforey = h[ki].y; //이동전 말의 위치
	int beforef = h[ki].f;
	int movex = beforex + mx[h[ki].m], movey = beforey + my[h[ki].m]; //이동후 말의 위치
	int moving_h_num = checkmap[beforex][beforey] - h[ki].f + 1; //이동할 말의 수

	if (moving_h_num == 1) {
		h[ki].x = movex, h[ki].y = movey;
		h[ki].f = checkmap[movex][movey] + 1;
	}
	else {
		if (realmap[movex][movey] == 0) {//흰
			for (int kj = 0; kj < K; ++kj) {
				if ((beforex == h[kj].x) && (beforey == h[kj].y) && (beforef <= h[kj].f))
				{
					h[kj].x = movex, h[kj].y = movey;
					h[kj].f += (checkmap[movex][movey] + 1 - beforef);
				}
			}
		}
		else {//빨
			for (int kj = 0; kj < K; ++kj) {
				if ((beforex == h[kj].x) && (beforey == h[kj].y) && (beforef <= h[kj].f))
				{
					h[kj].x = movex, h[kj].y = movey;
					h[kj].f = (checkmap[movex][movey] + 1 + checkmap[beforex][beforey] - h[kj].f);
				}
			}
		}
	}

	checkmap[beforex][beforey] -= moving_h_num; //이동전 map의 말 개수 갱신
	checkmap[movex][movey] += moving_h_num; //이동후 map의 말 개수 갱신
}

bool isHorse4() {
	for (int ki = 0; ki < K; ++ki)
	{
		if (checkmap[h[ki].x][h[ki].y] >= 4)
			return true;
	}
	return false;
}

int main()
{
	cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> realmap[i][j];
		}
	}
	int inputx, inputy;
	for (int ki = 0; ki < K; ++ki)
	{

		cin >> inputx >> inputy >> h[ki].m;
		h[ki].x = inputx - 1, h[ki].y = inputy - 1;
		h[ki].f = 1; //1층
		checkmap[h[ki].x][h[ki].y] = 1;
	}

	memBO = -1;
	for (int turn = 1; turn <= 1000; ++turn)
	{
		for (int ki = 0; ki < K;)
		{
			//printmap();
			int replay = isBlueOrOut(ki); //0: 흰/빨, 1:파/Out, 2:파/out 2번째
			if (replay == 1) { 
				continue;
			}
			else if (replay == 2) {
				++ki;
				continue;
			}

			//빨/흰
			moving(ki);

			if (isHorse4())
			{
				cout << turn;
				return 0;
			}
			++ki;
		}
	}
	cout << -1;
	return 0;
}
