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
const int maxn = 200000 + 5;

int n, m, q;

struct Edge { int to, nxt, d; } f[maxn * 2];
int head[maxn], ecnt, uu[maxn], vv[maxn], cc[maxn];
void adde(int x, int y, int d) {
  f[++ecnt] = { y, head[x], d };
  head[x] = ecnt;
}

bool vis[maxn];
ll disS[maxn], disT[maxn];
struct Node {
  int to; ll d;
  bool operator< (const Node& b)const{
    return d > b.d;
  }
};
void dijkstra(int s, ll dis[]) {
  for (int i = 0; i <= n; i++) {
    vis[i] = false; dis[i] = 1ll << 60;
  }
  ms(vis, 0); dis[s] = 0;
  priority_queue<Node> q;
  q.push((Node){s, 0});
  while (!q.empty()) {
    Node t = q.top(); q.pop();
    if (vis[t.to]) continue;
    vis[t.to] = 1;
    for (int i = head[t.to]; i; i = f[i].nxt) {
      int v = f[i].to;
      if (vis[v]) continue;
      if (dis[v] > dis[t.to] + f[i].d) {
        dis[v] = dis[t.to] + f[i].d;
        q.push({v, dis[v]});
      }
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1, u, v, c; i <= m; i++) {
    scanf("%d%d%d", &u, &v, &c);
    uu[i] = u; vv[i] = v; cc[i] = c;
    adde(u, v, c);
  }
  dijkstra(1, disS);
  ll mnd = disS[n];
  ms(head, 0); ecnt = 0;
  for (int i = 1; i <= m; i++) {
    adde(vv[i], uu[i], cc[i]);
  }
  dijkstra(n, disT);
  scanf("%d", &q);
  while (q--) {
    int i; scanf("%d", &i);
    if (disS[vv[i]] + cc[i] + disT[uu[i]] < mnd) {
      puts("YES");
    } else {
      puts("NO");
    }
  }
  return 0;
}