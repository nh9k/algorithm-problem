def solution(m, n, board):
    newboard = []
    for mi in range(m):
        tempboard = []
        for ni in range(n):
            tempboard.append(board[mi][ni])
        newboard.append(tempboard)

    while 1:
        break_true = False
        erase_list = []
        for mi in range(m - 1):
            for ni in range(n - 1):
                if (newboard[mi][ni] == newboard[mi + 1][ni] == newboard[mi][ni + 1] == newboard[mi + 1][ni + 1]) \
                        & (newboard[mi][ni] != '-'):
                    erase_list.append([mi, ni])
                    erase_list.append([mi + 1, ni])
                    erase_list.append([mi, ni + 1])
                    erase_list.append([mi + 1, ni + 1])
                    break_true = True

        for i in range(len(erase_list)):
            newboard[erase_list[i][0]][erase_list[i][1]] = '-'

        if break_true == False:
            break

        for ni in range(n):
            mem = 0
            for mi in range(m - 1, -1, -1):
                if newboard[mi][ni] == '-' and mem == 0:
                    mem = mi
                elif newboard[mi][ni] != '-' and mem != 0:
                    newboard[mem][ni] = newboard[mi][ni]
                    newboard[mi][ni] = '-'
                    mem = mem - 1

    answer = 0
    for mi in range(m):
        for ni in range(n):
            if newboard[mi][ni] == '-':
                answer += 1

    return answer

# 4	5	[CCBDE, AAADE, AAABF, CCBBF]	14
# 6	6	[TTTANT, RRFACC, RRRFCC, TRRRAA, TTMMMF, TMMTTJ]	15

solution(8,2, ["FF", "AA", "CC", "AA", "AA", "CC", "DD", "FF"])