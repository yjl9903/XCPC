x = int(input())

ans = 1
cnt = 1

while True:
    if ans % x == 0:
        print(ans // x, cnt)
        break
    ans = ans * 10 + 1
    cnt += 1