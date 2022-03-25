#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <utility>
#include <cassert>
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
const int maxn = 2000 + 5;

int n, k, vis[maxn], fa[maxn], a[maxn], c[maxn];
vector<int> edge[maxn], cols[maxn], ring;

void dfs(int u, int f) {
  fa[u] = f; vis[u] = 1;
  for (int v: edge[u]) {
    if (v == f) continue;
    if (vis[v]) {
      if (!ring.empty()) continue;
      ring.push_back(v);
      int x = u;
      while (x != v) {
        ring.push_back(x);
        x = fa[x];
      }
      continue;
    }
    dfs(v, u);
  }
}

namespace hk {
  int n, ans;
  int dx[maxn], dy[maxn];
  int linkx[maxn], linky[maxn];
  int head[maxn], to[maxn * maxn], nxt[maxn * maxn], ecnt;

  void clear(int N) {
    n = N; ecnt = ans = 0;
    ms(linkx, 0xff); ms(linky, 0xff);
  }
  void adde(int u, int v) {
    to[++ecnt] = v; nxt[ecnt] = head[u]; head[u] = ecnt;
    if (linkx[u] == -1 && linky[v] == -1) {
      linkx[u] = v;
      linky[v] = u;
      ans++;
    }
  }
  bool bfs() {
    bool res = 0;
    static int q[maxn], l, r;

    ms(dx, 0); ms(dy, 0);
    l = r = 0;
    for (int i = 1; i <= n; i++)
      if (linkx[i] == -1) q[r++] = i;

    while (l < r) {
      int x = q[l++];
      for (int i = head[x]; i; i = nxt[i]) {
        if (!dy[to[i]]) {
          dy[to[i]] = dx[x] + 1;
          if (linky[to[i]] == -1) res = 1;
          else dx[q[r++] = linky[to[i]]] = dy[to[i]] + 1;
        }
      }
    }
    return res;
  }
  bool dfs(int u) {
    for (int i = head[u]; i; i = nxt[i]) {
      if (dx[u] + 1 == dy[to[i]]) {
        dy[to[i]] = 0;
        if (linky[to[i]] == -1 || dfs(linky[to[i]])) {
          linky[to[i]] = u;
          linkx[u] = to[i];
          return true;
        }
      }
    }
    return false;
  }
  int match() {
    while (bfs()) {
      for (int i = 1; i <= n; i++) {
        if (linkx[i] == -1) ans += dfs(i);
      }
    }
    return ans;
  }
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1, m, x; i <= n; i++) {
    scanf("%d%d", a + i, &m);
    edge[a[i]].push_back(i);
    edge[i].push_back(a[i]);
    while (m--) {
      scanf("%d", &x); 
      cols[i].push_back(x);
    }
  }
  for (int i = 1; i <= k; i++) scanf("%d", c + i);
  dfs(1, 0);
  for (int x: ring) dbg(x);

  hk::clear(n);
  for (int i = 1; i <= n; i++) {
    for (int x: cols[i]) {
      for (int j = 1; j <= k; j++) {
        if (c[j] != x) continue;
        hk::adde(i, j);
      }
    }
  }
  for (int i = 0; i < (int)ring.size(); i++) {
    int tot = ring[i], nxt = ring[0];
    if (i + 1 < (int)ring.size()) nxt = ring[i + 1];
    if (a[tot] == nxt) {
      hk::adde(tot, k + 1);
    } else if (a[nxt] == tot) {
      hk::adde(nxt, k + 1);
    } else assert(0);
  }

  int s = hk::match();
  if (s < n) return puts("-1"), 0;

  vector<PII> ans(k + 2, {0, 0});
  for (int i = 1; i <= n; i++) {
    int id = hk::linkx[i];
    if (id == -1) continue;
    if (id == k + 1) continue;
    ans[id] = { i, a[i] };
  }

  for (int i = 1; i <= k; i++) 
    printf("%d %d\n", ans[i].first, ans[i].second);
  return 0;
}