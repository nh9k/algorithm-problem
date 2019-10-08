#include <iostream>
using namespace std;

typedef struct {
	char map[3][3];
}CUBE;
CUBE c[6];
int clockwise[3][4] = { {4,6,3,5},{1,6,2,5}, {1,3,2,4} };

void cubing(char turn, char pm)
{
	int temp[3], topordown;

	if (turn == 'U')
		topordown = 0;
	else if (turn == 'D')
		topordown = 2;
	else if (turn == 'F')
	{

	}
	else if (turn == 'R')
	{

	}
	else if (turn == 'L')
	{

	}
	else
	{

	}

	if ((pm == '+' && topordown == 0 )||(pm == '-' && topordown == 2))
	{
		for (int idx = 0; idx < 3; idx++)
			temp[idx] = c[clockwise[0][3]].map[topordown][idx];

		for (int turning = 3; turning > 0; --turning)
			for (int idx = 0; idx < 3; idx++)
				c[clockwise[0][turning]].map[topordown][idx] = c[clockwise[0][turning - 1]].map[topordown][idx];

		for (int idx = 0; idx < 3; idx++)
			c[clockwise[0][0]].map[topordown][idx] = temp[idx];
	}
	else
	{
		for (int idx = 0; idx < 3; idx++)
			temp[idx] = c[clockwise[0][0]].map[topordown][idx];

		for (int turning = 1; turning < 4; ++turning)
			for (int idx = 0; idx < 3; idx++)
				c[clockwise[0][turning - 1]].map[topordown][idx] = c[clockwise[0][turning]].map[topordown][idx];

		for (int idx = 0; idx < 3; idx++)
			c[clockwise[0][3]].map[topordown][idx] = temp[idx];
	}
	
	
	return;
}

int main()
{
	int tc;
	cin >> tc;

	int cnt;
	char turn, pm;
	for (int t = 0; t < tc; ++t)
	{
		cin >> cnt;
		for (int cnti = 0; cnti < cnt; cnti++)
		{
			cin >> turn >> pm;
			cubing(turn, pm);
		}
			
	}
	

	return 0;
}
