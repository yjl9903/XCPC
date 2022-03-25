n = int(input())
k = [int(x) for x in input().split()]
edge = [[] for i in range(n)]

for i in range(n - 1):
    s = input().split()
    u = int(s[0]) - 1
    v = int(s[1]) - 1
    edge[u].append(v)
    edge[v].append(u)

def solve():
    def two(x):
        if x == 0:
            return 0
        flag = 1
        if x < 0:
            x = -x
            flag = -1
        x -= 1
        return flag * (1 << x)
    def get(x):
        if x == 0:
            return '0'
        s = ''
        t = ''
        if x < 0:
            t = '-'
            x = -x
        while x != 0:
            s += str(x % 2)
            x = x // 2
        return t + s[::-1]

    q = int(input())
    ans = 0

    def dfs(u, f, x):
        nonlocal ans
        ans = max(ans, x)
        for v in edge[u]:
            if v == f:
                continue
            dfs(v, u, x + two(k[v]))

    for _ in range(q):
        x = int(input()) - 1
        li = []
        for v in edge[x]:
            ans = 0
            dfs(v, u, two(k[v]))
            if ans:
                li.append(ans)
        li.sort()
        que = two(k[x])
        for i in li[-4:]:
            que += i
        print(get(que))

solve()