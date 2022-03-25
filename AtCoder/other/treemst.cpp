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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const ll inf = 1ll << 60;
const int maxn = 200000 + 5;

int n, a[maxn];
vector<PII> edge[maxn];

int vis[maxn], siz[maxn], sum, mn, rt;
void getsz(int u, int f) {
  siz[u] = 1; int mx = 0;
  for (auto& x: edge[u]) {
    int v = x.first;
    if (v == f || vis[v]) continue;
    getsz(v, u);
    siz[u] += siz[v];
    mx = max(mx, siz[v]);
  }
  mx = max(mx, sum - siz[u]);
  if (mx < mn) {
    mn = mx; rt = u;
  }
}
int getsz(int u) {
  sum = siz[u]; mn = 1e9;
  getsz(u, 0); return rt;
}

vector< tuple<ll,int,int> > egs;
void solve(int u) {
  vis[u] = 1;
  ll mn = inf; int y;
  function<void(int,int,ll)> dfs = [&](int u, int f, ll d) {
    if (d + a[u] < mn) {
      mn = d + a[u]; y = u;
    }
    for (auto& x: edge[u]) {
      int v = x.first;
      if (v == f || vis[v]) continue;
      dfs(v, u, d + x.second);
    }
  };
  dfs(u, 0, 0);
  dfs = [&](int u, int f, ll d) {
    egs.emplace_back(mn + d + a[u], u, y);
    for (auto& x: edge[u]) {
      int v = x.first;
      if (v == f || vis[v]) continue;
      dfs(v, u, d + x.second);
    }
  };
  dfs(u, 0, 0);
  for (auto& x: edge[u]) {
    if (vis[x.first]) continue;
    solve(getsz(x.first));
  }
}

int pre[maxn];
int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}
int join(int x, int y) {
  x = find(x); y = find(y);
  if (x == y) return false;
  pre[x] = y;
  return true;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  for (int i = 2, u, v, w; i <= n; i++) {
    scanf("%d%d%d", &u, &v, &w);
    edge[u].emplace_back(v, w);
    edge[v].emplace_back(u, w);
  }
  siz[1] = n; solve(getsz(1));
  for (int i = 1; i <= n; i++) pre[i] = i;
  sort(begin(egs), end(egs));
  for (auto& e: egs) {
    ll w; int u, v; tie(w, u, v) = e;
    dbg(w, u, v);
  }
  ll ans = 0;
  for (auto& e: egs) {
    ll w; int u, v; tie(w, u, v) = e;
    if (join(u, v)) {
      ans += w;
    }
  }
  cout << ans << endl;
  return 0;
}