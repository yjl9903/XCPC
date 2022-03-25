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
const int maxn = 500000 + 5;

int n, m, q, a[maxn], qx[maxn];
int from[maxn], to[maxn];
bool op[maxn], del[maxn];

int pre[maxn], siz[maxn];
int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}

vector<int> edge[maxn];
int tot, L[maxn], R[maxn], rdfn[maxn];
void dfs(int u) {
  L[u] = ++tot;
  rdfn[tot] = u;
  for (int v: edge[u]) {
    dfs(v);
  }
  R[u] = tot;
}

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1

  int pos[maxn << 2];
  void pushup(int rt) {
    int L = pos[rt << 1], R = pos[rt << 1 | 1];
    pos[rt] = a[L] >= a[R] ? L : R;
  }
  void build(int l = 1, int r = n + n, int rt = 1) {
    if (l == r) {
      pos[rt] = rdfn[l];
      return ;
    }
    int m = (l + r) / 2;
    build(lson);
    build(rson);
    pushup(rt);
  }
  void update(int i, int l = 1, int r = n + n, int rt = 1) {
    if (l == r) return ;
    int m = (l + r) / 2;
    if (i <= m) update(i, lson);
    else update(i, rson);
    pushup(rt);
  }
  int query(int L, int R, int l = 1, int r = n + n, int rt = 1) {
    if (L <= l && r <= R) return pos[rt];
    int m = (l + r) / 2;
    if (R <= m) {
      return query(L, R, lson);
    } else if (L > m) {
      return query(L, R, rson);
    } else {
      int x = query(L, R, lson);
      int y = query(L, R, rson);
      return a[x] >= a[y] ? x : y;
    }
  }
}

int main() {
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", from + i, to + i);
  }
  for (int i = 1; i <= q; i++) {
    int op;
    scanf("%d%d", &op, qx + i);
    if (op == 2) {
      ::op[i] = true;
      del[qx[i]] = true;
    }
  }
  for (int i = 1; i <= n; i++) {
    pre[i] = i;
    siz[i] = 1;
  }
  int tot = n;
  auto link = [&](int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return false;
    tot++;
    pre[tot] = tot;
    siz[tot] = siz[x] + siz[y];
    edge[tot].push_back(x);
    edge[tot].push_back(y);
    pre[x] = tot;
    pre[y] = tot;
    return true;
  };
  for (int i = 1; i <= m; i++) {
    if (del[i]) continue;
    link(from[i], to[i]);
  }
  for (int i = q; i >= 1; i--) {
    if (op[i]) {
      link(from[qx[i]], to[qx[i]]);
    } else {
      int y = find(qx[i]);
      qx[i] = y;
    }
  }
  for (int i = 1; i <= tot; i++) {
    if (i == find(i)) {
      dfs(i);
    }
  }
  SegT::build();
  for (int i = 1; i <= q; i++) {
    if (op[i]) continue;
    int pos = SegT::query(L[qx[i]], R[qx[i]]);
    printf("%d\n", a[pos]);
    a[pos] = 0;
    SegT::update(L[pos]);
  }
  return 0;
}