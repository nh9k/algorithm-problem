def solution(a, b):
    if a>b: a,b = b,a
    return sum([number for number in range(a,b+1)])


def develop_sol(a,b):
    if a>b: a,b = b,a
    return sum(range(a,b+1))


print(solution(3, 5))
print(develop_sol(3, 5))