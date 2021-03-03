def solution(triangle):
    answer = 0
    for i in range(1, len(triangle)):
        for j in range(0, len(triangle[i])):
            if j==0:
                triangle[i][j] += triangle[i-1][j]
            elif j==len(triangle[i])-1:
                triangle[i][j] += triangle[i-1][j-1]
            else:
                triangle[i][j] +=  max(triangle[i-1][j-1], triangle[i-1][j])
    
    for j  in range(0, len(triangle[len(triangle)-1])):
        answer = max(answer, triangle[len(triangle)-1][j])
                
    return answer