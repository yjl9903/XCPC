from math import sqrt

a = [19, 38] + list(range(50, 62)) + [63] + list(range(65, 81)) + list(range(82, 100))

for x in a:
    for y in a:
        sq = int(sqrt(x + y))
        if sq * sq == x + y:
            print(x, y)