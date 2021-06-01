import math
# 잘못된 풀이, 알고리즘적 접근도 잘못됨 gcd 이용.
def solution(w, h):
    answer = w * h

    mem = 0
    for i in range(1, w+1):
        hx = (h * i) / w
        answer = answer - (math.ceil(hx) - mem)
        # print(mem, math.ceil(hx),(math.ceil(hx) - mem))
        mem = math.floor(hx)

    return answer

def good_solution(w, h):
    return w*h-(w+h-math.gcd(w,h))

solution(8,12)