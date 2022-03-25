# HDu6397 Character Encoding

组合数。

特判一些等于0的情况。

考虑容斥原理。

令 f(x) = C(m + x - 1, x)

g(x) 表示不定方程中至少有 x 个大于等于 n 的方案数。

g(x) = C(m, x) * f(k - x * n) - g(x + 1)

# HDu6401 Magic Square

# HDu6406 Taotao Picks Apples

ST表。

二分查找 p 后面第一个大于 q 的位置。

反向dp打出以 x 为开始的序列长度。

预处理每个点是否是在一开始的序列中，他的前一个在序列的元素和每个位置的答案。

分类讨论。