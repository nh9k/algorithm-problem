# >>> a = {'a','b'}
# >>> b = {'b','a'}
# >>> a == b
# True

answer = 0
remain_temp = list()


def dfs(curi, temp, leng, result_id):
    if len(temp) == leng:
        global answer, remain_temp

        for rt in remain_temp:
            if temp == rt:
                return

        remain_temp.append(temp.copy())  # copy를 안해주면 temp가 바뀔때마다 remain_temp의 원소도 바뀜
        return

    for r in result_id[curi]:
        if r in temp:
            continue
        temp.add(r)
        dfs(curi + 1, temp, leng, result_id)
        temp.remove(r)


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
    dfs(0, set(), len(banned_id), result_id)

    return len(remain_temp)