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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const ll inf = 1ll << 60;
const int maxn = 200000 + 5;

int n, m;

struct edge { int to, nxt, d; } f[maxn * 2];
int head[maxn], tot;
void adde(int x, int y, int d) {
  f[++tot] = {y, head[x], d};
  head[x] = tot;
}

bool vis[maxn];
ll dis[maxn];
struct node {
  ll to, d;
  bool operator< (const node& b) const {
    if (d == b.d) {
      return to > b.to;
    }
    return d < b.d;
  }
};

ll dijkstra() {
  for (int i = 0; i <= n; i++) dis[i] = 1ll << 60;
  ms(vis, 0); dis[1] = 0;
  priority_queue<node> q;
  q.push({ 1, 0 });
  while (!q.empty()) {
    node t = q.top(); q.pop();
    if (vis[t.to]) continue;
    vis[t.to] = 1;
    for (int i = head[t.to]; i; i = f[i].nxt) {
      int v = f[i].to;
      // if (vis[v]) continue;
      if (dis[v] > dis[t.to] + f[i].d) {
        dis[v] = dis[t.to] + f[i].d;
        q.push({v, dis[v]});
      }
    }
  }
  return dis[n];
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    adde(u, v, w);
    adde(v, u, w);
  }
  ll ans = dijkstra();
  if (ans == inf) {
    puts("-1");
  } else {
    printf("%I64d\n", ans);
  }
  return 0;
}