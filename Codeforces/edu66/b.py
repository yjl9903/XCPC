n = int(input())

l = []
tot = 1
inf = 4294967295
x = 0
f = 0

for i in range(n):
    ip = input().split()
    if ip[0] == 'for':
        ip[1] = int(ip[1])
        l.append(ip[1])
        tot *= ip[1]
    elif ip[0] == 'add':
        if tot > inf:
            print('OVERFLOW!!!')
            exit(0)
        x += tot
        if x > inf:
            print('OVERFLOW!!!')
            exit(0)
    else:
        tot = tot // l.pop()

print(x)