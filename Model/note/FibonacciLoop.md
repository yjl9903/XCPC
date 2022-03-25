# 斐波那契额数列循环节

矩阵快速幂 + 数论 + 结论

斐波那契额数列变换矩阵 A = {1, 1; 1, 0}。

快速幂思想。

具体过程：

n = sigma(p_i ^ a_i),

loop(n) = PI(loop(p_i ^ a_i))

loop(p_i ^ a_i) = p_i ^ (a_i - 1) * loop(p)

loop(p):
    if legendre(p) = qpow(5, (p - 1) >> 1, p) == 1:
        let n = p - 1
    else:
        let n = 2 * (p + 1)
    for i in n's factor:
        if power(A, i - 1, p) (1, 0) == (1, 0):
            output i