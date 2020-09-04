def solution(priorities, location):
    answer = 0
    
    while 1:
        find_max = 0
        for i in range(1,len(priorities)):
            find_max = max(priorities[1:])
        
        if priorities[0] < find_max:
            priorities.append(priorities[0])
            if location == 0:
                location = len(priorities) - 1
        else:
            answer += 1
            if location == 0:
                return answer
        location -= 1
        priorities.pop(0)
            
    
    return answer