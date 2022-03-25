#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const ll inf = 1ll << 60;
const int maxn = 500000 + 5;

int n, m, q;
vector<PII> G[maxn], rG[maxn];
ll a[maxn], f[maxn], g[maxn];
bool vis[maxn];

void dij(int s, vector<PII>* edge, ll* f) {
  for (int i = 1; i <= n; i++) {
    vis[i] = false;
    f[i] = inf;
  }
  priority_queue<pair<ll,int> > pq;
  f[s] = 0;
  pq.emplace(0, s);
  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();
    if (vis[u]) continue;
    for (auto& x: edge[u]) {
      int v = x.first;
      int w = x.second;
      if (f[v] > f[u] + w) {
        f[v] = f[u] + w;
        pq.emplace(-f[v], v);
      }
    }
  }
}

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1

  ll a[maxn << 2];
  void pushup(int rt) {
    a[rt] = min(a[rt << 1], a[rt << 1 | 1]);
  }
  void build(int l = 1, int r = n - 1, int rt = 1) {
    if (l == r) {
      a[rt] = f[l] + (g[l] != inf ? (g[l] + ::a[l] - 1) / ::a[l] : inf);
      return ;
    }
    int m = (l + r) / 2;
    build(lson);
    build(rson);
    pushup(rt);
  }
  void update(int i, int l = 1, int r = n - 1, int rt = 1) {
    if (l == r) {
      a[rt] = f[l] + (g[l] != inf ? (g[l] + ::a[l] - 1) / ::a[l] : inf);
      return ;
    }
    int m = (l + r) / 2;
    if (i <= m) update(i, lson);
    else update(i, rson);
    pushup(rt);
  }
  ll ans() {
    return min(f[n], a[1]);
  }
}

int main() {
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 1; i <= m; i++) {
    int u, v, c, d;
    scanf("%d%d%d%d", &u, &v, &c, &d);
    assert(1 <= c && c <= 1000000000);
    assert(1 <= d && d <= 1000000000);
    G[u].emplace_back(v, c);
    rG[v].emplace_back(u, d);
  }
  dij(1, G, f);
  dij(n, rG, g);
  for (int i = 1; i <= n; i++) {
    scanf("%lld", a + i);
    assert(a[i] >= 1 && a[i] <= 1000000000);
  }
  if (n == 1) {
    for (int i = 1; i <= q; i++) {
      int x, p;
      scanf("%d%d", &x, &p);
      puts("0");
    }
  } else {
    SegT::build();
    for (int i = 1; i <= q; i++) {
      int x, p;
      scanf("%d%d", &x, &p);
      a[x] = p;
      if (x < n) SegT::update(x);
      printf("%lld\n", SegT::ans());
    }
  }
  return 0;
}