l = int(input())
n = input()

mid = l // 2
choose = []

for i in range(mid, l):
    if n[i] == '0': continue
    # print(i)
    choose.append(int(n[:i]) + int(n[i:]))
    if len(choose) >= 3: break

for i in range(1, mid)[::-1]:
    if n[i] == '0': continue
    choose.append(int(n[:i]) + int(n[i:]))
    if len(choose) >= 6: break

choose.sort()
print(choose[0])