f = [1]
for i in range(0, 50):
  f.append(f[-1] * (i + 1))

T = int(input())

for _ in range(T):
  n, k = map(int, input().split())

  dp = [ -1 for i in range(n + 2) ]
  dp[n + 1] = 1

  def dfs(x):
    if dp[x] != -1:
      return dp[x]
    tot = 0
    for i in range(x, n + 1):
      if i - x <= 2:
        tot += dfs(i + 1)
      else:
        tot += f[i - x - 1] * dfs(i + 1)
    dp[x] = tot
    return tot

  dfs(1)

  print(dp)

  if k > dp[1]:
    print(-1)
    continue

  ans = []

  i = 1
  while i <= n:
    if i == n:
      ans.append(i)
      break
    ch = i - 1
    for c in range(i, n + 1):
      tot = 0
      if c - i <= 2:
        tot = dp[c + 1]
      else:
        tot = f[c - i - 1] * dp[c + 1]

      if k >= tot:
        k -= tot
        ch += 1
      else:
        break
    kk = k // dp[ch + 1] + 1
    k = dp[ch + 1]
    def gen(j):
      pass
    ans.append(ch)
    i = ch + 1

  print(' '.join(map(str, ans)))
