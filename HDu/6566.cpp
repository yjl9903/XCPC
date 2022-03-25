#include <cstdio>
#include <cassert>
#include <vector>
using namespace std;
using ll = long long;
const int maxn = 100 + 5;
const int maxm = 5000 + 5;

struct Node {
  int val;
  ll cnt;

  void operator += (const Node& rhs) {
    if (val == rhs.val) {
      cnt += rhs.cnt;
    } else if (val < rhs.val) {
      val = rhs.val;
      cnt = rhs.cnt;
    }
  }
} f[maxn][maxm], g[maxn][maxm];

int n, m, a[maxn], b[maxn];
int fa[maxn], dfn[maxn], rdfn[maxn];
vector<int> edge[maxn], chain[maxn];

namespace hld {
  int tot, siz[maxn], dep[maxn], son[maxn], top[maxn];
  void dfs(int u, int f) {
    fa[u] = f; siz[u] = 1; son[u] = 0;
    int m = -1;
    for (auto& v: edge[u]) {
      if (v == f) continue;
      dep[v] = dep[u] + 1;
      dfs(v, u);
      siz[u] += siz[v];
      if (siz[v] > m) son[u] = v, m = siz[v];
    }
  }
  void dfs(int u, int f, int tp) {
    dfn[u] = ++tot;
    rdfn[tot] = u;
    top[u] = tp;
    for (auto& v: edge[u]) {
      if (v == f || v == son[u]) continue;
      dfs(v, u, v);
    }
    if (son[u]) {
      dfs(son[u], u, tp);
    }
  }
  void build() {
    tot = 0;
    dep[1] = 0;
    dfs(1, 0);
    dfs(1, 0, 1);
    for (int i = 1; i <= n; i++) {
      int x = i;
      while (x) {
        chain[i].push_back(x);
        x = fa[top[x]];
      }
    }
  }
}

int main() {
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      edge[i].clear();
      chain[i].clear();
    }
    for (int i = 1; i <= n; i++) {
      scanf("%d%d", a + i, b + i);
    }
    for (int i = 2, u, v; i <= n; i++) {
      scanf("%d%d", &u, &v);
      edge[u].push_back(v);
      edge[v].push_back(u);
    }

    hld::build();
    for (int s = 0; s < 2; s++) {
      for (int j = 0; j <= m; j++) {
        f[s][j] = { 0, 0 };
      }
    }
    f[0][0] = { 0, 1 };
    f[1][a[rdfn[1]]] = { b[rdfn[1]], 1 };
    for (int i = 2; i <= n; i++, swap(f, g)) {
      int u = rdfn[i];
      int ss = 1 << chain[u].size();
      for (int s = 0; s < ss; s++) {
        for (int j = 0; j <= m; j++) {
          g[s][j] = { 0, 0 };
        }
      }
      int pre = rdfn[i - 1], fa = -1;
      int ps = 1 << chain[pre].size();
      vector<int> mp(chain[pre].size(), -1);
      for (int i = 0; i < chain[pre].size(); i++) {
        int x = chain[pre][i];
        if (x == ::fa[u]) fa = i;
        for (int j = 0; j < chain[u].size(); j++) {
          if (chain[u][j] == x) {
            mp[i] = j;
            break;
          }
        }
      }
      assert(fa != -1);
      for (int s = 0; s < ps; s++) {
        int nxt = 0;
        for (int i = 0; i < chain[pre].size(); i++) {
          if (s >> i & 1) {
            if (mp[i] != -1) {
              nxt |= 1 << mp[i];
            }
          }
        }
        for (int j = 0; j <= m; j++) {
          if (f[s][j].cnt == 0) continue;
          g[nxt][j] += f[s][j];
          if ((s >> fa & 1) == 0 && j + a[u] <= m) {
            g[nxt | 1][j + a[u]] += Node { f[s][j].val + b[u], f[s][j].cnt };
          }
        }
      }
    }

    printf("Case %d:\n", ++kase);
    for (int i = 1; i <= m; i++) {
      Node ans { 0, 0 };
      for (int s = 0; s < (1 << chain[rdfn[n]].size()); s++) {
        ans += f[s][i];
      }
      printf("%lld%c", ans.cnt, " \n"[i == m]);
    }
  }
  return 0;
}