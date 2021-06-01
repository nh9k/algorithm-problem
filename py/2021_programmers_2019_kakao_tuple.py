def solution(s):
    s = s.split('{')
    slist = []
    for spl in s:
        spl = spl.split('}')[0].split(',')
        if spl[0] != '':
            slist.append(spl)
    
    slist.sort(key=len)
    answer = []
    for s in slist:
        for sele in s:
            if int(sele) not in answer:
                answer.append(int(sele))
                break

    return answer