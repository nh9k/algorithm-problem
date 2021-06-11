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
        for c in opc:
            sti, opi, eni = 0, 0, 0
            while c in expression_copy:
                for i in range(sti, len(expression_copy)):
                    if expression_copy[i] == c:
                        opi = i

                        for j in range(opi + 1, len(expression_copy)):
                            if expression_copy[j] in opc:
                                eni = j

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

                    elif expression_copy[i] in opc:
                        sti = i + 1
            print(expression_copy)
            # if answer < int(expression_copy):
        #     answer = int(expression_copy)

    return answer

solution("100-200*300-500+20")