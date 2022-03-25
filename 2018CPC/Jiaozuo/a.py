#coding = utf-8

m = 10
for i in range(200):
    m = m * 10

i = 1

while i * i <= m:
    print i * i
    i = i + 1