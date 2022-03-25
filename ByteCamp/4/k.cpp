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
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;

const int maxn = 5000 + 5;
const int maxm = 100000 + 5;

int head[maxn], tot = 1;
struct edge{
  int to, nxt, flow, cost;
}g[maxm];
void add(int x, int y, int f, int c) {
  g[++tot] = edge{y, head[x], f, c};
  head[x] = tot;
  g[++tot] = edge{x, head[y], 0, -c};
  head[y] = tot;
}
void init() {
  ms(head, 0); tot = 1;
}

int vis[maxn], cost[maxn], pre[maxn], flow[maxn], last[maxn], mf, mc;
bool spfa(int s, int t) {
  ms(cost, 0x7f); ms(flow, 0x7f); ms(vis, 0);
  queue<int> q; q.push(s); vis[s] = 1; cost[s] = 0; pre[t] = -1;
  while (!q.empty()) {
    int now = q.front(); q.pop(); vis[now] = 0;
    for (int i = head[now]; i; i = g[i].nxt) {
      int v = g[i].to;
      if (g[i].flow > 0 && cost[v] > cost[now] + g[i].cost) {
        cost[v] = cost[now] + g[i].cost;
        pre[v] = now; last[v] = i;
        flow[v] = min(flow[now], g[i].flow);
        if (!vis[v]) {
          vis[v] = 1; q.push(v);
        }
      }
    }
  }
  return pre[t] != -1;
}

int s, t;
void mcmf() {
  mc = mf = 0;
  while (spfa(s, t)) {
    int now = t;
    mf += flow[t]; mc += flow[t] * cost[t];
    while (now != s) {
      g[last[now]].flow -= flow[t];
      g[last[now] ^ 1].flow += flow[t];
      now = pre[now];
    }
  }
}

int main() {
  init();
  int n, m; scanf("%d%d", &n, &m);
  int S = 1; T = m + 2 + n + n;
  s = m + 3 + n + n; t = m + 4 + n + n;

  auto add = [&](int u, int f1, int f2, int c) {

  };

  for (int i = 1; i <= n; i++) {
    add(m + 1 + i, t, 1, m, 0);
    add(m + 1 + i + n, t, 1, m, 0);
  }
  for (int i = 1; i <= m; i++) {
    int u, v, w; scanf("%d%d%d", &u, &v, &w);
    add(1, m + 1 + u, 0, 1, w + w);
    add(1, m + 1 + v + n, 0, 1, w + w);

    add(1, i + 1, 1, 0);
    add(i + 1, m + 1 + u, 1, w + w);
    add(i + 1, m + 1 + v + n, 1, w + w);
  }

  mcmf();
  if (mf == n + n) {
    printf("%d\n", mc);
  } else {
    puts("NIE");
  }
  return 0;
}