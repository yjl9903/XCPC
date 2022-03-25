# KMP

https://blog.csdn.net/v_july_v/article/details/7041827

考虑朴素的算法，O(n ^ 2)，每次匹配失败时都是将目标串的下标恢复为 0。

那么我们如果考虑目标串有相同的前缀后缀，那么每次回退时只需要到前缀串的结尾位置重新匹配即可，无需完全重来。