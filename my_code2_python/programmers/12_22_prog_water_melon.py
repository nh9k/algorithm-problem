def solution(n):
    answer = ''
    for cnt in range(0,n):
        if cnt%2==0:
            answer+='수'
        else: answer+='박'
    return answer

def develop_sol(n):
    str = '수박' * (n//2+1)
    return str[:n]

print(develop_sol(3))