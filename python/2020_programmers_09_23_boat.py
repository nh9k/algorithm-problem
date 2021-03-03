def solution(people, limit):
    answer = 0
    p_dict = dict()
    for i in range(len(people)):
        if people[i] in p_dict:
            p_dict[people[i]] = p_dict[people[i]] + 1
        else:
            p_dict[people[i]] = 1

    p_dict = dict(sorted(p_dict.items(), reverse=True))
    k_list = list(p_dict.keys())
    print(p_dict)
    len_dict = len(k_list)
    for k, v in p_dict.items():
        if k == limit:
            answer += v
            v = 0
        else:
            s_limit = limit - k
            if s_limit in p_dict:
                if s_limit == k:
                    answer += v/2
                    v = 0
                else:
                    sub_min = min(p_dict[s_limit], v)
                    p_dict[s_limit] -= sub_min
                    v -= sub_min
                    answer += sub_min
            elif k_list[len(k_list) - 1] > s_limit:
                answer += v
            else:
                for i in reversed(range(len_dict)):
                    if k_list[i] > s_limit:
                        break
                    if int(p_dict[k_list[i]]) >= v:
                        answer += v
                        p_dict[k_list[i]] -= v
                        break
                    else:
                        answer += p_dict[k_list[i]]
                        p_dict[k] -= p_dict[k_list[i]]
                        len_dict -= 1
                        p_dict[k_list[i]] = 0

    return answer

if __name__=='__main__':
    print(solution([70, 50, 80, 50], 100))