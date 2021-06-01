num = int(input())
sum = 0
for cnt in [0,1,10,100]:
    for mul in [1,10,100,1000]:
        sum += num * mul
        print(num*mul)
        if mul//10==cnt:
            break

print(sum)