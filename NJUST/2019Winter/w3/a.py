from itertools import accumulate

ans, blist, b = [], [1], 1

for _ in range(4001):

    blist = list(accumulate([b]+blist))

    b = blist[-1]

    ans.append(blist[-2])

mod = 1000000000 + 7

print(ans[int(input())] % mod)