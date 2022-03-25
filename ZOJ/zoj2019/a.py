T = int(input())

def cal(n, p):
    if n < p: 
        return 0
    return cal(n // p, p) + n // p

for i in range(T):
    n = int(input())
    n /= 2
    ans = cal(n, 2) + n
    print(int(ans))