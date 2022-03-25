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
const int maxn = 10000 + 5;

int n, m, a, b, mK;
vector<PII> G[maxn], rG[maxn];

struct Node {
  int u, d, k;

  Node(int a = 0, int b = 0, int c = 0): u(a), d(b), k(c) {}

  bool operator< (const Node& b) const {
    return d > b.d;
  }
};

bool vis[maxn][12];
int aD[maxn], bD[maxn];
int dis1[maxn][12], dis2[maxn][12];
int dis3[maxn][12], dis4[maxn][12];

void dij(int a, int dis[][12], vector<PII> edge[]) {
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= mK; j++) {
      dis[i][j] = inf;
      vis[i][j] = false;
    }
  }
  priority_queue<Node> pq;
  pq.emplace(a, 0, 0);
  dis[a][0] = 0;
  while (!pq.empty()) {
    Node x = pq.top(); pq.pop();
    int u = x.u, k = x.k;
    if (vis[u][k]) continue;
    vis[u][k] = true;
    for (PII e: edge[u]) {
      int v = e.first;
      int w = e.second;
      if (dis[u][k] + w < dis[v][k]) {
        dis[v][k] = dis[u][k] + w;
        pq.emplace(v, dis[v][k], k);
      }
      if (k + 1 <= mK && dis[u][k] < dis[v][k + 1]) {
        dis[v][k + 1] = dis[u][k];
        pq.emplace(v, dis[v][k + 1], k + 1);
      }
    }
  }
}

int main() {
  scanf("%d%d%d%d%d", &n, &m, &a, &b, &mK);
  a++; b++;
  for (int i = 1, u, v, w; i <= m; i++) {
    scanf("%d%d%d", &u, &v, &w);
    u++; v++;
    G[u].emplace_back(v, w);
    rG[v].emplace_back(u, w);
  }

  dij(a, dis1, G);
  dij(a, dis2, rG);
  dij(b, dis3, G);
  dij(b, dis4, rG);


  for (int i = 1; i <= n; i++) {
    aD[i] = bD[i] = inf;
    for (int j = 0; j <= mK; j++) {
      for (int k = 0; j + k <= mK; k++) {
        if (dis1[i][j] < inf && dis2[i][k] < inf) {
          aD[i] = min(aD[i], dis1[i][j] + dis2[i][k]);
        }
        if (dis3[i][j] < inf && dis4[i][k] < inf) {
          bD[i] = min(bD[i], dis3[i][j] + dis4[i][k]);
        }
      }
    }
    dbg(i, aD[i], bD[i]);
  }

  int ans = inf, pos = inf;
  for (int i = 1; i <= n; i++) {
    if (i == a || i == b) continue;
    int x = aD[i], y = bD[i];
    dbg(i, x, y);
    if (x == inf || y == inf) continue;
    if (ans > x + y) {
      ans = x + y;
      pos = i;
    }
  }
  
  if (ans == inf) {
    puts(">:(");
  } else {
    printf("%d %d\n", pos - 1, ans);
  }
  return 0;
}