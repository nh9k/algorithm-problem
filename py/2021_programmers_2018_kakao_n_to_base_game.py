# https://codingdojang.com/scode/458?orderby=time&langby=python
# https://kldp.org/node/63551


def convert(n, base):
    T = "0123456789ABCDEF"
    q, r = divmod(n, base) # n을 base로 나눈 몫과 나머지를 튜플형태로 반환
    if q == 0:
        return T[r]
    else:
        return convert(q, base) + T[r]

    
def solution(n, t, m, p):
    numbering = ''
    answer = ''
    num = 0
    for i in range(p-1,t*m,m):
        while len(numbering) <= i:
            numbering += convert(num, n)
            num += 1
        answer += numbering[i]
        
    return answer