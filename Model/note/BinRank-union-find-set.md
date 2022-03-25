# 带权值的并查集

rank[x]代表当前与pre[x]相对关系, rank[x] == 1表示异性, rank[x] == 0表示同性。

## 1. find(int x)

```
○ root, rank = 0 
↑
○ rank = 1
↑
○ rank = 1
```

find()操作回溯时，先暂存路径压缩后的根节点，返回时当前节点指向根节点。

当前节点x与他的父亲节点pre[x]权值相同时，那么x与根节点同性：

+ 若rank[x] == rank[pre[x]] == 0, 那么x, pre[x], root同性。

+ 若rank[x] == rank[pre[x]] == 1, 那么pre[x]和root异性，x和pre[x]异性，因此x和root同性。

反之，x和根节点异性。

## 2. join(int x, int y)

```
          yy ○      ○ xx
            ↗ ↖    ↗
rank[y] = 1 ○  ○   ○ rank[x] = 1
            ↑
            ○
```

找到x的根节点xx, y的根节点yy。

若两者不在一个集合中，将yy指向xx，并修改rank[yy]。

x和y异性。

rank[y] == rank[x]时, rank[yy] = 1

+ rank[y] == rank[x] == 1, 则xx与x异性，yy与y异性，由x和y异性，那么xx和yy异性。

+ rank[y] == rank[x] == 0, xx和yy异性。

反之亦然。

**注意:** 回溯思想和取模的应用。
