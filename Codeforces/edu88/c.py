from fractions import Fraction

T = int(input())

for _ in range(T):
  h, c, t = map(int, input().split(' '))
  if t + t == h + c:
    print(2)
  else:
    mn = [2, abs(Fraction(h + c, 2) - t)]
    def push(k):
      if k < 0: return
      tot = Fraction((k + 1) * h + k * c, k + k + 1)
      if abs(tot - t) < mn[1]:
        mn[0] = k + k + 1
        mn[1] = abs(tot - t)
    mid = abs(h - t) // abs(t + t - h - c);
    for i in range(mid - 1, mid + 1):
      push(i)
    print(mn[0])

