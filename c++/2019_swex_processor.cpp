#include <iostream>

int n, map[12][12], cn, maxcore, minleng, chkcore, chkleng;
typedef struct pos
{
	int x, y, minimum[4];
	bool dir[4], no; //�������, �����ڸ� ���μ���
}pos;
pos core[12];

void fcheckdir()
{
	for (int i = 0; i < cn; i++)
	{
		//������� ������ �Ÿ� ����ؼ� �켱������ üũ�� ���� minimum[4]�� ������� �־��ֱ�
		int calx = core[i].x;
		int caly = core[i].y;
		
		if (calx >= n / 2) calx = n - 1 - calx;
		if (caly >= n / 2) caly = n - 1 - caly;

		if (calx <= caly) //�� ���� ���� �����ڸ��� ���� �Ÿ��� �� �����
		{ //x�� �� ���� ���
			if (core[i].x >= n / 2)
			{//[����Ž��]=����
				core[i].minimum[0] = 2;
				core[i].minimum[3] = 0;
			}
			else
			{
				core[i].minimum[0] = 0;
				core[i].minimum[3] = 2;
			}
			if (core[i].y >= n / 2)
			{
				core[i].minimum[1] = 1;
				core[i].minimum[2] = 3;
			}
			else
			{
				core[i].minimum[1] = 3;
				core[i].minimum[2] = 1;
			}
		}
		else { //y�� �� ���� ���
			if (core[i].x >= n / 2)
			{//[����Ž��]=����
				core[i].minimum[1] = 2;
				core[i].minimum[2] = 0;
			}
			else
			{
				core[i].minimum[1] = 0;
				core[i].minimum[2] = 2;
			}
			if (core[i].y >= n / 2)
			{
				core[i].minimum[0] = 1;
				core[i].minimum[3] = 3;
			}
			else
			{
				core[i].minimum[0] = 3;
				core[i].minimum[3] = 1;
			}
		}

		for (int j = 0; j < cn; j++)
		{
			if (core[i].x == 0 || core[i].x == n - 1 || core[i].y == 0 || core[i].y == n - 1) 
			{//�����ڸ��� �ִ� ���
				core[i].no = true;
				break;
			}	
			if (i == j) continue; //���� �ھ�� ����ϸ� �ȵ�
			else 
			{
				if (core[i].y == core[j].y) //���� �����ٿ� �ִ� ���
				{
					if (core[i].x > core[j].x) core[i].dir[0] = false; //�� ���� �Ұ�
					else core[i].dir[2] = false; //�� ���� �Ұ�
				}
				else if (core[i].x == core[j].x) //���� �����ٿ� �ִ� ���
				{
					if (core[i].y > core[j].y) core[i].dir[3] = false; //�� ���� �Ұ�
					else core[i].dir[1] = false; //�� ���� �Ұ�
				}
			}
		}
	}
	for (int i = 0; i < cn; i++)
	{
		if (core[i].dir[0] == false && core[i].dir[1] == false && core[i].dir[2] == false && core[i].dir[3] == false)
		{//��� ������ �ٸ� �ھ�� ���� ���
			core[i].no = true;
		}
	}
}

