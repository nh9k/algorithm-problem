def solution(people, limit):
    answer = 0
    people.sort(reverse=True)
    chk = len(people) * [0]
    b_ = len(people) - 1 #back
    
    for f_ in range(len(people)):
        if chk[f_] == 1:
            break
        if people[f_] + people[b_] <= limit:
            answer += 1
            chk[b_] = 1
            b_ -= 1
        else:
            answer += 1
            
    return answer