import re

def solution(files):
    tmp = []
    for i, f in enumerate(files):
        regular_split = re.split('(\d+)', f)
        tmp.append([regular_split[0], regular_split[1], i])
             
    tmp.sort(key=lambda x: (x[0].upper(), int(x[1])))
    answer = []
    for t in tmp:
        answer.append(files[t[2]])

    return answer