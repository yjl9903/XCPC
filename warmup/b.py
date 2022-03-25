x = int(input())

for k in range(1, 65)[::-1]:
    l = 2
    r = int(pow(x, 1 / k))
    p = -1
    # print(k, r)
    while l <= r:
        m = int((l + r) // 2)
        tot = int((m ** (k + 1) - 1) // (m - 1))
        if x == tot:
            p = m
            break
        if x > tot:
            l = m + 1
        else:
            r = m - 1
    
    if p != -1:
        print(p)
        break
