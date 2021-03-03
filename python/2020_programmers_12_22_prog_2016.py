def solution(a, b):
    month = [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    day = ['THU', 'FRI', 'SAT', 'SUN', 'MON', 'TUE', 'WED']
    sum_day = 0

    for c in range(0, a - 1):
        sum_day += month[c]
    sum_day += b

    return day[sum_day % 7]

def develop_sol(a,b):
    month = [31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
    day = ['THU', 'FRI', 'SAT', 'SUN', 'MON', 'TUE', 'WED']
    return day[(sum(month[0:a-1])+b)%7]

print(solution(5,24))
print(develop_sol(5,24))