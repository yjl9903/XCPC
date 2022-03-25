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
const ll inf = 1ll << 60;
const int maxn = 450 + 5;

struct EInfo {
  int nxt, val, col;
};

int n, m, k1, k2, S, T;
// bool vis[405][805][maxn];
// ll dis[405][805][maxn];
vector< vector< vector<bool> > > vis;
vector< vector< vector<ll> > > dis;
vector<EInfo> edge[maxn];

struct Node {
  int a, b, u; ll d;
  bool operator< (const Node& b) const {
    return d > b.d;
  }
};

int main() {
  scanf("%d%d%d%d", &n, &m, &k1, &k2);
  bool flag = false;
  if (k1 > k2) swap(k1, k2), flag = true;
  for (int i = 1; i <= m; i++) {
    int u, v, w, c;
    scanf("%d%d%d%d", &u, &v, &w, &c);
    if (flag && c) {
      if (c == 1) c = 2;
      else if (c == 2) c = 1;
    }
    edge[u].push_back({ v, w, c });
    edge[v].push_back({ u, w, c });
  }
  scanf("%d%d", &S, &T);
  vis = vector< vector< vector<bool> > >(k1 + 1, vector< vector<bool> >(k2 + 1, vector<bool>(n + 1, false)));
  dis = vector< vector< vector<ll> > >(k1 + 1, vector< vector<ll> >(k2 + 1, vector<ll>(n + 1, inf)));
  // for (int i = 0; i <= k1; i++) {
  //   for (int j = 0; j <= k2; j++) {
  //     for (int k = 1; k <= n; k++) {
  //       dis[i][j][k] = inf;
  //     }
  //   }
  // }
  priority_queue<Node> pq;
  pq.push({ 0, 0, S, 0 });
  dis[0][0][S] = 0;
  while (!pq.empty()) {
    auto u = pq.top(); pq.pop();
    if (vis[u.a][u.b][u.u]) continue;
    vis[u.a][u.b][u.u] = true;
    for (auto& E: edge[u.u]) {
      int na = u.a, nb = u.b;
      if (E.col == 1) {
        na++;
      } else if (E.col == 2) {
        nb++;
      }
      if (na > k1) continue;
      if (nb > k2) continue;
      Node nx = Node { na, nb, E.nxt, dis[u.a][u.b][u.u] + E.val };
      if (nx.d < dis[nx.a][nx.b][nx.u]) {
        dis[nx.a][nx.b][nx.u] = nx.d;
        pq.push(nx);
      }
    }
  }
  // for (int i = 0; i <= k1 * k2 + k1; i++) {
  //   for (int j = 1; j <= n; j++) {
  //     dbg(i, j, dis[i][j]);
  //   }
  // }
  if (dis[k1][k2][T] == inf) {
    puts("-1");
  } else {
    printf("%lld\n", dis[k1][k2][T]);
  }
  return 0;
}