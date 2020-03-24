#include<iostream>
#include<algorithm>
//#include<cmath>
using namespace std;
int n, k, number[28];
int sortnum[28], sidx; //배열 이용

/*추가*/
#include <set>
set <int, greater<int>> setnum; //내림차순 set 이용

#include <vector> //https://dpdpwl.tistory.com/39
vector <int> vecnum;

bool desc(int a, int b) {
	return a > b;
}

void makenum1() //n/4개씩 합쳐서 숫자를 만드는 함수
{
	int multiple = n / 4; //한변의 숫자 개수
	int calpow = multiple-1;
	sidx = 0;
	for (int i = 0; i < 28; i++) sortnum[i] = 0; //초기화

	for (int i = 0; i < multiple; i++) //회전수
	{
		for (int j = i; j < n + i; j++)
		{
			if (calpow < 0)
			{
				calpow = multiple - 1; //16의 제곱수를 자릿수 마다 초기화
				sidx++;
			}
			if (j > n - 1) sortnum[sidx] += number[j - n] * pow(16, calpow);
			else sortnum[sidx] += number[j] * pow(16, calpow);
			calpow--;		
		}
	}
}

int result1() //정렬 후에 중복 제외하고 k번째 수를 리턴하는 함수
{
	sort(sortnum, sortnum+sidx+1, desc); //조심
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

void makenum2() //n/4개씩 합쳐서 숫자를 만드는 함수 - set 이용
{
	int multiple = n / 4; //한변의 숫자 개수
	int calpow = multiple - 1;
	int multinum = 0;
	setnum.clear(); //초기화

	for (int i = 0; i < multiple; i++) //회전수
	{
		for (int j = i; j < n + i; j++)
		{
			if (calpow < 0)
			{
				setnum.insert(multinum);
				multinum = 0;
				calpow = multiple - 1; //16의 제곱수를 자릿수 마다 초기화
			}
			if (j > n - 1) multinum += number[j - n] * pow(16, calpow);
			else multinum += number[j] * pow(16, calpow);
			calpow--;
		}
	}
	setnum.insert(multinum); //마지막까지 multinum 넣어줘야함
}

int result2() //정렬 후에 중복 제외하고 k번째 수를 리턴하는 함수 - set 이용
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

void makenum3() //n/4개씩 합쳐서 숫자를 만드는 함수 - vector 이용
{
	int multiple = n / 4; //한변의 숫자 개수
	int calpow = multiple - 1;
	int multinum = 0;
	vecnum.clear();  //초기화

	for (int i = 0; i < multiple; i++) //회전수
	{
		for (int j = i; j < n + i; j++)
		{
			if (calpow < 0)
			{
				vecnum.push_back(multinum);
				multinum = 0;
				calpow = multiple - 1; //16의 제곱수를 자릿수 마다 초기화
			}
			if (j > n - 1) multinum += number[j - n] * pow(16, calpow);
			else multinum += number[j] * pow(16, calpow);
			calpow--;
		}
	}
	vecnum.push_back(multinum); //마지막까지 multinum 넣어줘야함
}

int result3() //정렬 후에 중복 제외하고 k번째 수를 리턴하는 함수 - unique , vector 이용
{
	sort(vecnum.begin(), vecnum.end(), desc); //조심
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
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}