from math import ceil

def solution(progresses, speeds):
    answer = []
    
    for i in range(0, len(progresses)):
        speeds[i] = ceil((100 - progresses[i]) / speeds[i])
    
    mem_val = 0; cnt = 0; j = 0;
    while 1:
        if mem_val == 0:
            mem_val = speeds[j]
            cnt = 1
        elif mem_val < speeds[j]:
            answer.append(cnt)
            mem_val = 0
            j -= 1
        else:
            cnt += 1
        j += 1
        if len(speeds) == j:
            break
    answer.append(cnt)
    return answer

def solution_print():
    print(solution([93, 30, 55], [1, 30, 5]))

solution_print()