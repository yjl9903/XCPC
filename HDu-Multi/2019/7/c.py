with open('cl.txt', 'r') as f:
    s = f.read().strip().split('\n')

with open('cl2.txt', 'w') as f:
    for item in s:
        f.write(item + ',\n')