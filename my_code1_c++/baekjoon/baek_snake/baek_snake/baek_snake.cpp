#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int n, k, l;

//��
typedef struct {
	int x, y;
	int dir = 1; //ó���� �����
}body;
vector <body> snake;

//���
typedef struct {
	int x, y;
}pos;
vector <pos> apple;

//����(������)
typedef struct {
	int t;
	char dir;
}dir_;
queue <dir_> mov;

int dirx[4] = { -1,0,1,0 }, diry[4] = { 0,1,0,-1 }; //�������
int left_[4] = { 3,0,1,2 }, right_[4] = { 1,2,3,0 };  //ȸ�� ����

int simulate()
{
	int time = 0;
	snake.push_back(body{ 1,1,1 });//��, ��, �����
	while (1)
	{
		time++;
		
		body tail;
		for (auto s = snake.begin(); s != snake.end(); s++) //�� �̵�
		{ 
			if (s == snake.end() - 1)
			{
				tail.x = (*s).x;
				tail.y = (*s).y;
				tail.dir = (*s).dir;
			}
			if (snake[0].x == (*s).x && snake[0].y == (*s).y && s != snake.begin())
			{
				return time;
			}
			(*s).x += dirx[(*s).dir];
			(*s).y += diry[(*s).dir];
		}

		int mem = snake[0].dir; 
		for (auto s = snake.begin() + 1; s != snake.end(); s++) //�� ���� ����
		{ 
			if (mem != (*s).dir)
			{
				int temp = (*s).dir;
				(*s).dir = mem;
				mem = temp;
			}
		}

		if (snake[0].x <= 0 || snake[0].x > n || snake[0].y <= 0 || snake[0].y > n) //���� �ε������� Ȯ��
		{
			return time;
		}

		for (auto a = apple.begin(); a != apple.end();) //��� ���� Ȯ��
		{
			if ((*a).x == snake[0].x && (*a).y == snake[0].y) //���� ���̰� �þ
			{
				snake.push_back(body{ tail.x, tail.y, tail.dir });
				a = apple.erase(a);
				break;
			}
			else
				a++;
		}

		if (!mov.empty())
		{
			if (time == mov.front().t)//��Ӹ� ���� ��ȯ
			{ 
				if (mov.front().dir == 'L') //����
				{
					snake[0].dir = left_[snake[0].dir];
				}
				else //������
				{
					snake[0].dir = right_[snake[0].dir];
				}
				mov.pop();
			}
		}
	}
}

int main()
{
	cin >> n; //����
	cin >> k; //��� ����
	int x, y;
	for (int ki = 0; ki < k; ki++)
	{
		cin >> x >> y;
		apple.push_back(pos{ x,y });
	}

	cin >> l; //������
	int t;
	char dir;
	for (int li = 0; li < l; li++)
	{
		cin >> t >> dir;
		mov.push(dir_{ t,dir });
	}
	cout << simulate() << endl;
	return 0;
}

