# PKu2251

> 2018 - 5 - 18

DFS+回溯超时，BFS可以AC。

# PKu2299 Ultra-QuickSort

> 2018 - 5 - 23

题目要求一个序列的逆序数，使用一个树状数组bit维护了从小到大每个数字出现次数的和，用这个有序的树状数组求得小于等于某个位置所有数的个数。

更新：使用stl的离散化技巧。

# PKu1077 Eight

> 2018 - 6 - 22

单向BFS+Hash判重。

Hash判重：

将一个状态压缩成为一个整数，添加到Hash表中，但是由于可能有1e9个状态，内存开不了这么大，故采用取模然后链表的方式。

将Hash压缩的整数取模后得到的Hash值，添加到类似于领接表的大链表中，通过链表进行查找。

> 2018 - 6 - 23

交错双向BFS。

https://blog.csdn.net/thudaliangrx/article/details/50659007

# PKu1611 The Suspects

> 2018 - 6 - 23

并查集裸题。

# PKu2492 A Bug's Life

> 2018 - 6 - 23

二元的权值并查集模板。

# PKu1852 Ants

> 2018 - 6 - 25

忽略两个蚂蚁之间的区别，本质都是交错前进。

# PKu2386 Lake Counting

> 2018 - 6 - 25

dfs求联通块。

# PKu3617 Best Cow Line

> 2018 - 6 - 25

字符串问题，从一个串头尾选择一个小的入栈，如果相同则比较他们下一对头尾，即正序序列和逆序序列进行比较，直到分出大小入栈。

# PKu3069 Saruman's Army 

> 2018 - 6 - 26

注意理解题意。

# PKu3253 Fence Repair

> 2018 - 6 - 26

提议理解！

优先队列。

# PKu2431 Expedition

> 2018 - 6 - 29

优先队列。

题意很多细节没说清楚。

BFS错误。

让车尽量走远，经过的加油站全部存到优先队列中，如果车无法走到下一个停靠点，则让车在之前加最多的油，模拟。

# PKu1127 Jack Straws

> 2018 - 6 - 29

计算几何。

给出一组线段，若两线段相连，则线段联通，询问两个线段是否联通。

并查集维护联通关系，预处理任意两条边，若两条边平行，看是否有一个顶点在另外一条边上，若不平行，求出交点后，判断交点是不是在两条边上。

# PKu2318 Toys

> 2018 - 7 - 1

特判边界，二分找归属位置。

叉积判断左右关系。

# PKu2398 Toy Storage

> 2018 - 7 - 2

同PKu2318，对输入进行排序和输出格式

# PKu2007 Scrambled Polygon

> 2018 - 7 - 4

极角排序。

# PKu3254 Corn Fields

> 2018 - 7 - 6

状压dp。

直接输入状态，不填的位置记为1，方便状态直接与错误态求并集，若非空，则错误。

是否存在相邻的判断: x & (x << 1)

注意位运算的顺序，易错点！

# PKu3311 Hie with the Pie

> 2018 - 7 - 7

状压DP解决TSP问题。

dp\[s][i] 表示已经走过了状态s并且s的终点是i。

初状态dp\[1][0] = 0

转移方程：dp\[s | (1 << j)][j] = min( , dp\[s][i] + map\[i][j])

从以i为终点的状态s，走一步到达 j 的最小距离。

# PKu2686 Traveling by Stagecoach

> 2018 - 7 - 10

dp\[s][i]表示车票使用情况s下，到达i所用的最短时间。

# PKu1426 Find The Multiple 

> 2018 - 7 - 10

BFS预处理01串，本地跑了最后两个时间特别长的。

# PKu3126 Prime Path

> 2018 - 7 - 11

线性筛法 + BFS.

# PKu1804 Brainman

> 2018 - 7 - 11

归并排序求逆序对。

在归并排序中添加一句即可。

归并过程中，对左右先进行排序，左右区间已经保证有序后，对 l...m 和 m+1...r 两个区间都是有序的，如果做区间的一个数大于右区间的一个数，则左区间剩余的也会大于右边那个数。

# PKu2533 Longest Ordered Subsequence

> 2018 - 7 - 11

LIS模板题，O(n^2)和O(nlogn)

# PKu1065 Wooden Sticks

> 2018 - 7 - 11

二维偏序问题。

排序搞掉一维，对于第二维，求最长递增子序列的数量。

由Dilworth定理，链的个数等于最长反链的长度。

# PKu1548 Robots

> 2018 - 7 - 11

二维偏序 + Dilworth定理 + LIS。

# PKu1384 Piggy-Bank

> 2018 - 7 - 16

完全背包变形。

求恰好填充某一重量的最小价值。

将dp全部初始化为inf，dp[0] = 0

for i = 1...n:
  for j = w[i]...f-e:
    dp[j] = min(dp[j], dp[j - w[i]] + p[i])

此时所有dp有值的都是恰好拼成的。

# PKu1664 放苹果 

> 2018 - 7 - 17

整数n的m划分数。

dp\[i][j] 表示 j 的 i 划分。

状态转移方程: dp\[i][j] = dp\[i - 1][j] + dp\[i][j - i]

这样保证了不会有重复计算，后一项表示了从 j - i 的 i 划分的每种情况中的每个数都加一，转移到 j 的 i 划分。

# PKu1032 Parliament

> 2018 - 7 - 17

求n的一种划分a1,a2,...,am，使得 a1 * a2 * ... * am 最大

只要求 2, 3, 4, 5,..., m即可，对于剩余部分加到分别加到后面的项。

# PKu1014 Dividing 

> 2018 - 7 - 18

多重背包的n^2优化。

dp\[i][j] 表示使用到第i个物品组成j时，使用第i个物品的剩余量的最大值。

