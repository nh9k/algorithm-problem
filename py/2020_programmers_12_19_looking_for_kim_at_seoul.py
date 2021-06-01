def solution(seoul):
    times = 0
    for s in seoul:
        if s == 'Kim':
            break;
        times += 1

    answer = '김서방은 ' + str(times) + '에 있다'
    return answer

def findKim2(seoul):
    return "김서방은 {}에 있다".format(seoul.index('Kim'))

def findKim3(seoul):
    kimIdx = 0
    # 함수를 완성하세요
    for i in range(len(seoul)):
        if seoul[i]=="Kim":
            return "김서방은 {}에 있다".format(i)

# 실행을 위한 테스트코드입니다.
print(solution(["Queen", "Tod", "Kim"]))