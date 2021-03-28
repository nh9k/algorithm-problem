# 1. 입력이 빈 문자열인 경우, 빈 문자열을 반환합니다. 
# 2. 문자열 w를 두 "균형잡힌 괄호 문자열" u, v로 분리합니다. 단, u는 "균형잡힌 괄호 문자열"로 더 이상 분리할 수 없어야 하며, v는 빈 문자열이 될 수 있습니다. 
# 3. 문자열 u가 "올바른 괄호 문자열" 이라면 문자열 v에 대해 1단계부터 다시 수행합니다. 
#   3-1. 수행한 결과 문자열을 u에 이어 붙인 후 반환합니다. 
# 4. 문자열 u가 "올바른 괄호 문자열"이 아니라면 아래 과정을 수행합니다. 
#   4-1. 빈 문자열에 첫 번째 문자로 '('를 붙입니다. 
#   4-2. 문자열 v에 대해 1단계부터 재귀적으로 수행한 결과 문자열을 이어 붙입니다. 
#   4-3. ')'를 다시 붙입니다. 
#   4-4. u의 첫 번째와 마지막 문자를 제거하고, 나머지 문자열의 괄호 방향을 뒤집어서 뒤에 붙입니다. 
#   4-5. 생성된 문자열을 반환합니다


def s_good(s):
    cnt = 0 
    for i in range(len(s)):
        if s[i] == '(':
            cnt+=1
        else:
            cnt-=1
        if cnt == 0:
            return i+1
    return len(s)  

def s_correct(s):
    stack = []
    for i in range(len(s)):
        if len(stack)==0:
            stack.append(s[i]) 
        elif stack[-1] == '(' and s[i] == ')':
            stack.pop()
        else:
            stack.append(s[i])
    if len(stack)==0:
        return True
    else:
        return False

def recur(s):
    if s=='':
        return ''
    
    idx = s_good(s)
    u = s[:idx]
    v = s[idx:]
    
    if s_correct(u):
        return u + recur(v)
    else:
        new_s = '('
        new_s += recur(v)
        new_s += ')'
        rev_u = ''
        for i in range(1, len(u)-1):
            if u[i] == '(':
                rev_u += ')'
            else:
                rev_u += '('
        new_s += rev_u
        return new_s
    

def solution(p):
    answer = recur(p)
    return answer