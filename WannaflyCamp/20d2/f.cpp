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
const int maxn = 1000000 + 5;
 
int n, q, son[maxn], siz[maxn], dfn[maxn], tot;
int top[maxn], fa[maxn], fad[maxn], fas[maxn], val[maxn];
vector<PII> edge[maxn];
 
struct BIT {
  ll a[maxn];
  void update(int i, int x) {
    for (; i <= n; i += i & -i) a[i] += x;
  }
  void update(int l, int r, int x) {
    if (l > r) return ;
    update(l, x); update(r + 1, -x);
  }
  ll query(int i) {
    ll r = 0;
    for (; i; i -= i & -i) r += a[i];
    return r;
  }
} hf, hh;
 
void dfs(int u, int f) {
  fa[u] = f; siz[u] = 1;
  for (auto& x: edge[u]) {
    int v = x.first;
    if (v == f) continue;
    fad[v] = x.second;
    dfs(v, u); siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) son[u] = v;
  }
}
void dfs(int u, int f, int tp) {
  top[u] = tp; dfn[u] = ++tot;
  if (son[u]) dfs(son[u], u, tp);
  for (auto& x: edge[u]) {
    int v = x.first;
    if (v == f) continue;
    if (v == son[u]) {
      fas[u] = x.second;
      continue;
    }
    dfs(v, u, v);
  }
}

ll sum = 0, lgt[maxn];
void update(int u, int x) {
  sum += x;
  while (u) {
    hf.update(dfn[top[u]], dfn[u], x);
    hh.update(dfn[top[u]], dfn[u] - 1, x);
    lgt[fa[top[u]]] += 1ll * x * fad[top[u]];
    u = fa[top[u]];
  }
}
ll query(int u) {
  return 1ll * fad[u] * (sum - hf.query(dfn[u])) + 1ll * fas[u] * hh.query(dfn[u]) + lgt[u];
}

int main() {
  scanf("%d", &n);
  for (int i = 2, u, v, w; i <= n; i++) {
    scanf("%d%d%d", &u, &v, &w);
    edge[u].push_back({v, w});
    edge[v].push_back({u, w});
  }
  dfs(1, 0); dfs(1, 0, 1);
  scanf("%d", &q);
  int rt = 1, op, u, x;
  while (q--) {
    scanf("%d%d", &op, &u);
    if (op == 1) {
      scanf("%d", &x); update(u, x);
      printf("%I64d\n", query(rt));
    } else if (op == 2) {
      printf("%I64d\n", query(rt = u));
    }
  }
  return 0;
}