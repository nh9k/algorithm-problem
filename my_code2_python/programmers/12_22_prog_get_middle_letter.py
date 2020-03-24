def solution(s):
    if len(s)%2==1:
        return s[len(s)//2]
    else:
        return s[len(s)//2-1]+s[len(s)//2]

def string_middle(str):
    return str[(len(str)-1)//2:len(str)//2+1]

def print_str_middle_index(str):
    # 홀수, 짝수에서 중간 인덱스 #홀수에서 중간 바로다음, 짝수에서 중간 다음다음
    print((len(str)-1)//2, len(str)//2+1)
    return

# 아래는 테스트로 출력해 보기 위한 코드입니다.
print(string_middle("power"))
print_str_middle_index('power')
print(string_middle("nanhee"))
print_str_middle_index('nanhee')

