#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <map>
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
using ull = unsigned long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500 + 5;

int n, rta, rtb, fa[maxn], fb[maxn];
vector<int> g1[maxn], g2[maxn];

int tot;
map<vector<int>,int> mp;
int siz[maxn];
int hsh1[maxn], hsh2[maxn];
void predfs(int u, int ff, vector<int>* edge, int* hsh) {
  siz[u] = 1;
  vector<int> vec;
  for (int v: edge[u]) {
    if (v == ff) continue;
    predfs(v, u, edge, hsh);
    siz[u] += siz[v];
    vec.push_back(hsh[v]);
  }
  sort(begin(vec), end(vec));
  if (!mp.count(vec)) {
    mp[vec] = ++tot;
  }
  hsh[u] = mp[vec];
}

struct MCMF {
  struct E {
    int from, to, cap, v;
    E() {}
    E(int f, int t, int cap, int v) : from(f), to(t), cap(cap), v(v) {}
  };

  int n, m, s, t;
  vector<E> edges;
  vector<int> G[maxn];
  bool inq[maxn];
  int dis[maxn], pre[maxn], a[maxn];

  void init(int _n, int _s, int _t) {
    n = _n; s = _s; t = _t;
    for (int i = 0; i <= n; i++) {
      G[i].clear();
    }
    edges.clear();
    m = 0;
  }

  void add(int from, int to, int cap, int cost) {
    edges.emplace_back(from, to, cap, cost);
    edges.emplace_back(to, from, 0, -cost);
    G[from].push_back(m++);
    G[to].push_back(m++);
  }

  bool spfa() {
    for (int i = 0; i <= n; i++) {
      dis[i] = 1e9;
      pre[i] = -1;
      inq[i] = false;
    }
    dis[s] = 0, a[s] = 1e9, inq[s] = true;
    queue<int> Q; Q.push(s);
    while (!Q.empty()) {
      int u = Q.front(); Q.pop();
      inq[u] = false;
      for (int& idx: G[u]) {
        E& e = edges[idx];
        if (e.cap && dis[e.to] > dis[u] + e.v) {
          dis[e.to] = dis[u] + e.v;
          pre[e.to] = idx;
          a[e.to] = min(a[u], e.cap);
          if (!inq[e.to]) {
            inq[e.to] = true;
            Q.push(e.to);
          }
        }
      }
    }
    return pre[t] != -1;
  }

  PII solve() {
    int flow = 0, cost = 0;
    while (spfa()) {
      flow += a[t];
      cost += a[t] * dis[t];

      int u = t;
      while (u != s) {
        edges[pre[u]].cap -= a[t];
        edges[pre[u] ^ 1].cap += a[t];
        u = edges[pre[u]].from;
      }
    }
    return make_pair(cost, flow);
  }
} f;

int mem[maxn][maxn];
int solve(int ua, int ub) {
  if (g1[ua].empty()) {
    return ua != ub;
  }
  if (mem[ua][ub] != -1) {
    return mem[ua][ub];
  }
  assert(g1[ua].size() == g2[ub].size());
  int n = g1[ua].size(), sz = siz[ub];
  vector<vector<int> > C(n, vector<int>(n, -1));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int va = g1[ua][i], vb = g2[ub][j];
      if (hsh1[va] == hsh2[vb]) {
        C[i][j] = solve(va, vb);
      }
    }
  }
  f.init(n + n + 2, n + n + 1, n + n + 2);
  for (int i = 0; i < n; i++) {
    f.add(n + n + 1, i + 1, 1, 0);
    f.add(n + i + 1, n + n + 2, 1, 0);
    for (int j = 0; j < n; j++) {
      if (C[i][j] != -1) {
        f.add(i + 1, n + j + 1, 1, C[i][j]);
      }
    }
  }
  auto res = f.solve();
  assert(res.second == n);
  return mem[ua][ub] = res.first + (ua != ub);
}

int main() {
  scanf("%d", &n);
  ms(mem, -1);
  for (int i = 1; i <= n; i++) {
    scanf("%d", fa + i);
    if (fa[i]) {
      g1[fa[i]].push_back(i);
    } else {
      rta = i;
    }
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", fb + i);
    if (fb[i]) {
      g2[fb[i]].push_back(i);
    } else {
      rtb = i;
    }
  }
  predfs(rta, 0, g1, hsh1);
  predfs(rtb, 0, g2, hsh2);
  assert(hsh1[rta] == hsh2[rtb]);
  printf("%d\n", solve(rta, rtb));
  return 0;
}