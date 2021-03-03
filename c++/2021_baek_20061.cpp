//제출 번호	아이디	문제	결과	메모리	시간	언어	코드 길이	제출한 시간
//26895084	nh9k	20061	맞았습니다!!2016	8	C++17 / 수정	5046	11초 전
//모노미노도미노2
//풀이 시간 약 3~4시간
//시뮬레이션 문제
//문제가 정확하게 서술되어 있지 않아서 + 생각지 못한 부분이 있어서 + 구현할 부분이 많아서 오래걸림
//1. 한줄이 지워지면 위에서 한칸씩만 앞당긴다
//2. 1라인의 연한 부분에 채워져서 5라인 한줄이 지워지고 당겨진후, 다시 1라인을 검사해 원래 0라인에 블럭이 있었는지 확인해야한다.
//3. 블럭을 당겨서 지워지고 나게 한 이후, 0라인의 블럭은 false로 넣어줘야 한다.
//4. 연한 부분에 블럭이 있어서 5라인을 한줄을 지울 경우, 이경우는 점수에 포함하지 않고 지워진 블록에만 측정한다.


#include <iostream>
using namespace std;
bool green[6][4], blue[4][6];
int point, eblock;


void down_block(int t, int x, int y)
{//입력된 블럭이 아래로 이동하는 함수
	if (t == 1)
	{
		//green(y고정)
		for (int xi = 2; xi < 6; ++xi) {
			if (green[xi][y] == true)
			{
				green[xi - 1][y] = true;
				break;
			}
			if (xi == 5)
			{
				green[xi][y] = true;
				break;
			}
		}
		//blue(x고정)
		for (int yi = 2; yi < 6; ++yi) {
			if (blue[x][yi] == true)
			{
				blue[x][yi - 1] = true;
				break;
			}
			if (yi == 5)
			{
				blue[x][yi] = true;
				break;
			}
		}
	}
	else if (t == 2)
	{
		//green(y, y+1 확인)
		for (int xi = 2; xi < 6; ++xi) {
			if ((green[xi][y] == true) || (green[xi][y+1] == true))
			{
				green[xi - 1][y] = true;
				green[xi - 1][y + 1] = true;
				break;
			}
			if (xi == 5)
			{
				green[xi][y] = true;
				green[xi][y + 1] = true;
				break;
			}
		}
		//blue(x고정, )
		for (int yi = 2; yi < 6; ++yi) {
			if (blue[x][yi] == true)
			{
				blue[x][yi - 2] = true;
				blue[x][yi - 1] = true;
				break;
			}
			if (yi == 5)
			{
				blue[x][yi-1] = true;
				blue[x][yi] = true;
				break;
			}
		}
	}
	else //t==3
	{
		//green(y고정)
		for (int xi = 2; xi < 6; ++xi) {
			if (green[xi][y] == true)
			{
				green[xi - 2][y] = true;
				green[xi - 1][y] = true;
				break;
			}
			if (xi == 5)
			{
				green[xi - 1][y] = true;
				green[xi][y] = true;
				break;
			}
		}
		//blue(x, x+1 확인)
		for (int yi = 2; yi < 6; ++yi) {
			if ((blue[x][yi] == true) || (blue[x+1][yi] == true))
			{
				blue[x][yi - 1] = true;
				blue[x + 1][yi - 1] = true;
				break;
			}
			if (yi == 5)
			{
				blue[x][yi] = true;
				blue[x + 1][yi] = true;
				break;
			}
		}
	}
}


void fill_empty(bool gb, int pos)
{//지워진 개수만큼 아래로 이동시키는 함수
	if (gb == 0) //green
	{
		for (int xi = pos; xi > 0; --xi) {
			green[xi][0] = green[xi - 1][0];
			green[xi][1] = green[xi - 1][1];
			green[xi][2] = green[xi - 1][2];
			green[xi][3] = green[xi - 1][3];
		}
		green[0][0] = false;
		green[0][1] = false;
		green[0][2] = false;
		green[0][3] = false;
	}
	else //blue
	{
		for (int yi = pos; yi > 0; --yi) {
			blue[0][yi] = blue[0][yi - 1];
			blue[1][yi] = blue[1][yi - 1];
			blue[2][yi] = blue[2][yi - 1];
			blue[3][yi] = blue[3][yi - 1];
		}
		blue[0][0] = false;
		blue[1][0] = false;
		blue[2][0] = false;
		blue[3][0] = false;
	}
}


