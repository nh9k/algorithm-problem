//최대한 풀어서 수식을 작성하자....

#include<iostream>

using namespace std;

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{
		double d, l, n;
        cin >> d >> l >> n;
        cout << "#" << test_case <<  " " << int(n * d + ( n * d * l * (n-1) / 200.0))<< endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}