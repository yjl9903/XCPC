from math import pow

T = int(input())

def cal(x, k, m):
    return x // int(pow(k, m)) - x // int(pow(k, m + 1))

for i in range(T):
    l, r, k, m = map(int, input().split())
    print(cal(r, k, m) - cal(l - 1, k, m))