from math import *
from fractions import *

def sqr(x):
  return x * x

class Point:
  def __init__(self, x = Fraction(0), y = Fraction(0)):
    self.x = x
    self.y = y

  def read(self):
    a, b = map(int, input().split(' '))
    self.x = Fraction(a)
    self.y = Fraction(b)

  def abs(self):
    return sqrt(self.x * self.x + self.y * self.y)

  def distance(self, b):
    x = self.x - b.x
    y = self.y - b.y
    return sqrt(x * x + y * y)

  def unit(self):
    l = self.abs()
    return Point(self.x / l, self.y / l)

def cal(a, b, c, L, R):
  eval = lambda x : a * x * x + b * x + c

  ans = min(eval(L), eval(R))

  if a != 0:
    mid = -b / (a + a)
    if L <= mid and mid <= R:
      ans = min(ans, eval(mid))

  if ans <= 0:
    ans = 0
  
  return ans

x1, x2, x3, x4 = map(int, input().split(' '))
y1, y2, y3, y4 = map(int, input().split(' '))

a = Point(Fraction(x1), Fraction(x2))
b = Point(Fraction(x3), Fraction(x4))
c = Point(Fraction(y1), Fraction(y2))
d = Point(Fraction(y3), Fraction(y4))

ab = a.distance(b)
cd = b.distance(d)

if Point(b.x - a.x, b.y - a.y).abs() == 0 and Point(d.x - c.x, d.y - c.y).abs() == 0:
  print(a.distance(c))
if Point(b.x - a.x, b.y - a.y).abs() == 0:
  k2 = Point(d.x - c.x, d.y - c.y).unit()
  A = sqr(k2.x) + sqr(k2.y)
  B = 2.0 * (c.x - b.x) * k2.x + 2.0 * (c.y - b.y) * k2.y
  C = sqr(c.x - b.x) + sqr(c.y - b.y)
  print(sqrt(cal(A, B, C, ab, cd)))
elif Point(d.x - c.x, d.y - c.y).abs() == 0:
  k1 = Point(b.x - a.x, b.y - a.y).unit()
  A = sqr(k1.x) + sqr(k1.y)
  B = 2.0 * (a.x - d.x) * k1.x + 2.0 * (a.y - d.y) * k1.y
  C = sqr(a.x - d.x) + sqr(a.y - d.y)
  print(sqrt(cal(A, B, C, cd, ab)))
else:
  k1 = Point(b.x - a.x, b.y - a.y).unit()
  k2 = Point(d.x - c.x, d.y - c.y).unit()

  A = sqr(k1.x - k2.x) + sqr(k1.y - k2.y)
  B = 2.0 * (k1.x - k2.x) * (a.x - c.x) + 2.0 * (k1.y - k2.y) * (a.y - c.y)
  C = sqr(a.x - c.x) + sqr(a.y - c.y)
  ans = cal(A, B, C, 0, min(ab, cd))

  if ab < cd:
    A = sqr(k2.x) + sqr(k2.y)
    B = 2.0 * (c.x - b.x) * k2.x + 2.0 * (c.y - b.y) * k2.y
    C = sqr(c.x - b.x) + sqr(c.y - b.y)
    ans = min(ans, cal(A, B, C, ab, cd))
  elif ab > cd:
    A = sqr(k1.x) + sqr(k1.y)
    B = 2.0 * (a.x - d.x) * k1.x + 2.0 * (a.y - d.y) * k1.y
    C = sqr(a.x - d.x) + sqr(a.y - d.y)
    ans = min(ans, cal(A, B, C, cd, ab))

  print(sqrt(ans))