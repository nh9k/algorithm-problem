# swexpert 11445. 무한 사전

T = int(input())
# 여러개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
for test_case in range(1, T + 1):
    p = input().rstrip()
    q = input().rstrip()
    
    if p + 'a' != q:
        print('#' + str(test_case) + ' ' + 'Y')
    else:
        print('#' + str(test_case) + ' ' + 'N')
