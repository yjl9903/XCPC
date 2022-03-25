# A Dividing

dp[0][0] = 0

虑dp\[i][j] 为组成 j 时第 i 个数字被用了多少次。

答案为 dp[n][maxs]

# B Decoding Morse Sequences

字典中所有字符使用map存储。

dp[i] 表示组成到 i 位的方案数。

if s[i:j] in word:
    dp[j] += dp[i] * mp[word]

# C Dissatisfying Lift

预处理 k_i 前缀和， (i - 1) * k_i的前缀和，(m - i) * k_i的前缀和。

# D Fourier's Lines

由欧拉示性数公式推知，n条直线线和m个交点一共分出了 n + m + 1 块平面区域。

只需要判断存在性即可，枚举每个情况下，有多少条平行边，考虑记忆化搜索。

# E Spam

同B。

# F Eating Together

dp[i][j] denote the i-th cow and the group of the i-th cow

for i in 1...n:
    dp[i][1] = dp[i - 1][1];
    dp[i][2] = min(dp[i - 1][1], dp[i - 1][2]);
    dp[i][3] = min(dp[i][2], dp[i - 1][3]);
    if (d[i] == 3) dp[i][2]++, dp[i][3]++;
    if (d[i] == 2) dp[i][1]++, dp[i][3]++;
    if (d[i] == 1) dp[i][1]++, dp[i][2]++;

互换1和3重新dp，两次取一个较小值即可。

# K Compromise 

LCS + LCS重新构造。

# L Artificial Intelligence? 

混入了模拟题？