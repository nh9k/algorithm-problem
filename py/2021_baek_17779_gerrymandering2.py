# 제출 번호	아이디	문제	결과	메모리	시간	언어	코드 길이	제출한 시간
# 28690170	nh9k	17779	맞았습니다!!	28776	1824	Python 3 / 수정	2118	1분 전
# 1시간 25분 풀이
# cpp 풀이: https://github.com/nh9k/algorithm-problem/blob/master/c%2B%2B/2020_baek-gm2.cpp

N = int(input())

maplist = []
for i in range(N):
    maplist.append(list(map(int, input().split())))

sum_maplist = 0
for i in range(N):
    sum_maplist += sum(maplist[i])

d = 1e9
for x in range(0, N-2):
    for y in range(1, N-1):
        for d1 in range(1, y+1):
            for d2 in range(1, N - y):
                if x + d1 + d2 > N-1:
                    continue

                visit = [[0 for _ in range(N)] for _ in range(N)]
                for di in range(0, d1+1):
                    visit[x + di][y - di] = 1
                    visit[x + d2 + di][y + d2 - di] = 1

                for di in range(0, d2+1):
                    visit[x + di][y + di] = 1
                    visit[x + d1 + di][y - d1 + di] = 1

                sum_all = []
                sum_tmp = 0
                for xi in range(0, x+d1):
                    for yi in range(0, y+1):
                        if visit[xi][yi] == 1: break
                        sum_tmp += maplist[xi][yi]
                        visit[xi][yi] = 2
                sum_all.append(sum_tmp)

                sum_tmp = 0
                for yi in range(y + 1, N):
                    for xi in range(0, x+d2+1):
                        if visit[xi][yi] == 1: break
                        sum_tmp += maplist[xi][yi]
                        visit[xi][yi] = 3
                sum_all.append(sum_tmp)

                sum_tmp = 0
                for yi in range(0, y-d1+d2):
                    for xi in range(N-1, x+d1-1, -1):
                        if visit[xi][yi] == 1: break
                        sum_tmp += maplist[xi][yi]
                        visit[xi][yi] = 4
                sum_all.append(sum_tmp)

                sum_tmp = 0
                for yi in range(y-d1+d2, N):
                    for xi in range(N-1, x+d2, -1):
                        if visit[xi][yi] == 1: break
                        sum_tmp += maplist[xi][yi]
                        visit[xi][yi] = 5
                sum_all.append(sum_tmp)

                sum_all.append(sum_maplist - sum(sum_all))

                d = min(d, max(sum_all) - min(sum_all))

print(d)