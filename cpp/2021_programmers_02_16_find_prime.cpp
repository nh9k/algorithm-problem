#include <string>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;
int answer;
bool chk[10000000];
bool room_chk[8];

bool is_prime(int number)
{
    if ((number == 1) || (number == 0)) return false;
    for (int i=2; i<=sqrt(number); ++i){
        if(number % i == 0)
            return false;
    }
    return true;
}

void dfs(string numbers, int cur_n, int max_n, string cur_numbers)
{
    if (cur_n == max_n){

        if ((chk[stoi(cur_numbers)] != 1) &&
            (is_prime(stoi(cur_numbers))))
        {
            chk[stoi(cur_numbers)] = 1;
            answer += 1;
            // cout << cur_numbers << endl;
        }
        return;
    }
    for(int i=0; i<numbers.length(); ++i){
        if (room_chk[i] == 1) continue;
        
        cur_numbers += numbers[i];
        room_chk[i] = 1;
        dfs(numbers, cur_n+1, max_n, cur_numbers);
        cur_numbers.erase(cur_numbers.length()-1, cur_numbers.length());
        room_chk[i] = 0;
    }
}

int solution(string numbers) {
    answer = 0;
    for(int i=1; i<=numbers.length(); ++i)
        dfs(numbers, 0, i, "");
    return answer;
}