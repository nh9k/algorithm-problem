# info 보다 query의 크기가 훨씬 클 수 있으므로 info를 모든 경우에 대해 저장한다
# binary search의 lowerbound를 정확히 짜지 못하면 틀린다

from itertools import combinations


def condition(q):
    point = int(q[q.rfind(' ') + 1:])
    q = q[:-len(str(point)) - 1].replace(' and ', ' ', 3)
    return q, point


def all_con(con):
    con_list = []
    con_list.append(con)
    con_arr = con.split()[0:4]
    selected = [0,1,2,3]
    for i in range(1,5):
        combi = combinations(selected,i)
        for c in list(combi):
            new_con = ""
            for ind in range(0, 4):
                if ind in c:
                    new_con += '-'
                else:
                    new_con += con_arr[ind]
                new_con += ' '
            con_list.append(new_con[:-1])
    return list(set(con_list))


import bisect
def search(scores, num):
    size = len(scores)
    return size - bisect.bisect_left(scores, num, lo=0, hi=size)


def solution(info, query):
    parsing_i = {}
    for inf in info:
        con, poi = condition(inf)
        check_con = all_con(con)

        for c in check_con:
            if c in parsing_i.keys():
                parsing_i[c].append(poi)
            else:
                parsing_i[c] = [poi]

    for key in parsing_i.keys():
        parsing_i[key].sort()

    answer = []
    for q in query:
        ccon, poi_q = condition(q)
        
        ans = 0
        if ccon not in parsing_i.keys(): answer.append(0)
        else:
            cnt = search(parsing_i[ccon], poi_q)
            answer.append(cnt)
        # if ccon in parsing_i:
        #     # # binary search
        #     # left = 0
        #     # right = len(parsing_i[ccon]) - 1
        #     # while left <= right:
        #     #     mid = int((left + right) / 2)
        #     #     if parsing_i[ccon][mid] > poi_q:
        #     #         right = mid - 1
        #     #     elif parsing_i[ccon][mid] < poi_q:
        #     #         left = mid + 1
        #     #     else:
        #     #         left = mid
        #     #         break
        #     answer.append(lowerBound(parsing_i, 0, len(parsing_i[ccon]), poi_q))
        # else:
        #     answer.append(0)
        
    return answer