# LIS

http://www.cnblogs.com/Blackops/p/5853673.html

dp的O(n^2)朴素做法。

```
ms(dp, -1); dp[1] = 1;
for (int i = 2; i <= n; i++){
    int len = 0;
    for (int j = 1; j < i; j++) if (a[j] < a[i] && dp[j] > len) len = dp[j];
    dp[i] = len + 1;
}
int res = 0;
for (int i = 1; i <= n; i++) res = max(res, dp[i]);
```

dp[i]表示前i个的最长递增子序列。

转移方程：dp[i] = max(dp[j])(a[j] < a[i] && j < i) + 1

O(nlogn)的做法：

考虑如果两个位置的LIS长度相同，则应该取位置在前面的那个。

dp[i]表示长度为i的LIS的最大元素。

dp初始化为inf。

遍历i = 1...n，将a[i]二分插入到dp中，维护保存的最大位置，最后即为最长递增子序列。