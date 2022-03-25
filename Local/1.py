
for j in range(200, 401):
    t = 1
    for i in range(j - 1):
        t = t * 2
    print str(j) + ': ' + str((t - 1) % j)
