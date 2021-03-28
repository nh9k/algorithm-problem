# 2021 kakao blind recruitment menu renewal
com = {}

def sorted_order(order):
    s = []
    for i in range(len(order)):
        s.append(order[i])
        
    s.sort()
    order = ''
    for i in s:
        order += i
    
    return order


def combination(order, cur_com, cur, fin):
    global com
    if len(cur_com) == fin:
        if cur_com in com:
            com[cur_com] += 1
        else:
            com[cur_com] = 1
        return
    
    for i in range(cur, len(order)):
        combination(order, cur_com + order[i], i + 1, fin)

        
def solution(orders, course):
    answer = []
    
    for sz in course:
        global com
        com.clear()
        
        pass_sign = True
        for ord in orders:
            if len(ord) >= sz:
                combination(sorted_order(ord), '', 0, sz)
                pass_sign = False
            else:
                continue
                
        if not pass_sign:
            max_value = max(com.values())
            if max_value >= 2:
                for key, value in com.items():
                    if max_value == value:
                        answer.append(key)
                
    answer.sort()
    return answer