n = int(input())
a = [int(x) for x in input().split(' ')]

l = 0
s = a[0]
c = 1
ans = [0 for i in range(n)]

for i in range(1, n + 1):
  if i == n or s < c * a[i]:
    for j in range(l, i):
      ans[j] = s / c
    if i == n: break
    l = i
    s = a[i]
    c = 1
  else:
    s += a[i]
    c += 1

print('\n'.join([format(x, '.9f') for x in ans]))
