def solution(strings, n):
    answer = []
    answer.append(strings[0])
    for i in range(1,len(strings)):
        for j in range(0, len(answer)):
            if answer[j][n] > strings[i][n]:
                answer.insert(j,strings[i])
                break
            if answer[j][n] == strings[i][n]:
                if answer[j] > strings[i]:
                    answer.insert(j,strings[i])
                    break
            if j==len(answer)-1:
                answer.append(strings[i])
    return answer

def strange_sort(strings, n):
    '''strings의 문자열들을 n번째 글자를 기준으로 정렬해서 return하세요'''
    return sorted(sorted(strings), key=lambda x: x[n])

strings = ['sun','bed','bedf','bedd','bed','car']
print(solution(["sun", "bed", "car"],1)) # car, bed, sun 순서대로
print(solution(strings, 1))
print(strange_sort(strings, 1))