因此 dp\[i][j] = m[i] when dp\[i - 1][j] >= 0
dp\[i][j] = -1 when dp\[i - 1][j] < 0 and (j < v[i] || dp\[i][j - v[i]])
dp\[i][j] = dp\[i][j - v[i]] - 1

# PKu1085 炮兵阵地

> 2018 - 7 - 18

状压DP好题。

dp\[i]\[s1][s2]，表示第i行为状态s，i-1行为状态s2时的最大值。

注意不要爆内存，提前压缩好状态。

# PKu2823 Sliding Window

> 2018 - 7 - 18

单调队列模板。

先将 k - 1 个元素入队，每次入队时保证当前元素大于（小于）队尾元素，并且检查队首元素是否在滑动窗口内，之后更新答案为队首元素。

# PKu1276 Cash Machine

> 2018 - 7 - 19

多重背包的二进制优化。

# PKu3468 A Simple Problem with Integers

> 2018 - 7 - 21

线段树，维护区间和，区间更新，区间查询。

# PKu3264 Balanced Lineup

> 2018 - 7 - 21

线段树，维护区间最值，区间查询。

# PKu3321 Apple Tree

> 2018 - 7 - 22

dfs序 + 线段树 单点修改 区间查询。

领接表建图，卡vector。

# PKu1328 Radar Installation

> 2018 - 7 - 23

将每个岛对应的雷达范围压成区间，求最少多少点可以覆盖掉所有区间。

右端点排序，贪心扫一遍。

# PKu2352 Stars

> 2018 - 7 - 25

线段树或者树状数组维护。

# PKu3624 Charm Bracelet

> 2018 - 7 - 25

01背包。

# PKu2104 K-th Number 

> 2018 - 7 - 25

主席树求区间第k小。

# PKu3903 Stock Exchange

> 2018 - 7 - 27

LIS的nlogn优化。

# PKu1458 Common Subsequence

> 2018 - 7 - 27

LCS.

# PKu3687 Labeling Balls

> 2018 - 7 - 29

输出非字典序的拓扑排序，注意输出答案。

# PKu2976 Dropping tests

> 2018 - 8 - 3

01分数规划 + 二分。

# PKu1088 滑雪

> 2018 - 8 - 5

记忆化搜索。

# PKu1251 Jungle Roads

> 2018 - 8 - 18

最小生成树模板。

# PKu1287 Networking

> 2018 - 8 - 18

最小生成树模板。

# PKu2926 Requirements

> 2018 - 8 - 22

五维最远曼哈顿距离。

# PKu2528 Mayor's posters

> 2018 - 9 - 20

线段树。

离散化。

维护每个区间[l, r]，-1表示区间内有多个海报，其他表示区间内全是这种海报，pushdown(rt)，pushup(rt)改写为对应形式。

维护每张海报的长度，最后输出所有长度为正数的海报数量。

# PKu3368 Frequent values

> 2018 - 9 - 21

预处理每个位置出现的数的次数。

对于每个询问特判，与左端点相同的数的数量，剩余部分rmq解决。

# PKu1182 食物链

> 2018 - 9 - 21

带权并查集的应用。

val[x] = 0: x 与 pre[x] 同类

val[x] = 1: x 吃 pre[x] 

val[x] = 2: pre[x] 吃 x

路径压缩和查找时维护一下 val[x] 即可。

# PKu3281 Dining

> 2018 - 9 - 21

建一个超级源点和超级汇点，源点连上每个 f 物品，流量为 1，汇点连上每个 d 物品，流量为 1。

对于每头牛，拆成两个点，他喜欢的 f 与左边相连，他喜欢的 d 与右边相连，中间连一下，流量均为 1。

跑一个 dinic 即可完成匹配。

# PKu2230 Watchcow

> 2018 - 9 - 27

输出一个有向图的欧拉回路。

# PKu1236 Network of Schools

> 2018 - 10 - 10

tarjan。

缩点后，找到所有入度为 0 的点为分配的个数。

第二问是求最少加多少条边可以将整个图变成一个强联通分量。

要建边指向入度为0的边，建边指出出度为0的边，答案为两种情况的最大值。

# PKu2774 Long Long Message

> 2018 - 10 - 30

将两个串用一个小字符连在一起后跑后缀数组。

答案就是 max(height[i]), 满足 sa[i] 和 sa[i - 1] 不在一个串中。

# PKu1509 Glass Beads

> 2018 - 11 - 1

循环同构串的最小表示法。

# PKu1741 Tree

> 2019 - 2 - 12

树分治。

# PKu3764 The xor-longest Path

> 2019 - 2 - 14

树上路径最大异或和。

# PKu2559 Largest Rectangle in a Histogram

> 2019 - 5 - 9

单调栈。

# PKu1419 Graph Coloring

> 2019 - 5 - 29

一般图最大独立集。

# PKu2674 弹性碰撞

> 2019 - 6 - 7

# PKu3261 Milk Patterns

> 2019 - 6 - 15

后缀数组 + 二分。

# PKu1743 Musical Theme

> 2019 - 6 - 15

后缀数组 + 二分。

# PKu3294 Life Forms 

> 2019 - 6 - 15

后缀数组 + 二分。

# PKu2234 Matches Game

> 2019 - 6 - 16

NIM 博弈。

# PKu2311 Cutting Game

> 2019 - 6 - 16

SG 函数。

# PKu3415 Common Substrings

> 2019 - 6 - 17

后缀数组 + 单调栈。

# PKu2778 DNA Sequence

> 2019 - 7 - 4

AC 自动机 + DP + 矩阵快速幂。

# PKu3275 Ranking the Cows

> 2020 - 7 - 7

图的传递闭包。
