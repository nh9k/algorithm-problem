#include <string>
#include <vector>
#include <deque>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;
    deque <pair<int, int>> bridge;
    int cur_weights = 0;
    int iter_ = 0;
    while((truck_weights.size() != iter_) || (bridge.size() != 0)){
        answer += 1;
        
        if(bridge.size()!=0)
        {
            for(int i=0; i<bridge.size(); ++i)
            {
                bridge[i].second += 1;
            }
            
            if (bridge[bridge.size()-1].second > bridge_length)
            {
                cur_weights -= bridge[bridge.size()-1].first;
                bridge.pop_back();
            }

        }
        
        if ((iter_ < truck_weights.size()) && (cur_weights + truck_weights[iter_]) <= weight)
        {
            cur_weights += truck_weights[iter_];
            bridge.push_front(pair<int, int>(truck_weights[iter_],1));
            iter_ += 1;
        }
    }
     
    return answer;
}