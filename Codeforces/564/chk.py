import os
import subprocess

for i in range(101):
    print("%d ing" % i)
    for j in range(101):
        for k in range(101):
            with open('.\\input\\in.txt', 'w') as f:
                f.write("%d %d %d" % (i, j, k))
            r1 = os.popen('.\\debug\\a.exe <.\\input\\in.txt').read().strip()
            r2 = os.popen('.\\debug\\a2.exe <.\\input\\in.txt').read().strip()
            if r1 != r2:
                print("%d %d %d" % (i, j, k))