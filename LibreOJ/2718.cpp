#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 400000 + 5;

int n, m, Q, K, S;

struct Edge {
  int from, to, w, h;

  bool operator < (const Edge& b) const {
    return h > b.h;
  }
} eg[maxn];
vector<Edge> G[maxn];

int dis[maxn];
bool vis[maxn];
void dij() {
  priority_queue<PII> pq;
  for (int i = 1; i <= n; i++) {
    dis[i] = inf;
    vis[i] = false;
  }
  dis[1] = 0;
  pq.emplace(0, 1);
  while (!pq.empty()) {
    int u = pq.top().second;
    pq.pop();
    if (vis[u]) continue;
    vis[u] = true;
    for (auto e: G[u]) {
      int v = e.to, w = e.w;
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        pq.emplace(-dis[v], v);
      }
    }
  }
}

int ch[maxn][2], pre[maxn], mnH[maxn];
int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}
bool join(int x, int y) {
  x = find(x);
  y = find(y);
  if (x == y) return false;
  pre[x] = y;
  return true;
}

int fa[20][maxn];
void dfs(int u) {
  for (int j = 1; j < 20; j++) {
    fa[j][u] = fa[j - 1][fa[j - 1][u]];
  }
  if (u > n) {
    fa[0][ch[u][0]] = u;
    fa[0][ch[u][1]] = u;
    dfs(ch[u][0]);
    dfs(ch[u][1]);
    dis[u] = min(dis[ch[u][0]], dis[ch[u][1]]);
  }
}
int query(int u, int H) {
  for (int j = 19; j >= 0; j--) {
    int f = fa[j][u];
    if (!f) continue;
    if (mnH[f] <= H) continue;
    u = f;
  }
  return dis[u];
}

int main() {
  #ifdef ONLINE_JUDGE
    freopen("return.in", "r", stdin);
    freopen("return.out", "w", stdout);
  #endif

  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      pre[i] = i;
      mnH[i] = inf;
      G[i].clear();
    }
    for (int i = 1; i <= m; i++) {
      int u, v, l, a;
      scanf("%d%d%d%d", &u, &v, &l, &a);
      eg[i] = Edge { u, v, l, a };
      G[u].push_back({ u, v, l, a });
      G[v].push_back({ v, u, l, a });
    }
    
    dij();
    sort(eg + 1, eg + 1 + m);
    int vsz = n;
    for (int i = 1; i <= m; i++) {
      int x = find(eg[i].from);
      int y = find(eg[i].to);
      if (x != y) {
        vsz++;
        pre[vsz] = vsz;
        join(x, vsz);
        join(y, vsz);
        ch[vsz][0] = x;
        ch[vsz][1] = y;
        mnH[vsz] = eg[i].h;
        mnH[vsz] = min(mnH[vsz], mnH[x]);
        mnH[vsz] = min(mnH[vsz], mnH[y]);
      }
    }
    for (int i = 1; i <= vsz; i++) {
      if (i == find(i)) {
        dfs(i);
        break;
      }
    }
    
    scanf("%d%d%d", &Q, &K, &S);
    int ans = 0;
    while (Q--) {
      int v, p;
      scanf("%d%d", &v, &p);
      v = (v + K * ans - 1) % n + 1;
      p = (p + K * ans) % (S + 1);
      printf("%d\n", ans = query(v, p));
    }
  }
  return 0;
}