from math import gcd

n, a, b, p, q = map(int, input().split())

# print(n, a, b, p, q)
x = n // a * p
y = n // b * q
z = (n // (a * b // gcd(a, b))) * min(p, q)

print(x + y - z)