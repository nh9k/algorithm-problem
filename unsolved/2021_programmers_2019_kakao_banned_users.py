answer = 0
remain_temp = []


def dfs(curi, temp, leng, result_id):
    global answer
    global remain_temp
    if len(temp) == leng:
        if not (temp in remain_temp):
            remain_temp.append(temp)
            answer += 1
        print(temp, remain_temp)
        return
    for r in result_id[curi]:
        if r in temp:
            continue
        temp.append(r)
        dfs(curi + 1, temp, leng, result_id)
        temp.pop(len(temp) - 1)


def solution(user_id, banned_id):
    # because the size of user_id is small, don't cared optimization

    result_id = []
    for b in banned_id:
        temp = []
        for u in user_id:
            is_same = True
            if len(b) != len(u):
                is_same = False
            else:
                for bi in range(len(b)):
                    if b[bi] == '*':
                        continue
                    elif b[bi] != u[bi]:
                        is_same = False
                        break

            if is_same:
                temp.append(u)
        result_id.append(temp)

    global answer
    dfs(0, [], len(banned_id), result_id)

    return answer


solution(["frodo", "fradi", "crodo", "abc123", "frodoc"],["fr*d*", "abc1**"])