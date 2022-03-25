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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 5000 + 5;

int n, m, col[maxn], id[maxn], ans[maxn];
vector<PII> edge[maxn];

int fa[maxn], dep[maxn];
void dfs(int u, int f) {
  dep[u] = dep[f] + 1; fa[u] = f;
  for (auto& x: edge[u]) {
    int v = x.first;
    if (v == f) continue;
    id[v] = x.second;
    dfs(v, u);
  }
}

void work(int w, int u, int v) {
  while (u != v) {
    if (dep[u] < dep[v]) swap(u, v);
    col[u] = w;
    u = fa[u];
  }
}
int query(int u, int v) {
  int mn = 1e9;
  while (u != v) {
    if (dep[u] < dep[v]) swap(u, v);
    mn = min(mn, col[u]);
    u = fa[u];
  }
  return mn;
}

int main() {
  scanf("%d", &n);
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].emplace_back(v, i);
    edge[v].emplace_back(u, i);
  }
  dfs(1, 0);
  vector< tuple<int,int,int> > path;
  scanf("%d", &m);
  for (int i = 1, u, v, w; i <= m; i++) {
    scanf("%d%d%d", &u, &v, &w);
    path.emplace_back(w, u, v);
  }
  sort(begin(path), end(path));
  for (auto& p: path) {
    int w, u, v; tie(w, u, v) = p;
    work(w, u, v);
  }
  for (auto& p: path) {
    int w, u, v; tie(w, u, v) = p;
    if (query(u, v) != w) {
      puts("-1"); return 0;
    }
  }
  for (int i = 2; i <= n; i++) {
    if (col[i]) {
      ans[id[i]] = col[i];
    } else {
      ans[id[i]] = 1e6;
    }
  }
  for (int i = 2; i <= n; i++) {
    printf("%d ", ans[i]);
  }
  return 0;
}