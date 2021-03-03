//���� ��ȣ	���̵�	����	���	�޸�	�ð�	���	�ڵ� ����	������ �ð�
//26895084	nh9k	20061	�¾ҽ��ϴ�!!2016	8	C++17 / ����	5046	11�� ��
//���̳뵵�̳�2
//Ǯ�� �ð� �� 3~4�ð�
//�ùķ��̼� ����
//������ ��Ȯ�ϰ� �����Ǿ� ���� �ʾƼ� + ������ ���� �κ��� �־ + ������ �κ��� ���Ƽ� �����ɸ�
//1. ������ �������� ������ ��ĭ���� �մ���
//2. 1������ ���� �κп� ä������ 5���� ������ �������� �������, �ٽ� 1������ �˻��� ���� 0���ο� ���� �־����� Ȯ���ؾ��Ѵ�.
//3. ���� ��ܼ� �������� ���� �� ����, 0������ ���� false�� �־���� �Ѵ�.
//4. ���� �κп� ���� �־ 5������ ������ ���� ���, �̰��� ������ �������� �ʰ� ������ ��Ͽ��� �����Ѵ�.


#include <iostream>
using namespace std;
bool green[6][4], blue[4][6];
int point, eblock;


void down_block(int t, int x, int y)
{//�Էµ� ���� �Ʒ��� �̵��ϴ� �Լ�
	if (t == 1)
	{
		//green(y����)
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
		//blue(x����)
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
		//green(y, y+1 Ȯ��)
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
		//blue(x����, )
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
		//green(y����)
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
		//blue(x, x+1 Ȯ��)
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
{//������ ������ŭ �Ʒ��� �̵���Ű�� �Լ�
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
{//row �� col Ȯ���ϰ� ����� �Լ�
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