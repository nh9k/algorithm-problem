from itertools import permutations

def solution(expression):
    oplist = []
    if expression.find('+') != -1:
        oplist.append('+')
    if expression.find('-') != -1:
        oplist.append('-')
    if expression.find('*') != -1:
        oplist.append('*')

    opclist = list(permutations(oplist, len(oplist)))
    answer = 0
    for opc in opclist:
        expression_copy = expression
        poplist = list(opc)
        for c in opc:
            sti, opi, eni = 0, 0, 0
            while c in expression_copy[sti+1:]: # 음의 정수인 경우 while을 반복해서 보므로 , sti+1이 중요
                for i in range(sti, len(expression_copy)):
                    if expression_copy[i] == c:
                        opi = i
                        if sti == opi: #음의 정수인경우 continue
                            continue
                        for j in range(opi + 1, len(expression_copy)):
                            if expression_copy[j] in poplist:
                                eni = j
                                break
                            elif j + 1 == len(expression_copy):
                                eni = len(expression_copy)

                        num1 = int(expression_copy[sti:opi])
                        num2 = int(expression_copy[opi + 1:eni])

                        if c == '+':
                            num3 = num1 + num2
                        elif c == '-':
                            num3 = num1 - num2
                        elif c == '*':
                            num3 = num1 * num2

                        expression_copy = expression_copy[0:sti] + str(num3) + expression_copy[eni:]
                        opi = 0
                        break

                    elif expression_copy[i] in poplist:
                        sti = i + 1
            # print(expression_copy)

            poplist.pop(0)

        if answer < abs(int(expression_copy)):
            answer = abs(int(expression_copy))

    return answer

print(solution("100-200*300-500+20"))
print(solution("2-990-5+2"))
print(solution("177-661*999*99-133+221+334+555-166-144-551-166*166-166*166-133*88*55-11*4+55*888*454*12+11-66+444*99"))