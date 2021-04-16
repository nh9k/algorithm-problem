from heapq import heappush, heappop


def solution(n, s, a, b, fares):
    taxi = [[] for i in range(n + 1)]
    for fare in fares:
        sp, ep, co = fare[0], fare[1], fare[2]
        taxi[sp].append([co, ep])
        taxi[ep].append([co, sp])

    INF = int(1e9)

    def dijkstra(graph, start, end):
        route = [INF for i in range(n)]
        route[start - 1] = 0
        pq = [[0, start]]

        while pq:
            cost, cur_x = heappop(pq)

            if route[cur_x - 1] < cost:
                continue

            for w, new_x in graph[cur_x]:
                if cost + w < route[new_x - 1]:
                    route[new_x - 1] = cost + w
                    heappush(pq, [cost + w, new_x])

        return route[end - 1]

    answer = INF
    for i in range(1, n + 1):
        answer = min(answer, dijkstra(taxi, s, i)
                     + dijkstra(taxi, i, a)
                     + dijkstra(taxi, i, b))

    return answer