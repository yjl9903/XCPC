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
#ifdef XLor
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
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
const int maxn = 200000 + 5;

int q, qx[maxn], qy[maxn], qp[maxn];
bool type[maxn];

vector<PII> edge[maxn];
int m, val[maxn], L[maxn], R[maxn];
void dfs(int u) {
  L[u] = ++m;
  for (auto x: edge[u]) {
    int v = x.first;
    val[v] = val[u] ^ x.second;
    dfs(v);
  }
  R[u] = m;
}

namespace PTrie {
  #define lson l, m, ls[rt]
  #define rson m + 1, r, rs[rt]

  int tot = 1, root[maxn], ls[maxn * 300], rs[maxn * 300];
  int cnt[maxn * 300];

  const int B = 30;

  vector<int> L, R;
  int query(int x) {
    int ans = 0;
    for (int i = B; i >= 0; i--) {
      int b = (x >> i) & 1;
      int sum = 0;
      if (b == 0) {
        for (int& x: L) sum -= cnt[rs[x]];
        for (int& x: R) sum += cnt[rs[x]];
      } else {
        for (int& x: L) sum -= cnt[ls[x]];
        for (int& x: R) sum += cnt[ls[x]];
      }
      // dbg(x, i, sum);
      // dbg("L");
      // for (int x: L) dbg(x);
      // dbg("R");
      // for (int x: R) dbg(x);
      if (sum) {
        ans += 1 << i;
        for (int& x: L) x = b == 0 ? rs[x] : ls[x];
        for (int& x: R) x = b == 0 ? rs[x] : ls[x];
      } else {
        for (int& x: L) x = b == 0 ? ls[x] : rs[x];
        for (int& x: R) x = b == 0 ? ls[x] : rs[x];
      }
    }
    return ans;
  }

  inline void insert(int i, int val) {
    auto ins = [&](int& rt) {
      if (!rt) rt = ++tot;
      int u = rt;
      for (int i = B; i >= 0; i--) {
        cnt[u]++;
        int b = (val >> i) & 1;
        if (b == 0) {
          if (!ls[u]) ls[u] = ++tot;
          u = ls[u];
        } else {
          if (!rs[u]) rs[u] = ++tot;
          u = rs[u];
        }
      }
      cnt[u]++;
    };
    for (; i <= m; i += i & -i) ins(root[i]);
  }
  inline int query(int l, int r, int x) {
    L.clear(); R.clear();
    for (int i = l - 1; i; i -= i & -i) L.push_back(root[i]);
    for (int i = r; i; i -= i & -i) R.push_back(root[i]);
    return query(x);
  }
}

int main() {
  scanf("%d", &q);
  int sz = 1;
  for (int i = 1; i <= q; i++) {
    char buf[10];
    int x, y;
    scanf("%s%d%d", buf, &x, &y);
    qx[i] = x;
    qy[i] = y;
    if (buf[0] == 'A') {
      type[i] = true;
      edge[x].emplace_back(++sz, y);
      qp[i] = sz;
    }
  }
  dfs(1);
  PTrie::insert(1, 0);
  for (int i = 1; i <= q; i++) {
    if (type[i]) {
      // add
      dbg(L[qp[i]], val[qp[i]]);
      PTrie::insert(L[qp[i]], val[qp[i]]);
    } else {
      // qry
      printf("%d\n", PTrie::query(L[qy[i]], R[qy[i]], val[qx[i]]));
    }
  }
  return 0;
}