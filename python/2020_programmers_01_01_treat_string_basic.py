def alpha_string46(s):
    return s.isdigit() and len(s) in (4, 6)

# 아래는 테스트로 출력해 보기 위한 코드입니다.
print( alpha_string46("a234") )
print( alpha_string46("1234") )


def solution(s):
    answer = True
    if len(s) != 4 and len(s) != 6:
        return False
    for i in range(0, len(s)):
        if s[i] < '0' or s[i] > '9':
            answer = False
            break

    return answer