x = int(input())

if x == 1:
    print(2)
else:
    i = 3
    sum = 2
    while True:
        sum += int(sum // 2)
        if sum > x:
            print(i)
            break
        i += 1