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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 400000 + 5;

struct Seg {
  int l, r, t;

  bool operator < (const Seg& rhs) const {
    if (r != rhs.r) {
      return r < rhs.r;
    }
    return l < rhs.l;
  }
} a[maxn];

int n, nn;

struct SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1
  
  int a[maxn << 2], tag[maxn << 2];
  void add(int rt, int x) {
    a[rt] += x; tag[rt] += x;
  }
  void pushdown(int rt) {
    add(rt << 1, tag[rt]);
    add(rt << 1 | 1, tag[rt]);
    tag[rt] = 0;
  }
  void update(int L, int R, int x, int l = 1, int r = nn, int rt = 1) {
    if (L <= l && r <= R) {
      add(rt, x);
      return ;
    }
    int m = (l + r) / 2;
    pushdown(rt);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    a[rt] = max(a[rt << 1], a[rt << 1 | 1]);
  }
  int query(int L, int R, int l = 1, int r = nn, int rt = 1) {
    if (L <= l && r <= R) {
      return a[rt];
    }
    int m = (l + r) / 2, ans = 0;
    pushdown(rt);
    if (L <= m) ans = query(L, R, lson);
    if (R > m) ans = max(ans, query(L, R, rson));
    return ans;
  }
} f[2];

vector<int> bag[maxn];

int main() {
  scanf("%d", &n);
  vector<int> lsh = { 0 };
  auto gid = [&](int x) {
    return lower_bound(begin(lsh), end(lsh), x) - begin(lsh) + 1;
  };
  for (int i = 1; i <= n; i++) {
    scanf("%d%d%d", &a[i].l, &a[i].r, &a[i].t);
    lsh.push_back(a[i].l);
    lsh.push_back(a[i].r);
    a[i].t--;
  }
  sort(begin(lsh), end(lsh));
  lsh.resize(unique(begin(lsh), end(lsh)) - begin(lsh));
  nn = lsh.size();

  vector<Seg> vec[2];
  for (int i = 1; i <= n; i++) {
    a[i].l = gid(a[i].l);
    a[i].r = gid(a[i].r);
    bag[a[i].r].push_back(i);
  }

  int dp[2] = { 0, 0 };
  for (int i = 2; i <= nn; i++) {
    for (int x: bag[i]) {
      f[a[x].t ^ 1].update(1, a[x].l - 1, 1);
    }
    dp[0] = max(dp[0], f[1].query(1, i - 1));
    dp[1] = max(dp[1], f[0].query(1, i - 1));
    f[0].update(i, i, dp[0]);
    f[1].update(i, i, dp[1]);
  }
  printf("%d\n", max(dp[0], dp[1]));
  return 0;
}