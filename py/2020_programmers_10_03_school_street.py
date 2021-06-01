def solution(m, n, puddles):
    def in_puddles(x, y):
        for sz in range(len(puddles)):
            if (puddles[sz][0] - 1 == x) and (puddles[sz][0] - 1 == y):
                return 1
        return 0

    def out_range(x, y):
        if (x >= m) or (y >= n) or (x < 0) or (y < 0):
            return 1
        return 0

    answer = 0
    memcnt = 200

    def dfs(x, y, cnt):
        if (x == m - 1) and (y == n - 1):
            if memcnt > cnt:
                memcnt = cnt
                answer = 0
            elif memcnt == cnt:
                answer += 1
            return
        if (in_puddles(x, y) == 1) or (out_range(x, y) == 1):
            return

        for i in range(2):
            return dfs(x + 1, y, cnt + 1) if i == 0 else dfs(x, y + 1, cnt + 1)

    dfs(0, 0, 0, memcnt, answer)

    return answer

if __name__ == '__main__':
    print(solution(4,3,[[2,2]]))