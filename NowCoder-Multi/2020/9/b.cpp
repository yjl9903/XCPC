#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef long long ll;
const int max_n = 100005;
typedef pair<ll, ll> P;

int T, n;
vector<P> G[max_n];
int a[max_n];

P dfs(int u, int fa) {
  vector<P> o;
  for (auto p : G[u]) {
    int v = p.fi, w = p.se;
    if (v == fa) continue;
    P t = dfs(v, u);
    t.fi += w;
    if (t.se >= w)
      t.se -= w;
    else {
      t.fi += w - t.se;
      t.se = 0;
    }
    o.push_back(t);
  }
  sort(o.begin(), o.end(), [&](P p1, P p2) {
    bool x = (p1.se - p1.fi) >= 0;
    bool y = (p2.se - p2.fi) >= 0;
    if (x != y) {
      return x > y;
    } else if (x == true) {
      if (p1.fi != p2.fi) {
        return p1.fi < p2.fi;
      }
      return p1.se > p2.se;
    } else {
      if (p1.se != p2.se) {
        return p1.se > p2.se;
      }
      return p1.fi < p2.fi;
    }
  });
  ll x = 0, y = a[u];
  for (auto p : o) {
    if (y >= p.fi)
      y -= p.fi, y += p.se;
    else
      x += p.fi - y, y = p.se;
  }
  return P(x, y);
}

int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) G[i].clear();
    for (int i = 1; i <= n; i++) scanf("%d", a + i);
    for (int i = 1; i < n; i++) {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      G[u].push_back(P(v, w));
      G[v].push_back(P(u, w));
    }
    P p = dfs(1, 0);
    printf("%lld\n", p.fi);
  }
  return 0;
}