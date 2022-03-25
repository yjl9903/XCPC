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
const int maxn = 300000 + 5;

int n, m, k;
vector<PII> edge[maxn];
int pre[maxn], vis[maxn];
ll a[maxn];

int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}

struct Node {
  ll val;
  int u, id;

  bool operator < (const Node& b) const {
    return val < b.val;
  }
};
priority_queue<Node> pq[maxn];

void dfs(int u) {
  vis[u] = true;
  for (auto& x: edge[u]) {
    int v = x.first;
    int id = x.second;
    if (vis[v]) continue;
    dfs(v);
    pq[u].push({ a[v], v, id });
  }
  while (!pq[u].empty() && a[find(u)] + a[find(pq[u].top().u)] >= k) {
    auto tp = pq[u].top();
    int v = tp.u;
    pq[u].pop();
    if (find(u) == find(v)) continue;

    printf("%d\n", tp.id);
    a[find(u)] += a[find(v)] - k;
    pre[find(v)] = find(u);

    if (pq[v].size() > pq[u].size()) pq[v].swap(pq[u]);
    while (!pq[v].empty()) {
      auto x = pq[v].top();
      pq[v].pop();
      pq[u].push(x);
    }
  }
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  ll sum = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%lld", a + i);
    sum += a[i];
  }
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    edge[u].emplace_back(v, i);
    edge[v].emplace_back(u, i);
  }
  if (sum < 1ll * (n - 1) * k) {
    puts("NO");
  } else {
    for (int i = 1; i <= n; i++) {
      pre[i] = i;
    }
    puts("YES");
    dfs(1);
  }
  return 0;
}