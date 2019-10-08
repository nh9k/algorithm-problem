#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <bitset>
using namespace std;

vector<string> solution1(int n, vector<int> arr1, vector<int> arr2) {
	stack <int> binary_x, binary_y;
	vector<string> answer;

	for (int i = 0; i < n; i++)
	{
		int x = arr1[i];
		int y = arr2[i];

		//* 배열 1에 대해 이진화
		while (x != 1)
		{
			binary_x.push(x % 2);
			cout << x % 2;
			x /= 2;
		}
		binary_x.push(1);
		cout << 1;
		while (binary_x.size() < n)
		{
			binary_x.push(0);
			cout << 0;
		}
		cout << endl;
		//* 배열 2에 대해 이진화
		while (y != 1)
		{
			binary_y.push(y % 2);
			cout << y % 2;
			y /= 2;
		}
		binary_y.push(1);
		cout << 1;
		while (binary_y.size() < n)
		{
			binary_y.push(0);
			cout << 0;
		}
		cout << endl;
		//* 스택을 다시 빼면서 검사 & 스트링 만들기
		string input = "x";
		while (!binary_x.empty())
		{
			if (binary_x.top() || binary_y.top())
			{ //둘 중하나라도 1이 섞였으면
				if (input == "x") input = "#";
				else input += "#";
			}
			else
			{
				if (input == "x") input = " ";
				else input += " ";
			}
			binary_x.pop(), binary_y.pop();
		}

		//* 스트링 push
		answer.push_back(input);
		cout << input << endl;
	}
	return answer;
}

vector<string> solution(int n, vector<int> arr1, vector<int> arr2) { //https://simsimjae.tistory.com/85
	vector<string> answer;
	for (int i = 0; i < n; i++)
	{
		int map = arr1[i] | arr2[i];
		cout << map << endl;
		cout << bitset<5>(map) << endl;
		bitset<16> b_map(map);

		string input = "x";
		for (int i = n - 1; i >= 0; i--)
		{
			cout << b_map[i];
			if (b_map[i] == 0)
			{
				if (input == "x") input = " ";
				else input += " ";			
			}			
			else
			{
				if (input == "x") input = "#";
				else input += "#";
			}
		}

		cout << endl;
		answer.push_back(input);
	}
	return answer;
}

//vector<string> solution(int n, vector<int> arr1, vector<int> arr2) {
//	//stack <int> binary_x, binary_y;
//	bool binary_x[16], binary_y[16];
//	vector<string> answer;
//
//	for (int i = 0; i < n; i++)
//	{
//		int x = arr1[i];
//		int y = arr2[i];
//
//		//* 배열 1에 대해 이진화
//		int which = 0;
//		while (x != 1)
//		{
//			binary_x[which] = x % 2;
//			x /= 2;
//			which++;
//		}
//		binary_x[which] = 1;
//		which++;
//		while (which <= n - 1)
//		{
//			binary_x[which] = 0;
//			which++;
//		}
//
//		//* 배열 2에 대해 이진화
//		which = 0;
//		while (y != 1)
//		{
//			binary_y[which] = y % 2;
//			y /= 2;
//			which++;
//		}
//		binary_y[which] = 1;
//		which++;
//		while (which <= n - 1)
//		{
//			binary_y[which] = 0;
//			which++;
//		}
//
//		//* 스택을 다시 빼면서 검사 & 스트링 만들기
//		string input = "x";
//		//for (int i = which - 1; i >= 0; i--)
//		//{
//		//	cout << binary_x[i];
//
//		//}
//		//cout << endl;
//		//for (int i = which - 1; i >= 0; i--)
//		//{
//		//	cout << binary_y[i];
//
//		//}
//		//cout << endl;
//		for (int i = which-1; i >= 0; i--)
//		{
//			if (binary_x[i] || binary_y[i])
//			{ //둘 중하나라도 1이 섞였으면
//				if (input == "x") input = "#";
//				else input += "#";
//			}
//			else
//			{
//				if (input == "x") input = " ";
//				else input += " ";
//			}
//			//binary_x.pop(), binary_y.pop();
//		}
//
//		//* 스트링 push
//		answer.push_back(input);
//		cout << input << endl;
//	}
//	return answer;
//}

int main()
{
	solution(5, { 9, 20, 28, 18, 11 }, { 30, 1, 21, 17, 28 });
	//cout << 0 % 2;
	//cout << 0 / 2;

	bitset<10> b(88);//00010 11000

	for (int i = 0; i < b.size(); i++)
	{ //거꾸로 출력됨
		cout << i << ":" << b[i] << '\n';
	}
}