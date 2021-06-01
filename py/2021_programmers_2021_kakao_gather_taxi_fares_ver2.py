#https://programmers.co.kr/learn/courses/30/lessons/72413
#프로그래머스 합승 택시 요금
#다익스트라 연습하기 좋은 문제

import heapq 

def solution(n, s, a, b, fares):
    path = [[] for _ in range(n)]
    
    for f in fares:
        path[f[0]-1].append([f[2], f[1]-1])
        path[f[1]-1].append([f[2], f[0]-1])
        
    def dijkstra(start, end):
        q = []
        heapq.heappush(q, [0, start])
        destination = [1e9 for _ in range(n)]
        destination[start] = 0
        
        while len(q) != 0:
            cost, present = heapq.heappop(q)
            
            #test 7,8 time over
            if destination[present] < cost:
                continue
            
            for w, end_p in path[present]:
                if cost + w < destination[end_p]:
                    destination[end_p] = cost + w
                    heapq.heappush(q, [cost+w, end_p])
        
        return destination[end]

    
    answer = 1e9
    for i in range(n):
        answer = min(answer, dijkstra(s-1, i) + dijkstra(i, a-1) + dijkstra(i, b-1))

    return answer