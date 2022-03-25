table = [
  1, 2, 1, 1,
  4, 2, 2, 2,
  4, 2, 4, 1,
  4, 4, 4, 4,
  2, 2, 3, 1,
  1, 1, 1, 2,
  4, 1, 4, 3,
  1, 3, 3, 4,
  3, 2, 3, 3,
  1, 4, 4, 2,
  1, 1, 2, 2,
  4, 4, 2, 4,
  4, 4, 3, 2,
  3, 3, 1, 4,
  4, 3, 4, 1,
  4, 2, 4
]

n = int(input())
a = input().split(' ')
b = input().split(' ')

# expr = [ a[0] ]

last = int(a[0])

for i in range(n - 1):
  cur = int(a[i + 1])
  type = table[int(b[i]) - 1]
  if type == 1:
    # expr.append('+')
    last = last + cur
  elif type == 2:
    # expr.append('-')
    last = last - cur
  elif type == 3:
    # expr.append('*')
    last = last * cur
  else:
    # expr.append('//')
    last = last // cur
  # expr.append(a[i + 1])

print(last)
