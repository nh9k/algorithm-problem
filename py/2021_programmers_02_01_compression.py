# https://programmers.co.kr/learn/courses/30/lessons/17684
# 압축[3차]

def solution(msg):
    answer = []
    chardict = {}

    # add basic index
    for i in range(ord('A'), ord('Z') + 1):
        chardict[chr(i)] = i - 64

    mem = 0
    for cur in range(len(msg)):
        if cur < mem:
            continue;
        mem = cur + 1
        for post in range(cur + 1, len(msg)):
            w = msg[cur:post + 1]
            if w not in chardict.keys():
                mem = post
                # add index
                chardict[w] = len(chardict) + 1
                break;

            if post == (len(msg) - 1):
                mem = post + 1

        # add print
        answer.append(chardict[msg[cur:mem]])
    # print(answer)
    # print(chardict)
    return answer

print(solution('KAKAO'))
