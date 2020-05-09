/*
@nh9k github
@baekjoon 1932, integer-triangle
채점 번호	아이디	문제 번호	결과	메모리	시간	언어	코드 길이	
19698959	nh9k	1932	맞았습니다!!2644	40	C++14 / 수정	1151
*/

#include <iostream> 
#include <vector> 
#include <algorithm> //for use the max function

int main()
{
	int N;
	std::cin >> N;

	std::vector<std::vector<int>> triangle(N); //using array is more faster than vector
	int input;
	for (int n = 0; n < N; ++n) {
		for (int room = 0; room <= n; ++room) {
			std::cin >> input;
			triangle[n].push_back(input);
		}
	}

	//Parallel and down calculation with method:DP 
	//using array is more faster than vector
	//and don't care DP vector because we can save in triangle vector 

	for (int n = 1; n < N; ++n) {
		for (int room = 0; room <= n; ++room) {
			if (room == 0) {
				triangle[n][room] = triangle[n - 1][room] + triangle[n][room];
			}
			else if (room == n) {
				triangle[n][room] = triangle[n - 1][room - 1] + triangle[n][room];
			}
			else {
				triangle[n][room] = std::max(triangle[n - 1][room - 1], triangle[n - 1][room]) + triangle[n][room];
			}
		}
	}

	//result is max value of last child value that make up tree 
	int result = 0;
	for (int room = 0; room <= N - 1; ++room) {
		result = std::max(result, triangle[N - 1][room]);
	}

	//print result
	std::cout << result;
}

/*
@nh9k github
채점 번호	아이디	문제 번호	결과	메모리	시간	언어	코드 길이	
19698877	nh9k	1932	맞았습니다!!3304	44	C++14 / 수정	1028
*/

/*
#include <iostream> 
#include <vector> 
#include <algorithm> //for use the max function

int main()
{
	int N;
	std::cin >> N;

	std::vector<std::vector<int>> triangle(N); //using array is more faster than vector
	int input;
	for (int n = 0; n < N; ++n) {
		for (int room = 0; room <= n; ++room) {
			std::cin >> input;
			triangle[n].push_back(input);
		}
	}

	//Parallel and down calculation with method:DP 
	std::vector<std::vector<int>> DP(N); //using array is more faster than vector
										 //and don't care DP vector because we can save in triangle vector 
	DP[0].push_back(triangle[0][0]);
	for (int n = 1; n < N; ++n) {
		for (int room = 0; room <= n; ++room) {
			if (room == 0) {
				DP[n].push_back(DP[n - 1][room] + triangle[n][room]);
			}
			else if (room == n) {
				DP[n].push_back(DP[n - 1][room - 1] + triangle[n][room]);
			}
			else {
				DP[n].push_back(std::max(DP[n - 1][room - 1], DP[n - 1][room]) + triangle[n][room]);
			}
		}
	}

	//result is max value of last child value that make up tree 
	int result = 0;
	for (int room = 0; room <= N - 1; ++room) {
		result = std::max(result, DP[N - 1][room]);
	}

	//print result
	std::cout << result;
}
*/