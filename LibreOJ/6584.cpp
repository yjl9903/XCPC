#include <cstdio>
#include <cassert>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
const int maxn = 500000 + 5;

int n, k, fa[maxn], ans[maxn], dep[maxn];
vector<int> edge[maxn];

int pre[maxn];
int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}
bool join(int x, int y) {
  x = find(x); y = find(y);
  if (x == y) return false;
  pre[x] = y;
  return true;
}

int a[maxn];
void update(int i, int x) {
  for (; i < maxn; i += i & -i) a[i] += x;
}
int query(int i) {
  if (i > n) i = n;
  if (i <= 0) return 0;
  int r = 0;
  for (; i; i -= i & -i) r += a[i];
  return r;
}
int query(int l, int r) {
  if (l > r) return 0;
  return query(r) - query(l - 1);
}

vector<int> ri;
bool vis[maxn], ring[maxn];
void getring(int u) {
  vis[u] = true;
  for (int v: edge[u]) {
    if (vis[v]) {
      if (!ri.empty()) continue;
      int x = u;
      while (x != v) {
        ring[x] = true;
        ri.push_back(x);
        x = fa[x];
      }
      ring[v] = true;
      ri.push_back(v);
      continue;
    }
    dep[v] = dep[u] + 1;
    getring(v);
  }
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) pre[i] = i;
  vector<int> rts;
  for (int i = 1; i <= n; i++) {
    scanf("%d", fa + i);
    edge[fa[i]].push_back(i);
    if (!join(fa[i], i)) {
      rts.push_back(i);
    }
  }
  for (int rt: rts) {
    dep[rt] = 1; ri.clear();
    getring(rt);
    for (int x: ri) {
      ans[x] -= query(1, k - ((int)ri.size() - dep[x]));
    }
    function<void(int)> dfs = [&](int u) {
      if (ring[u]) {
        ans[u] -= query(max(dep[u], 1 + k - ((int)ri.size() - dep[u])), dep[u] + k);
      } else {
        ans[u] -= query(dep[u], dep[u] + k);
      }
      update(dep[u], 1);
      for (int v: edge[u]) {
        if (v == rt) continue;
        dfs(v);
      }
      if (ring[u]) {
        ans[u] += query(max(dep[u], 1 + k - ((int)ri.size() - dep[u])), dep[u] + k);
      } else {
        ans[u] += query(dep[u], dep[u] + k);
      }
    };
    dfs(rt);
    for (int x: ri) {
      ans[x] += query(1, k - ((int)ri.size() - dep[x]));
    }
  }
  for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
  return 0;
}