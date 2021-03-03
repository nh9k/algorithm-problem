def solution(s):
    answer = len(s)
    
    for i in range(1, len(s)//2+1):
        cnt = 0
        new_compression = ""
        mem = s[0:i]
        for j in range(len(s)//i + 1):
            if ((j+1)*i) > len(s):
                new_compression += s[j*i:len(s)]
            elif s[j*i:(j+1)*i] == mem:
                cnt += 1
                if len(s)//i == j+1:
                    if cnt == 1 or cnt == 0:
                        new_compression += mem
                    else:
                        new_compression += (str(cnt) + mem)
            else:
                if cnt == 1 or cnt == 0:
                    new_compression += mem
                else:
                    new_compression += (str(cnt) + mem)
                mem = s[j*i:(j+1)*i]
                cnt = 1
                if len(s)//i == j+1:
                    new_compression += mem
                    
        if answer > len(new_compression):
            answer = len(new_compression)
        # print(new_compression)

    return answer