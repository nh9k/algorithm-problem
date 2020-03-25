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
	vector<int> answer; //vector<int> answer(prices.size()); �ϸ� ũ�� �Ҵ� ������, ansarr ���ʿ� ������
	vector<int> stk; //vector�� stack ó�� ���

	for (int pi = 0; pi < prices.size(); ++pi)
	{
		if (stk.empty())
		{
			stk.push_back(pi); 
		}
		else
		{
			//���������� ����̹Ƿ� �����Ϸ��� ���ʿ��� ���������� �����Ƿ� empty �ҽ� �ڵ��ٰ� ��ġ�� ����
			while (prices[stk.back()] > prices[pi]) 
			{
				ansarr[stk.back()] = (pi - stk.back());
				stk.pop_back();
				if (stk.empty()) break;
			}
			if (stk.empty()) stk.push_back(pi); //�� �κ� ������ core dumped(out of range�� ��� �߻���!!)
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
//ä���� �����մϴ�.
//��Ȯ��  �׽�Ʈ
//�׽�Ʈ 1 ��	���(0.01ms, 3.77MB)
//�׽�Ʈ 2 ��	���(0.01ms, 3.78MB)
//�׽�Ʈ 3 ��	���(0.02ms, 3.79MB)
//�׽�Ʈ 4 ��	���(0.02ms, 3.86MB)
//�׽�Ʈ 5 ��	���(0.03ms, 3.81MB)
//�׽�Ʈ 6 ��	���(0.00ms, 3.74MB)
//�׽�Ʈ 7 ��	���(0.01ms, 3.81MB)
//�׽�Ʈ 8 ��	���(0.02ms, 3.8MB)
//�׽�Ʈ 9 ��	���(0.01ms, 3.8MB)
//�׽�Ʈ 10 ��	���(0.02ms, 3.93MB)
//ȿ����  �׽�Ʈ
//�׽�Ʈ 1 ��	���(1.29ms, 5.36MB)
//�׽�Ʈ 2 ��	���(0.97ms, 4.86MB)
//�׽�Ʈ 3 ��	���(1.34ms, 5.62MB)
//�׽�Ʈ 4 ��	���(1.10ms, 4.96MB)
//�׽�Ʈ 5 ��	���(0.73ms, 4.46MB)
//ä�� ���
//��Ȯ�� : 66.7
//	ȿ���� : 33.3
//	�հ� : 100.0 / 100.0

//first_my_solution()
//ä���� �����մϴ�.
//��Ȯ��  �׽�Ʈ
//�׽�Ʈ 1 ��	���(0.01ms, 3.8MB)
//�׽�Ʈ 2 ��	���(0.01ms, 3.83MB)
//�׽�Ʈ 3 ��	���(0.03ms, 3.81MB)
//�׽�Ʈ 4 ��	���(0.03ms, 3.82MB)
//�׽�Ʈ 5 ��	���(0.03ms, 3.77MB)
//�׽�Ʈ 6 ��	���(0.01ms, 3.82MB)
//�׽�Ʈ 7 ��	���(0.02ms, 3.91MB)
//�׽�Ʈ 8 ��	���(0.02ms, 3.93MB)
//�׽�Ʈ 9 ��	���(0.01ms, 3.82MB)
//�׽�Ʈ 10 ��	���(0.03ms, 3.82MB)
//ȿ����  �׽�Ʈ
//�׽�Ʈ 1 ��	���(1.86ms, 5.92MB)
//�׽�Ʈ 2 ��	���(1.42ms, 5.54MB)
//�׽�Ʈ 3 ��	���(2.00ms, 6.34MB)
//�׽�Ʈ 4 ��	���(1.62ms, 5.85MB)
//�׽�Ʈ 5 ��	���(1.09ms, 5.05MB)
//ä�� ���
//��Ȯ�� : 66.7
//	ȿ���� : 33.3
//	�հ� : 100.0 / 100.0

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