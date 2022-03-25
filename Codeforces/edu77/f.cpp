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
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

namespace {
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
  int Inv[maxn];
  inline int inv(int x) {
    if (x < maxn) return Inv[x];
    return qpow(x, mod - 2);
  }
}

namespace SegT {
  const int maxm = maxn * 40;
  int tot, ls[maxm], rs[maxm];
  int a[maxm], taga[maxm], b[maxm], tagb[maxm];
  vector<int> nodes;
  void clear(int l, int r, int rt) {
    if (!rt) return ;
    if (l < r) {
      int m = (l + r) / 2;
      clear(l, m, ls[rt]);
      clear(m + 1, r, rs[rt]);  
    }
    ls[rt] = rs[rt] = 0;
    a[rt] = taga[rt] = 0;
    b[rt] = tagb[rt] = 0;
    nodes.push_back(rt);
  }
  void update(int L, int R, int x, int y, int l, int r, int& rt) {
    if (!rt) {
      if (nodes.empty()) rt = ++tot;
      else rt = nodes.back(), nodes.pop_back();
    }
    int len = min(R, r) - max(L, l) + 1;
    if (L <= l && r <= R) {
      taga[rt] = add(taga[rt], x);
      tagb[rt] = add(tagb[rt], y);
      return ;
    }
    a[rt] = add(a[rt], mul(len, x));
    b[rt] = add(b[rt], mul(len, y));
    int m = (l + r) / 2;
    if (L <= m) update(L, R, x, y, l, m, ls[rt]);
    if (R > m) update(L, R, x, y, m + 1, r, rs[rt]);
  }
  PII query(int L, int R, int l, int r, int rt) {
    if (!rt) return {0, 0};
    if (L <= l && r <= R) {
      return { add(a[rt], mul(taga[rt], r - l + 1)), add(b[rt], mul(tagb[rt], r - l + 1)) };
    }
    int m = (l + r) / 2;
    int len = min(R, r) - max(L, l) + 1;
    PII ans(mul(taga[rt], len), mul(tagb[rt], len));
    if (L <= m) {
      PII x = query(L, R, l, m, ls[rt]);
      ans.first = add(ans.first, x.first);
      ans.second = add(ans.second, x.second);
    }
    if (R > m) {
      PII x = query(L, R, m + 1, r, rs[rt]);
      ans.first = add(ans.first, x.first);
      ans.second = add(ans.second, x.second);
    }
    return ans;
  }
};

int n, ans, root[maxn];
int dep[maxn], son[maxn], siz[maxn];
int tot, tin[maxn], tout[maxn], rdfn[maxn];
PII a[maxn];
vector<int> edge[maxn];

inline int invL(int u) {
  return inv(a[u].second - a[u].first + 1);
}

void predfs(int u, int f) {
  tin[u] = ++tot; rdfn[tot] = u;
  siz[u] = 1; dep[u] = dep[f] + 1;
  for (int v: edge[u]) {
    if (v == f) continue;
    predfs(v, u);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) son[u] = v;
  }
  tout[u] = tot;
}

int depu;
void cal(int u, int root) {
  PII q = SegT::query(a[u].first, a[u].second, 1, 1e5, root);
  ans = add(ans, mul(invL(u), q.first));
  ans = add(ans, mul(mul(invL(u), sub(dep[u], depu)), q.second));
}
void upd(int u, int root) {
  int x = mul(dep[u], invL(u));
  int y = invL(u);
  SegT::update(a[u].first, a[u].second, x, y, 1, 1e5, root);
}

void dfs(int u, int f) {
  if (!son[u]) {
    int x = mul(dep[u], invL(u));
    int y = invL(u);
    SegT::update(a[u].first, a[u].second, x, y, 1, 1e5, root[u]);
    return ;
  }
  dfs(son[u], u);
  int rt = root[son[u]];
  depu = 2 * dep[u];
  cal(u, root[u] = rt);
  upd(u, root[u]);
  for (int v: edge[u]) {
    if (v == f || v == son[u]) continue;
    dfs(v, u);
    SegT::clear(1, 1e5, root[v]);
    depu = 2 * dep[u];
    for (int i = tin[v]; i <= tout[v]; i++) {
      cal(rdfn[i], rt);
    }
    for (int i = tin[v]; i <= tout[v]; i++) {
      upd(rdfn[i], rt);
    }
  }
}

int main() {
  for (int i = 1; i < maxn; i++) Inv[i] = qpow(i, mod - 2);
  scanf("%d", &n);
  int xs = 1;
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &a[i].first, &a[i].second);
    xs = mul(xs, a[i].second - a[i].first + 1);
  }
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  predfs(1, 0);
  dfs(1, 0);
  printf("%d\n", mul(xs, ans));
  return 0;
}