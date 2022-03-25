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
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 150000 + 5;

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

int n, q, son[maxn], siz[maxn], dfn[maxn], tot, ivn;
int top[maxn], fa[maxn], val[maxn];
vector<int> edge[maxn];

struct BIT {
  int a[maxn];
  void update(int i, int x) {
    for (; i <= n; i += i & -i) a[i] = add(a[i], x);
  }
  void update(int l, int r, int x) {
    if (l >= r) return ;
    update(l, x); update(r, mod - x);
  }
  int query(int i) {
    int r = 0;
    for (; i; i -= i & -i) r = add(r, a[i]);
    return r;
  }
} h;

void dfs(int u, int f) {
  fa[u] = f;
  dfn[u] = ++tot; siz[u] = 1;
  for (int v: edge[u]) {
    if (v == f) continue;
    dfs(v, u); siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) son[u] = v;
  }
}
void dfs(int u, int f, int tp) {
  top[u] = tp;
  if (son[u]) dfs(son[u], u, tp);
  for (int v: edge[u]) {
    if (v == f || v == son[u]) continue;
    dfs(v, u, v);
  }
}

void update(int u, int d) {
  val[u] = add(val[u], d);
  int tot = mul(d, siz[u]);
  h.update(1, dfn[u], tot);
  h.update(dfn[u] + siz[u], n + 1, tot);
  if (son[u]) {
    int v = son[u]; tot = mul(d, n - siz[v]);
    h.update(dfn[v], dfn[v] + siz[v], tot);
  }
}

int query(int u) {
  int ans = h.query(dfn[u]), x = u;
  while (x) {
    int tp = top[x];
    ans = add(ans, mul(val[fa[tp]], n - siz[tp]));
    x = fa[tp];
  }
  return add(val[u], mul(ans, ivn));
}

int main() {
  scanf("%d%d", &n, &q);
  ivn = inv(n);
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  dfs(1, 0); dfs(1, 0, 1);
  int op, u, d;
  while (q--) {
    scanf("%d%d", &op, &u);
    if (op == 1) {
      scanf("%d", &d);
      update(u, d);
    } else if (op == 2) {
      printf("%d\n", query(u));
    }
  }
  return 0;
}