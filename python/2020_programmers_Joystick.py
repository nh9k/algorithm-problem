minimum = 20


def solution(name):
    answer = 0
    existA = 0
    existA_ = 0
    selected = [0] * len(name)
    selected[0] = 1
    for i in range(0, len(name)):
        if name[i] != 'A':
            answer += min(ord(name[i]) - ord('A'), ord('Z') - ord(name[i]) + 1)
            if i != 0:
                existA_ += 1
        else:
            existA = 1
            selected[i] = 1

    if existA == 0:  # A does not exist
        answer += len(name) - 1
        return answer
    elif (existA == 1 and existA_ == 0):  # only A
        return answer

    def dfs(move, cnt, select):
        if (select == 0) or (cnt > 20):
            global minimum
            if minimum > cnt:
                minimum = cnt

            return;

        for i in range(2):
            if i == 0:
                move -= 1
                if move < 0:
                    move = len(name) - 1

                if selected[move] == 0:
                    selected[move] = 1
                    dfs(move, cnt + 1, select - 1)
                    selected[move] = 0
                else:
                    dfs(move, cnt + 1, select)
            else:
                move += 1
                if move >= len(name):
                    move = 0

                if selected[move] == 0:
                    selected[move] = 1
                    dfs(move, cnt + 1, select - 1)
                    selected[move] = 0
                else:
                    dfs(move, cnt + 1, select)

    global minimum
    minimum = len(name) - 1
    dfs(0, 0, existA_)

    return answer + minimum

if __name__== '__main__':
    print(solution("JAN"))
