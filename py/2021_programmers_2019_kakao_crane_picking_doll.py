def solution(board, moves):
    answer = 0   
    tmp = []
    for m in moves:
        for b in board:
            if b[m-1] !=0:
                tmp.append(b[m-1])
                b[m-1] = 0
                
                if len(tmp) > 1:
                    if tmp[len(tmp)-1] == tmp[len(tmp)-2]:
                        tmp.pop(len(tmp)-1)
                        tmp.pop(len(tmp)-1)
                        answer += 2
                break
    
    return answer