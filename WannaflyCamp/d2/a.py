def fac(n):
    if n <= 1:
        return 1
    return n * fac(n - 1)

def E(n):
    return n * (n - 1) / 4

def cal(n):
    sum = 0
    for i in range(1, n + 1):
        print(i, fac(i - 1), E(i - 1), fac(n - i), E(n - i))
        sum += fac(i - 1) * E(i - 1) + fac(n - i) * E(n - i)
    return sum

print(cal(5))