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
#include <limits>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 150000 + 5;

struct LineContainer  {
  static const ll inf = 2e18;
  static bool modeQ;
 
  struct Line {
    mutable ll a, b, end;
    ll intersect(const Line& r) const {
      if (a == r.a) return b > r.b ? inf : -inf;
      ll u = b - r.b, d = r.a - a;
      return u / d - ((u ^ d) < 0 && u % d);
    }
    bool operator<(const Line& r) const {
      return modeQ ? end < r.end : a < r.a;
    }
  };
 
  multiset<Line> S;
  void clear() { S.clear(); }

  // Updates segment end
  bool update(multiset<Line>::iterator it) {
    auto cur = it++; cur->end = inf;
    if (it == S.end()) return false;
    cur->end = cur->intersect(*it);
    return cur->end >= it->end;
  }

  // Insert f(x) = ax + b
  void insert(ll a, ll b) {
    auto it = S.insert({ a, b, inf });
    while (update(it)) it = --S.erase(++it);
    while (it != S.begin() && update(--it)) {
      update(it = --S.erase(++it));
    }
    while (it != S.begin() && update(--it)) {
      update(it = --S.erase(++it));
    }
  }

  // Query max(f(x))
  ll query(ll x) {
    assert(!S.empty());
    modeQ = 1;
    auto l = *S.lower_bound({ 0, 0, x });
    modeQ = 0;
    return l.a * x + l.b;
  }
};

bool LineContainer::modeQ = false;

int n, a[maxn];
vector<int> edge[maxn];

int vis[maxn], siz[maxn], sum, mn, rt;
void getrt(int u, int f) {
  siz[u] = 1; int t = 0;
  for (int v: edge[u]) {
    if (v == f || vis[v]) continue;
    getrt(v, u); siz[u] += siz[v];
    t = max(t, siz[v]);
  }
  t = max(t, sum - siz[u]);
  if (t < mn) mn = t, rt = u;
}
int getrt(int u) {
  sum = siz[u]; mn = 1e9; rt = 0;
  getrt(u, 0); return rt;
}

ll ans = 0;
void solve(int u) {
  vis[u] = true;
  // pair<int,ll> mx(0, 0ll);
  LineContainer ch; ch.insert(0, 0);
  function<void(int,int,int,ll,ll)> dfs = [&](int u, int f, int d, ll s1, ll s2) {
    d++; s1 += 1ll * a[u] * d; s2 += a[u];
    // ans = max(ans, mx.second + s2 * mx.first + s1);
    ans = max(ans, ch.query(s2) + s1);
    for (int v: edge[u]) {
      if (vis[v] || v == f) continue;
      dfs(v, u, d, s1, s2);
    }
  };
  function<void(int,int,int,ll,ll)> dfs2 = [&](int u, int f, int d, ll s1, ll s2) {
    d++; s2 += a[u]; s1 += s2;
    // mx = max(mx, make_pair(d, s1));
    ch.insert(d, s1);
    for (int v: edge[u]) {
      if (vis[v] || v == f) continue;
      dfs2(v, u, d, s1, s2);
    }
  };
  for (int v: edge[u]) {
    if (vis[v]) continue;
    dfs(v, u, 1, a[u], a[u]);
    dfs2(v, u, 0, 0, 0);
  }
  reverse(begin(edge[u]), end(edge[u]));
  // mx = make_pair(0, 0ll);
  ch.clear(); ch.insert(0, 0);
  for (int v: edge[u]) {
    if (vis[v]) continue;
    dfs(v, u, 1, a[u], a[u]);
    dfs2(v, u, 0, 0, 0);
  }
  reverse(begin(edge[u]), end(edge[u]));
  for (int v: edge[u]) {
    if (vis[v]) continue;
    solve(getrt(v));
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  siz[1] = n;
  solve(getrt(1));
  printf("%I64d\n", ans);
  return 0;
}