from itertools import permutations
# permutations!

def solution(n, weak, dist):
    w = []
    for i in range(len(weak)):
        if i + 1 != len(weak):
            w.append(weak[i + 1] - weak[i])
        else:
            w.append(n - weak[i] + weak[0])
    # print(w)
    answer = []
    for i in range(len(w)):
        last = i + len(w) - 1

        for friends in permutations(dist):
            len_ans = len(answer)
            cur_f = friends[0]
            idx = i
            for fi, f in enumerate(friends):
                if len_ans != len(answer):
                    len_ans = len(answer)
                    break
                elif cur_f == friends[0] and fi == 1:
                    break
                cur_f = f
                while 1:
                    if w[idx % len(w)] > cur_f:
                        if cur_f != f:
                            idx += 1
                        else:
                            # 한 사람이 한 점만 커버하는 경우
                            cur_f = 0
                            idx += 1
                        break
                    else:
                        cur_f -= w[idx % len(w)]
                        idx += 1
                if idx > last:
                    answer.append(fi + 1)
                    break

    return min(answer) if len(answer) != 0 else -1

print(solution(200,[0,100],[1,1]))