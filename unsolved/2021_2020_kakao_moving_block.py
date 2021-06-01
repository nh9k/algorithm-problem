def solution(board):
    visit = []
    for i in range(len(board)):
        visit.append([0 for _ in range(len(board[i]))])

    robot_pos = []
    robot_pos.append([0, 0, 0, 1])
    # just move(4) + rotate(4)
    dx1 = [-1, 0, 1, 0, 0, -1, 0, 1]
    dy1 = [0, 1, 0, -1, 0, 1, 0, 1]
    dx2 = [-1, 0, 1, 0, -1, 0, 1, 0]
    dy2 = [0, 1, 0, -1, -1, 0, -1, 0]
    # diagonal check
    chkx1 = [-1, -1, 1, 1]
    chky1 = [1, 0, 1, 0]
    past_pos = robot_pos[0]
    n = len(board)
    while len(robot_pos):
        pos = robot_pos.pop(0)
        visit[pos[0]][pos[1]] = visit[past_pos[0]][past_pos[1]] + 1
        visit[pos[2]][pos[3]] = visit[past_pos[0]][past_pos[1]] + 1

        print(visit)
        for i in range(8):
            x1 = pos[0] + dx1[i]
            y1 = pos[1] + dy1[i]
            x2 = pos[2] + dx2[i]
            y2 = pos[3] + dy2[i]

            if x1 < 0 or x1 >= n or x2 < 0 or x2 >= n or y1 < 0 or y1 >= n or y2 < 0 or y2 >= n:
                continue

            if board[x1][y1] == 1 or board[x2][y2] == 1:
                continue

            if i >= 4:
                print(pos)
                print(x1,y1,x2,y2)
                print(i)
                if board[pos[0] + chkx1[i - 4]][pos[1] + chky1[i - 4]] == 1:
                    continue

            if visit[x1][y1] > 0 and visit[x2][y2] > 0:
                continue

            robot_pos.append([x1, y1, x2, y2])

        past_pos = pos

    return visit[n - 1][n - 1]

print(solution([[0, 0, 0, 1, 1],[0, 0, 0, 1, 0],[0, 1, 0, 1, 1],[1, 1, 0, 0, 1],[0, 0, 0, 0, 0]]))