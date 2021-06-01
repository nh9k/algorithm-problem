def solution(numbers, hand): 
    xy = [[3,1]]
    for x in range(3):
        for y in range(3):
            xy.append([x,y])
    
    answer = ''
    lx, ly, rx, ry = 3, 0, 3, 2

    for num in numbers:
        if num in [2,5,8,0]:
            ldist = abs(xy[num][0] - lx) + abs(xy[num][1] - ly)
            rdist = abs(xy[num][0] - rx) + abs(xy[num][1] - ry)
            if ldist < rdist:  
                lx = xy[num][0]
                ly = xy[num][1]
                answer += 'L'
            elif ldist > rdist:
                rx = xy[num][0]
                ry = xy[num][1]
                answer += 'R'
            else:
                if hand == 'left':
                    lx = xy[num][0]
                    ly = xy[num][1]
                    answer += 'L'
                else:
                    rx = xy[num][0]
                    ry = xy[num][1]
                    answer += 'R'
        elif num in [1,4,7]:
            lx = xy[num][0]
            ly = xy[num][1]
            answer += 'L'
        else:
            rx = xy[num][0]
            ry = xy[num][1]
            answer += 'R'
    
    return answer