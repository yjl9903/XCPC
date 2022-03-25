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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 2000 + 5;

struct MCMF {
  struct edge {
    int to, flow, cost, rev;
    edge() {}
    edge(int to, int f, int cost, int r): to(to), flow(f), cost(cost), rev(r) {}
  };
  static const int maxm = 5000 + 5;
  int V, H[maxm + 5], dis[maxm + 5], preV[maxm + 5], preE[maxm + 5];
  vector<edge> G[maxm + 5];
  void init(int n) {
    V = n;
    for (int i = 0; i <= V; ++i) G[i].clear();
  }
  void add(int from, int to, int cap, int cost) {
    G[from].push_back(edge(to, cap, cost, (int)G[to].size()));
    G[to].push_back(edge(from, 0, -cost, (int)G[from].size() - 1));
  }
  int getmin(int s, int t, int f, int& flow) {
    int ans = 0;
    fill(H, H + 1 + V, 0);
    while (f) {
      priority_queue<PII,vector<PII>,greater<PII> > q;
      fill(dis, dis + 1 + V, inf);
      dis[s] = 0; q.push({0, s});
      while (!q.empty()) {
        PII now = q.top(); q.pop();
        int v = now.second;
        if (dis[v] < now.first) continue;
        for (int i = 0; i < G[v].size(); ++i) {
          edge& e = G[v][i];
          if (e.flow > 0 && dis[e.to] > dis[v] + e.cost + H[v] - H[e.to]) {
            dis[e.to] = dis[v] + e.cost + H[v] - H[e.to];
            preV[e.to] = v;
            preE[e.to] = i;
            q.push({dis[e.to], e.to});
          }
        }
      }
      if (dis[t] == inf) break;
      for (int i = 0; i <= V; ++i) H[i] += dis[i];
      int d = f;
      for (int v = t; v != s; v = preV[v]) d = min(d, G[preV[v]][preE[v]].flow);
      f -= d; flow += d; ans += d * H[t];
      for (int v = t; v != s; v = preV[v]) {
        edge& e = G[preV[v]][preE[v]];
        e.flow -= d;
        G[v][e.rev].flow += d;
      }
    }
    return ans;
  }
} mcf;

int n, a, b, la[maxn], lb[maxn];
vector<int> ega[maxn], egb[maxn];
vector<int> baga[maxn], bagb[maxn];

void adfs(int u) {
  if (la[u]) {
    assert(ega[u].empty());
    baga[u].push_back(la[u]);
    return ;
  }
  for (int v: ega[u]) {
    adfs(v);
    for (auto& x: baga[v]) baga[u].push_back(x);
  }
}
void bdfs(int u) {
  if (lb[u]) {
    assert(egb[u].empty());
    bagb[u].push_back(lb[u]);
    return ;
  }
  for (int v: egb[u]) {
    bdfs(v);
    for (auto& x: bagb[v]) bagb[u].push_back(x);
  }
}

int main() {
  scanf("%d%d", &n, &a);
  for (int i = 2, x; i <= a; i++) {
    scanf("%d", &x);
    ega[x].push_back(i);
  }
  for (int i = 1, x; i <= n; i++) {
    scanf("%d", &x);
    la[x] = i;
  }
  scanf("%d", &b);
  for (int i = 2, x; i <= b; i++) {
    scanf("%d", &x);
    egb[x].push_back(i);
  }
  for (int i = 1, x; i <= n; i++) {
    scanf("%d", &x);
    lb[x] = i;
  }
  adfs(1); bdfs(1);
  // 1 ~ a, a + 1 ~ a + b, a + b + 1 ~ a + b + n, a + b + n + 1, a + b + n + 2
  mcf.init(a + b + n + 2);
  int S = a + b + n + 1, T = a + b + n + 2;

  return 0;
}