int chkvisit(int whatcore, int idx)//0: �� �� ���� ��, 1: �� �� �ִ� ��, 2: üũ�� �ʿ䰡 ���� �ھ�
{    
	idx = core[whatcore].minimum[idx];
	if (core[whatcore].no) return 2; //üũ�� �ʿ䰡 ���� �ھ��̸�
	if (!core[whatcore].dir[idx]) return 0; //�ٸ� �ھ�� ���� ������ �����̸�

	if (idx == 0) {//����� üũ + ���� üũ
		for (int x = core[whatcore].x - 1; x >= 0; x--)
		{
			if (map[x][core[whatcore].y] == 0){ //�ƹ��͵� ���� ��
				map[x][core[whatcore].y] = whatcore; 
				chkleng++;
			}
			else if (map[x][core[whatcore].y] == whatcore) { //�ڱⰡ �̹� �Դ� �� ��
				map[x][core[whatcore].y] = 0; 
				chkleng--;
			}
			else { //�̹� �ٸ� �ھ �±�
				for (int xr = x + 1; xr < core[whatcore].x; xr++) { //�ٽ� �ǵ��� ����
					map[xr][core[whatcore].y] = 0; chkleng--;
				}
				return 0; //0��ȯ
			}
		}
	}
	else if (idx == 1) { //����� üũ + ���� üũ
		for (int y = core[whatcore].y + 1; y <= n-1; y++)
		{
			if (map[core[whatcore].x][y] == 0) {
				map[core[whatcore].x][y] = whatcore; //�ƹ��͵� ���� ��
				chkleng++;
			}
			else if (map[core[whatcore].x][y] == whatcore) {
				map[core[whatcore].x][y] = 0; //�ڱⰡ �̹� �Դ� �� ��
				chkleng--;
			}
			else { //�̹� �ٸ� �ھ �±�
				for (int yr = y - 1; yr > core[whatcore].y; yr--) { //�ٽ� �ǵ��� ����
					map[core[whatcore].x][yr] = 0; chkleng--;
				}
				return 0; //0��ȯ
			}
		}
	}
	else if (idx == 2) { //�� ���� üũ
		for (int x = core[whatcore].x + 1; x <=n-1 ; x++)
		{
			if (map[x][core[whatcore].y] == 0) { //�ƹ��͵� ���� ��
				map[x][core[whatcore].y] = whatcore; 
				chkleng++;
			}
			else if (map[x][core[whatcore].y] == whatcore) { //�ڱⰡ �̹� �Դ� �� ��
				map[x][core[whatcore].y] = 0; 
				chkleng--;
			}
			else { //�̹� �ٸ� �ھ �±�
				for (int xr = x - 1; xr > core[whatcore].x; x--) { //�ٽ� �ǵ��� ����
					map[xr][core[whatcore].y] = 0; chkleng--;
				}
				return 0;//0��ȯ
			}
		}
	}
	else { //�� ���� üũ
		for (int y = core[whatcore].y - 1; y >= 0; y--)
		{
			if (map[core[whatcore].x][y] == 0) { //�ƹ��͵� ���� ��
				map[core[whatcore].x][y] = whatcore; 
				chkleng++;
			}
			else if (map[core[whatcore].x][y] == whatcore) { //�ڱⰡ �̹� �Դ� �� ��
				map[core[whatcore].x][y] = 0; 
				chkleng--;
			}
			else { //�̹� �ٸ� �ھ �±�
				for (int yr = y + 1; yr < core[whatcore].y; yr++) { //�ٽ� �ǵ��� ����
					map[core[whatcore].x][yr] = 0; chkleng--;
				}
				return 0;//0��ȯ
			}
		}
	}
	return 1;//1��ȯ
}

void dfs(int cnt)
{
	if (cnt >= cn)
	{
		if (maxcore <= chkcore)
		{
			maxcore = chkcore;
			if (minleng > chkleng)
				minleng = chkleng;			
		}
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		int chk = chkvisit(cnt, i);
		if(chk!=2 &&chk!=1) continue; //0��ȯ�� ���  //�̹� �ٸ� �ھ �±��̰ų� �ٸ� �ھ�� �������
		chkcore++;
		dfs(cnt + 1); //�� �ھ ���� 4���⿡ ���ؼ� dfs ���� �ĸ� ��� �� �� �ΰ�
		chkvisit(cnt, i); chkcore--;
	}
}
int main()
{
	freopen("sample_input.txt", "r", stdin);
	int t;
	scanf("%d", &t);
	for (int tc = 0; tc < t; tc++)
	{
		scanf("%d", &n);
		cn = 0;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				scanf("%d", &map[i][j]);
				if (map[i][j])
				{
					core[cn].x = i;  core[cn].y = j;
					cn++;
				}
			}
		}
		for (int i = 0; i < cn; i++)
		{
			core[i].dir[0] = true; core[i].dir[1] = true; core[i].dir[2] = true; core[i].dir[3] = true;
			core[i].no = false;
		}
		fcheckdir(); //ó������ ������� ���⿡ ���ؼ� �� �� �ִ��� üũ����
		maxcore = 0, minleng = 144, chkcore = 0, chkleng = 0;
		dfs(0);

		printf("#%d %d\n", tc + 1, minleng);
	}
	return 0;
}