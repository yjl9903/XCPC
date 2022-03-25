mod = 10 ** 18 + 31

def qpow(x, n):
  r = 1
  while n > 0:
    if n % 2 == 1:
      r = r * x % mod
    n = n // 2
    x = x * x % mod
  return r


k = 1000000
a = [0 for i in range(k + 1)]
a[k] = 300
for i in range(k):
  a[k - 1 - i] = qpow(42, a[k - 1 - i + 1])

n = int(input())
print(a[n])