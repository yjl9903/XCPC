#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int, int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

struct Dinic {
  struct Edge {
    int from, to;
    ll cap, flow;
    Edge(int u, int v, ll c, ll f) : from(u), to(v), cap(c), flow(f) {}
  };

  int n, m, s, t;
  vector<Edge> edges;
  vector<int> G[maxn];
  bool vis[maxn];
  int dep[maxn], cur[maxn];
  void init(int _n) {
    n = _n;
    for (int i = 0; i <= n; i++) G[i].clear();
    edges.clear();
  }
  void adde(int from, int to, ll cap) {
    edges.emplace_back(from, to, cap, 0);
    edges.emplace_back(to, from, 0, 0);
    m = edges.size();
    G[from].push_back(m - 2);
    G[to].push_back(m - 1);
  }
  bool bfs() {
    ms(vis, 0);
    ms(dep, 0);
    queue<int> q;
    q.push(s);
    dep[s] = 0;
    vis[s] = 1;
    while (!q.empty()) {
      int x = q.front();
      q.pop();
      for (int i = 0; i < G[x].size(); i++) {
        Edge& e = edges[G[x][i]];
        if (!vis[e.to] && e.cap > e.flow) {
          vis[e.to] = 1;
          dep[e.to] = dep[x] + 1;
          q.push(e.to);
        }
      }
    }
    return vis[t];
  }
  ll dfs(int x, ll a) {
    if (x == t || a == 0) return a;
    ll flow = 0, f;
    for (int& i = cur[x]; i < G[x].size(); i++) {
      //从上次考虑的弧
      Edge& e = edges[G[x][i]];
      if (dep[x] + 1 == dep[e.to] &&
          (f = dfs(e.to, min(a, e.cap - e.flow))) > 0) {
        e.flow += f;
        edges[G[x][i] ^ 1].flow -= f;
        flow += f;
        a -= f;
        if (a == 0) break;
      }
    }
    return flow;
  }
  ll get(int s, int t) {
    this->s = s, this->t = t;
    ll flow = 0;
    while (bfs()) {
      ms(cur, 0);
      flow += dfs(s, inf);
    }
    return flow;
  }
} f;

int n, m, p, vis[maxn];

int main() {
  scanf("%d%d%d", &n, &m, &p);
  int S = n + m + p + 1, T = n + m + p + 2;
  for (int i = 1; i <= n; i++) {
    f.adde(S, i, 1);
    int k;
    scanf("%d", &k);
    while (k--) {
      int x;
      scanf("%d", &x);
      f.adde(i, n + x, 1);
    }
  }
  for (int i = 1; i <= p; i++) {
    int cur = n + m + i, k;
    scanf("%d", &k);
    while (k--) {
      int x;
      scanf("%d", &x);
      vis[x] = 1;
      f.adde(n + x, cur, 1);
    }
    scanf("%d", &k);
    f.adde(cur, T, k);
  }
  for (int i = 1; i <= m; i++) {
    if (vis[i]) continue;
    f.adde(n + i, T, 1);
  }
  printf("%lld\n", f.get(S, T));
  return 0;
}