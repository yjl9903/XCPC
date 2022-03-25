#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <map>
#include <set>
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 300000 + 5;

inline int add(int x, int y) {
  x += y;
  return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
  x -= y;
  return x < 0 ? x += mod : x;
}
inline int mul(int x, int y) {
  return 1ll * x * y % mod;
}
inline int qpow(int x, ll n) {
  int r = 1;
  while (n > 0) {
    if (n & 1) r = 1ll * r * x % mod;
    n >>= 1; x = 1ll * x * x % mod;
  }
  return r;
}
inline int inv(int x) {
  return qpow(x, mod - 2);
}

int n, a[maxn], dp[maxn], pre[maxn];
vector<int> bag[maxn];

struct Node {
  int val, cnt;
  void clear() {
    val = -inf; cnt = 0;
  }
  Node operator+(const Node& b) const {
    if (val == b.val) return (Node){ val, cnt + b.cnt };
    else if (val > b.val) return (Node){ val, cnt };
    else return (Node){ b.val, b.cnt };
  }
  Node operator+=(const int& b) {
    val += b;
  }
} b[maxn * 4];
int tag[maxn * 4];
void build(int l, int r, int rt) {
  b[rt].clear(); tag[rt] = 0;
  if (l == r) {
    b[rt].cnt = 1; return ;     
  }
  int m = (l + r) / 2;
  build(lson); build(rson);
}
void pushdown(int rt) {
  if (!tag[rt]) return ;
  int& t = tag[rt];
  b[rt << 1] += t;
  tag[rt << 1] += t;
  b[rt << 1 | 1] += t;
  tag[rt << 1 | 1] += t;
  t = 0;
}
void update(int L, int R, int x, int l = 1, int r = n, int rt = 1) {
  if (L <= l && r <= R) {
    b[rt] += x; tag[rt] += x;
    return ;
  }
  int m = (l + r) / 2; pushdown(rt);
  if (L <= m) update(L, R, x, lson);
  if (R > m) update(L, R, x, rson);
  b[rt] = b[rt << 1] + b[rt << 1 | 1];
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    bag[i].push_back(0);
  }
  build(1, n, 1);
  for (int i = 1; i <= n; i++) {
    pre[i] = pre[i - 1];
    update(i, i, n - 1);
    update(bag[a[i]].back() + 1, i - 1, -1);
    bag[a[i]].push_back(i);
    int pos = (int)bag[a[i]].size() - 3;
    if (pos >= 0) {
      update(bag[a[i]][pos] + 1, bag[a[i]][pos + 1], 1);
    }
    // int l = query(1, n, 1);
    // if (l <= n) {
    //   dbg(l, i);
    // }
  }
  int sum = qpow(2, n - 1);
  printf("%d\n", sub(sum, dp[n]));
  return 0;
}