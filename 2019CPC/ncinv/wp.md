# 签到题

右键源码，ctrl+F 搜索flag，翻一下，签到题flag在标签的属性里。

# sendRedirect

点击去发现跳转到了google，用chrome network找到get请求，状态码302，response headers 里面有一个奇怪的值 nusctf。

看起来像是base64，解出来不对，结合后面re2，感觉也是base58，猜一发，解出来了。

# Re1

ida, F5。

注意到输入3个数,a,b,c, a < b < c < 999，且 a,b,c 为 xyx 形式的数。

盲猜是正的，枚举一下，有 3 组解试一下。

292-323-565

424-565-666

444-959-989

# Do You Know J Language

教程：[J](https://github.com/azurity/learnJ_zh_cn/tree/master/md)

扫了一遍，大概意思是两行5列的字符串 wrong 和 right，根据后面的输入值选一个出来。

把后面拿出来试一试发现是用后面的字符串生成一个数组，猜一下是和前面的比对。

修改试试，发现挺连续的比较好试，从左到右把每个位置对上即可。

```
((128&|@+/)\)(3&u:) 'J_l4ng_1s_3a5y!'
```

# Re2

ida，F5，string看一看，看到一个密文和字符集 "987...321ABCD...abcd..."。

encode函数里面有模 58 的操作，盲猜是base58，但是字符集顺序不一样，改一下密文，解码。

外面试了下，猜了一个 nust{}。

# 代码

## RE

```python
import os

l = []

for i in range(10):
    for j in range(10):
        l.append(i * 100 + j * 10 + i)

print(l)

for i in range(len(l)):
    for j in range(i + 1, len(l)):
        for k in range(j + 1, len(l)):
            with open('1.txt', 'w') as f:
                f.write(str(l[i]) + ' ' + str(l[j]) + ' ' + str(l[k]))
            res = os.popen('./re1 <1.txt').read().strip().lstrip('input your flag:')
            print(res, end='')
```