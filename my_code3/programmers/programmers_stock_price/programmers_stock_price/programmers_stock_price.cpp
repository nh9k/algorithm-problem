//2020.0326
#include <string>
#include <vector>
#include <iostream>
using namespace std;

vector<int> solution(vector<int> prices)
{
	vector<int> answer(prices.size()); 
	vector<int> stk;

	for (int pi = 0; pi < prices.size(); ++pi)
	{
		while (!stk.empty() && (prices[stk.back()] > prices[pi]))
		{
			answer[stk.back()] = (pi - stk.back());
			stk.pop_back();
		}
		stk.push_back(pi);
	}

	while (!stk.empty())
	{
		answer[stk.back()] = (prices.size() - 1 - stk.back());
		stk.pop_back();
	}

	/*for (int si = 0; si < prices.size(); ++si)
		cout << answer[si];*/

	return answer;
}

int ansarr[100001];
vector<int> first_my_solution(vector<int> prices)
{
	vector<int> answer; //vector<int> answer(prices.size()); 하면 크기 할당 가능함, ansarr 쓸필요 없어짐
	vector<int> stk; //vector를 stack 처럼 사용

	for (int pi = 0; pi < prices.size(); ++pi)
	{
		if (stk.empty())
		{
			stk.push_back(pi); 
		}
		else
		{
			//절차지향적 언어이므로 컴파일러가 왼쪽에서 오른쪽으로 읽으므로 empty 소스 코드줄과 합치기 가능
			while (prices[stk.back()] > prices[pi]) 
			{
				ansarr[stk.back()] = (pi - stk.back());
				stk.pop_back();
				if (stk.empty()) break;
			}
			if (stk.empty()) stk.push_back(pi); //이 부분 때문에 core dumped(out of range일 경우 발생함!!)
			else if (prices[stk.back()] <= prices[pi])
			{
				stk.push_back(pi);
			}

		}
	}

	while (!stk.empty())
	{
		ansarr[stk.back()] = (prices.size() - 1 - stk.back());
		stk.pop_back();
	}

	for (int si = 0; si < prices.size(); ++si)
		answer.push_back(ansarr[si]);

	//for (int si = 0; si < prices.size(); ++si)
	//	cout << answer[si];


	return answer;
}

//solution()
//채점을 시작합니다.
//정확성  테스트
//테스트 1 〉	통과(0.01ms, 3.77MB)
//테스트 2 〉	통과(0.01ms, 3.78MB)
//테스트 3 〉	통과(0.02ms, 3.79MB)
//테스트 4 〉	통과(0.02ms, 3.86MB)
//테스트 5 〉	통과(0.03ms, 3.81MB)
//테스트 6 〉	통과(0.00ms, 3.74MB)
//테스트 7 〉	통과(0.01ms, 3.81MB)
//테스트 8 〉	통과(0.02ms, 3.8MB)
//테스트 9 〉	통과(0.01ms, 3.8MB)
//테스트 10 〉	통과(0.02ms, 3.93MB)
//효율성  테스트
//테스트 1 〉	통과(1.29ms, 5.36MB)
//테스트 2 〉	통과(0.97ms, 4.86MB)
//테스트 3 〉	통과(1.34ms, 5.62MB)
//테스트 4 〉	통과(1.10ms, 4.96MB)
//테스트 5 〉	통과(0.73ms, 4.46MB)
//채점 결과
//정확성 : 66.7
//	효율성 : 33.3
//	합계 : 100.0 / 100.0

//first_my_solution()
//채점을 시작합니다.
//정확성  테스트
//테스트 1 〉	통과(0.01ms, 3.8MB)
//테스트 2 〉	통과(0.01ms, 3.83MB)
//테스트 3 〉	통과(0.03ms, 3.81MB)
//테스트 4 〉	통과(0.03ms, 3.82MB)
//테스트 5 〉	통과(0.03ms, 3.77MB)
//테스트 6 〉	통과(0.01ms, 3.82MB)
//테스트 7 〉	통과(0.02ms, 3.91MB)
//테스트 8 〉	통과(0.02ms, 3.93MB)
//테스트 9 〉	통과(0.01ms, 3.82MB)
//테스트 10 〉	통과(0.03ms, 3.82MB)
//효율성  테스트
//테스트 1 〉	통과(1.86ms, 5.92MB)
//테스트 2 〉	통과(1.42ms, 5.54MB)
//테스트 3 〉	통과(2.00ms, 6.34MB)
//테스트 4 〉	통과(1.62ms, 5.85MB)
//테스트 5 〉	통과(1.09ms, 5.05MB)
//채점 결과
//정확성 : 66.7
//	효율성 : 33.3
//	합계 : 100.0 / 100.0

#include <stack>
vector<int> good_solution(vector<int> prices) {
	vector<int> answer(prices.size());
	stack<int> s;
	int size = prices.size();
	for (int i = 0; i < size; i++) {
		while (!s.empty() && prices[s.top()] > prices[i]) {
			answer[s.top()] = i - s.top();
			s.pop();
		}
		s.push(i);
	}
	while (!s.empty()) {
		answer[s.top()] = size - s.top() - 1;
		s.pop();
	}
	return answer;
}

int main(void)
{
	solution({ 1, 2, 3, 4, 3, 2, 1 });
}