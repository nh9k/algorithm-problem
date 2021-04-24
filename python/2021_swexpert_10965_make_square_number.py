# swexpert
# 10965 제곱수 만들기

# 여러개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
prime_list = [2]
for i in range(3, int(10000000 ** 0.5), 2):
    for p in prime_list:
        if not i % p:
            break
    else:
        prime_list.append(i)

print(prime_list)

T = int(input())
answer = []
for test_case in range(1, T + 1):
    A = int(input())
    tmp_ans = 1
    if A**0.5 != int(A**0.5):
        for p in prime_list:
            cnt = 0
            while not A%p:
                A //= p
                cnt += 1
            if cnt % 2:
                tmp_ans *= p
            if A < p or A==1:
                break
        if A>1:
            tmp_ans *= A
    answer.append('#' + str(test_case) + ' ' + str(tmp_ans))
for a in answer:
    print(a)
