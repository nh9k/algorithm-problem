#include<iostream>
#include<algorithm>
//#include<cmath>
using namespace std;
int n, k, number[28];
int sortnum[28], sidx; //�迭 �̿�

/*�߰�*/
#include <set>
set <int, greater<int>> setnum; //�������� set �̿�

#include <vector> //https://dpdpwl.tistory.com/39
vector <int> vecnum;

bool desc(int a, int b) {
	return a > b;
}

void makenum1() //n/4���� ���ļ� ���ڸ� ����� �Լ�
{
	int multiple = n / 4; //�Ѻ��� ���� ����
	int calpow = multiple-1;
	sidx = 0;
	for (int i = 0; i < 28; i++) sortnum[i] = 0; //�ʱ�ȭ

	for (int i = 0; i < multiple; i++) //ȸ����
	{
		for (int j = i; j < n + i; j++)
		{
			if (calpow < 0)
			{
				calpow = multiple - 1; //16�� �������� �ڸ��� ���� �ʱ�ȭ
				sidx++;
			}
			if (j > n - 1) sortnum[sidx] += number[j - n] * pow(16, calpow);
			else sortnum[sidx] += number[j] * pow(16, calpow);
			calpow--;		
		}
	}
}

int result1() //���� �Ŀ� �ߺ� �����ϰ� k��° ���� �����ϴ� �Լ�
{
	sort(sortnum, sortnum+sidx+1, desc); //����
	//for (int i = 0; i < sidx + 1; i++) printf("num:: %d\n", sortnum[i]);
	int mem = sortnum[0];
	for (int i = 1; i < sidx + 1; i++)
	{
		if (mem == sortnum[i]) 
		{
			//k++;	
			sortnum[i] = 0;
		}
		mem = sortnum[i];
	}
	sort(sortnum, sortnum + sidx + 1, desc);
	return sortnum[k-1];
}

void makenum2() //n/4���� ���ļ� ���ڸ� ����� �Լ� - set �̿�
{
	int multiple = n / 4; //�Ѻ��� ���� ����
	int calpow = multiple - 1;
	int multinum = 0;
	setnum.clear(); //�ʱ�ȭ

	for (int i = 0; i < multiple; i++) //ȸ����
	{
		for (int j = i; j < n + i; j++)
		{
			if (calpow < 0)
			{
				setnum.insert(multinum);
				multinum = 0;
				calpow = multiple - 1; //16�� �������� �ڸ��� ���� �ʱ�ȭ
			}
			if (j > n - 1) multinum += number[j - n] * pow(16, calpow);
			else multinum += number[j] * pow(16, calpow);
			calpow--;
		}
	}
	setnum.insert(multinum); //���������� multinum �־������
}

int result2() //���� �Ŀ� �ߺ� �����ϰ� k��° ���� �����ϴ� �Լ� - set �̿�
{
	int i = 0;
	for (auto x : setnum)
	{		
		if (i == k - 1) return x;
		i++;
	}
	//return setnum.begin() + k - 1;*/
	//return 0;
}

void makenum3() //n/4���� ���ļ� ���ڸ� ����� �Լ� - vector �̿�
{
	int multiple = n / 4; //�Ѻ��� ���� ����
	int calpow = multiple - 1;
	int multinum = 0;
	vecnum.clear();  //�ʱ�ȭ

	for (int i = 0; i < multiple; i++) //ȸ����
	{
		for (int j = i; j < n + i; j++)
		{
			if (calpow < 0)
			{
				vecnum.push_back(multinum);
				multinum = 0;
				calpow = multiple - 1; //16�� �������� �ڸ��� ���� �ʱ�ȭ
			}
			if (j > n - 1) multinum += number[j - n] * pow(16, calpow);
			else multinum += number[j] * pow(16, calpow);
			calpow--;
		}
	}
	vecnum.push_back(multinum); //���������� multinum �־������
}

int result3() //���� �Ŀ� �ߺ� �����ϰ� k��° ���� �����ϴ� �Լ� - unique , vector �̿�
{
	sort(vecnum.begin(), vecnum.end(), desc); //����
	vecnum.erase(unique(vecnum.begin(), vecnum.end()), vecnum.end());
	return vecnum[k - 1];
}


int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("sample_input.txt", "r", stdin);
	scanf("%d", &T);

	for (test_case = 1; test_case <= T; ++test_case)
	{
		scanf("%d %d\n", &n, &k);
		
		char num = 0;
		for (int i = 0; i < n; i++)
		{
			scanf("%c", &num);

			if (num >= 'A')
				number[i] = num - 'A' + 10;
			else
				number[i] = num - '0';
		}
		makenum2();
		printf("#%d %d\n", test_case, result2());
	}
	return 0;//��������� �ݵ�� 0�� �����ؾ��մϴ�.
}