void check_line()
{//row 와 col 확인하고 지우는 함수
	//green
	for (int xi = 5; xi > 1;) {
		bool etrue = true;
		for (int yi = 0; yi < 4; ++yi) {
			if (green[xi][yi] == false)
			{
				etrue = false;
				break;
			}	
		}
		if (etrue == true)
		{
			for (int yi = 0; yi < 4; ++yi) green[xi][yi] = false;
			point += 1;
			eblock += 4;
			fill_empty(0, xi);
		}
		else
			--xi;
	}
	for (int xi = 1; xi >= 0;)
	{
		bool etrue = false;
		for (int yi = 0; yi < 4; ++yi)
		{
			if (green[xi][yi] == true)
			{
				etrue = true;
				break;
			}
		}
		if (etrue == true) {
			//for (int yi = 0; yi < 4; ++yi)
			//{
			//	if (green[xi][yi] == true)
			//	{
			//		eblock += 1;
			//		green[xi][yi] = false;
			//	}
			//}
			for (int yi = 0; yi < 4; ++yi)
			{
				if (green[5][yi] == true)
				{
					eblock += 1;
					green[5][yi] = false;
				}
			}
			fill_empty(0, 5);
		}
		else
			--xi;
	}

	//blue
	for (int yi = 5; yi > 1;) {
		bool etrue = true;
		for (int xi = 0; xi < 4; ++xi) {
			if (blue[xi][yi] == false)
			{
				etrue = false;
				break;
			}
		}
		if (etrue == true)
		{
			for (int xi = 0; xi < 4; ++xi) blue[xi][yi] = false;
			point += 1;
			eblock += 4;
			fill_empty(1, yi);
		}
		else
			--yi;
	}
	for (int yi = 1; yi >=0;)
	{
		bool etrue = false;
		for (int xi = 0; xi < 4; ++xi)
		{
			if (blue[xi][yi] == true)
			{
				etrue = true;
				break;
			}
		}
		if (etrue == true) {
			//for (int xi = 0; xi < 4; ++xi) {
			//	if (blue[xi][yi] == true)
			//	{
			//		blue[xi][yi] = false;
			//		eblock += 1;
			//	}
			//}
			for (int xi = 0; xi < 4; ++xi) {
				if (blue[xi][5] == true)
				{
					blue[xi][5] = false;
					eblock += 1;
				}
			}
			fill_empty(1, 5);
		}
		else
			--yi;
	}
}



int main()
{
	int N;
	cin >> N;

	int tmpt, tmpx, tmpy;
	int ablock = 0;
	for (int i = 0; i < N; ++i)
	{
		cin >> tmpt >> tmpx >> tmpy;
		down_block(tmpt, tmpx, tmpy);

		//for (int xi = 0; xi < 6; ++xi) {
		//	for (int yi = 0; yi < 4; ++yi)
		//	{
		//		cout << green[xi][yi];
		//	}
		//	cout << endl;
		//}cout << endl;
		//for (int xi = 0; xi < 4; ++xi){
		//	for (int yi = 0; yi < 6; ++yi) {
		//		cout << blue[xi][yi];
		//	}
		//	cout << endl;
		//}cout << endl;

		check_line();

		//for (int xi = 0; xi < 6; ++xi) {
		//	for (int yi = 0; yi < 4; ++yi)
		//	{
		//		cout << green[xi][yi];
		//	}
		//	cout << endl;
		//}cout << endl;
		//for (int xi = 0; xi < 4; ++xi) {
		//	for (int yi = 0; yi < 6; ++yi) {
		//		cout << blue[xi][yi];
		//	}
		//	cout << endl;
		//}cout << endl;

		if (tmpt == 1) ablock += 2;
		else ablock += 4;
	}
	cout << point << endl << ablock - eblock << endl;
	return 0;
}