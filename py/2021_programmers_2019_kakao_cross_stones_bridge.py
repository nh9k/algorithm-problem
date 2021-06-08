# 이분탐색으로 ((건널 수 있는 최대 사람 수) + (건널 수 있는 최소 사람 수)) / 2부터 돌다리에 빼기 해본다.
# k에 대해 건널 수 없는 돌다리가 있다면 
# 재 탐색 한다.

def solution(stones, k):
    l = min(stones)
    r = max(stones)

    if k==1: # 정확성 2번
        return l
    
    cur = (l + r)//2
    
    while l!=cur:
        temp_chk = 0
        
        break_point = False
        for s in stones:
            if s - cur <= 0: # 건너지 못함!
                temp_chk += 1
                if temp_chk >= k: # 마지막까지 건널 수 없는 경우도 고려
                    break_point = True
                    break                  
            else:
                temp_chk = 0
        
        if break_point == False:
            l = cur

        else:
            r = cur
        
        cur = (l + r)//2

    return r