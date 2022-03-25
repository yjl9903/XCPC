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
#include <queue>
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const ll inf = 1ll << 60;
const int maxn = 200000 + 5;
const int L = 20;

int n, m, q;
bool vis[maxn];
ll dep[maxn][L], dis[maxn];
vector<PII> anc[maxn], edge[maxn];

int len(int x) {
  return 31 - __builtin_clz(x);
}

void dij(int rt) {
  dis[rt] = 0;
  vis[rt] = false;
  priority_queue< pair<ll, int> > pq;
  pq.emplace(0, rt);
  while (!pq.empty()) {
    auto x = pq.top();
    int u = x.second;
    pq.pop();
    if (vis[u]) continue;
    vis[u] = true;
    for (auto& x: edge[u]) {
      int v = x.first;
      int w = x.second;
      if (dis[v] > dis[u] + w) {
        dis[v] = dis[u] + w;
        pq.emplace(-dis[v], v);
      }
    }
  }
}

void iterate(function<void(int)> f, int u) {
  if (u > n) return ;
  f(u);
  iterate(f, u * 2);
  iterate(f, u * 2 + 1);
}

void dfs(int u) {
  if (u > n) return ;
  for (auto& x: anc[u]) {
    edge[u].emplace_back(x);
    edge[x.first].emplace_back(u, x.second);
  }
  int rt = u;
  auto add = [&](int u) {
    vis[u] = false;
    dis[u] = inf;
    for (auto& x: anc[u]) {
      edge[u].emplace_back(x);
      edge[x.first].emplace_back(u, x.second);
    }
  };
  auto del = [&](int u) {
    dep[u][len(rt)] = min(dep[u][len(rt)], dis[u]);
    for (auto& x: anc[u]) {
      edge[u].pop_back();
      edge[x.first].pop_back();
    }
  };
  dfs(u * 2);
  dfs(u * 2 + 1);
  iterate(add, u * 2);
  iterate(add, u * 2 + 1);
  for (int x = u; x >= 1; x /= 2) {
    vis[x] = false;
    dis[x] = inf;
  }
  dij(u);
  for (int x = u; x >= 1; x /= 2) {
    dep[u][len(x)] = min(dep[u][len(x)], dis[x]);
  }
  iterate(del, u * 2);
  iterate(del, u * 2 + 1);
  for (auto& x: anc[u]) {
    edge[u].pop_back();
    edge[x.first].pop_back();
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < L; j++) {
      dep[i][j] = inf;
    }
  }
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    assert(v >> (len(v) - len(u)) == u);
    anc[v].emplace_back(u, w);
  }
  dfs(1);
  scanf("%d", &q);
  while (q--) {
    int u, v;
    scanf("%d%d", &u, &v);
    ll ans = inf;
    int x = u, y = v;
    while (u >= 1 && v >= 1) {
      if (u == v) {
        int d = len(u);
        ans = min(ans, dep[x][d] + dep[y][d]);
        u /= 2;
        v /= 2;
      } else {
        if (u < v) swap(u, v);
        u /= 2;
      }
    }
    if (ans == inf) {
      puts("-1");
    } else {
      printf("%lld\n", ans);
    }
  }
  return 0;
}