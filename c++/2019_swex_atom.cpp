#include<iostream>
#include<vector>
using namespace std;

typedef struct atoms
{
	int x, y, dir, k; //x,y,이동방향, 에너지
}atoms;
//atoms atom[1001]; //1~1000개이므로
int n, energy, map[4001][4001]; //원자 개수 //energy 전체 //끝에서 끝으로 이동하면 (-1000~1000) + 0.5부분에서 부딪히는 곳 처리 (*2)
int dx[4] = { 0,0, -1,1 }, dy[4] = { 1,-1,0,0 };//상하좌우 //쉼표를 안넣음
vector <atoms> atom;

int move() //원자들이 움직이면서 소멸하고 에너지를 방출하는 함수
{
	energy = 0;
	while (!atom.empty()) //모든 원자가 소멸할 때까지
	{
		int vsize = (int)atom.size();
		for (int i = 0; i < vsize; i++) //원자 이동
		{
			map[atom[i].x][atom[i].y] = 0; //지나간 곳을 0으로 마무리
			atom[i].x += dx[atom[i].dir];
			atom[i].y += dy[atom[i].dir];

			//범위를 벗어나고, 계속가도 다른 원자와 만날 수 없음: 범위 체크
			if (atom[i].x > 4000 || atom[i].x < 0 || atom[i].y> 4000 || atom[i].y < 0)
				atom[i].k = 0; //그냥 소멸 //따로 에너지에 합쳐줄 필요없음

			else //맵에 표시
				map[atom[i].x][atom[i].y] += atom[i].k;
		}

		for (int i = 0; i < vsize; i++) //원자가 부딪힌 곳 처리
		{
			if (!atom[i].k) continue; //이미 범위를 벗어나서 죽은 원자는 넘어감

			if (map[atom[i].x][atom[i].y] != atom[i].k) //원자가 2개 이상으로 한 위치에 있을 때
			{ //아직 검사하지 않은 원자들도 미리 energy에 추가될 수 있으니 !=로 한다
				energy += map[atom[i].x][atom[i].y];
				map[atom[i].x][atom[i].y] = 0; //추가한 곳은 0으로 초기화
				atom[i].k = 0; //소멸
			}
		}

		//시간 초과를 피하기 위한 핵심은 vector나 queue를 선언해서 이전의 원자들은 제거하고 다음을 처리하는 것
		//임시 벡터를 선언하여 내부에 넣어주고 다시 원래의 벡터에 죽은 원자를 제외하고 넣어줌
		vector <atoms> temp;
		temp.assign(atom.begin(), atom.end()); //원래 벡터 복사
		atom.clear(); //원래 벡터 지워줌

		for (int i = 0; i < vsize; i++)
			if (temp[i].k != 0) //소멸하지 않은 원자이면
				atom.push_back(temp[i]); //다시 원자 index를 넣어줌
	}
	return energy;
}

int main(int argc, char** argv)
{
	int test_case, T;
	freopen("sample_input - 복사본.txt", "r", stdin);
	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case)
	{
		scanf("%d", &n);

		atoms input;
		for (int i = 0; i < n; i++)
		{
			scanf("%d %d %d %d", &input.x, &input.y, &input.dir, &input.k);
			input.x *= 2;
			input.y *= 2;
			input.x += 2000;
			input.y += 2000;
			atom.push_back(input);
		}
		printf("#%d %d\n", test_case, move());
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}