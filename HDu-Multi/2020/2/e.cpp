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
const int maxn = 100000 + 5;

vector<ll> costs;

int n, m;
int a[maxn], b[maxn];
ll c[maxn];

struct MCMF {
  struct E {
    int from, to, cap;
    ll v;
    E() {}
    E(int f, int t, int cap, ll v) : from(f), to(t), cap(cap), v(v) {}
  };

  int n, m, s, t;
  vector<E> edges;
  vector<int> G[maxn];
  bool inq[maxn];
  int pre[maxn], a[maxn];
  ll dis[maxn];

  void init(int _n, int _s, int _t) {
    n = _n; s = _s; t = _t;
    for (int i = 0; i <= n; i++) {
      G[i].clear();
    }
    edges.clear();
    m = 0;
  }

  void add(int from, int to, int cap, ll cost) {
    edges.emplace_back(from, to, cap, cost);
    edges.emplace_back(to, from, 0, -cost);
    G[from].push_back(m++);
    G[to].push_back(m++);
  }

  bool spfa() {
    for (int i = 0; i <= n; i++) {
      dis[i] = 1e18;
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

  ll solve() {
    costs.clear();
    int flow = 0;
    ll cost = 0;
    while (spfa()) {
      flow += a[t];
      cost += a[t] * dis[t];

      assert(a[t] == 1);
      costs.push_back(cost);

      int u = t;
      while (u != s) {
        edges[pre[u]].cap -= a[t];
        edges[pre[u] ^ 1].cap += a[t];
        u = edges[pre[u]].from;
      }
    }
    assert(flow == ::n);
    return cost;
  }
} f;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    vector<int> key;
    for (int i = 1; i <= n; i++) {
      key.push_back(i);
      key.push_back(m - i + 1);
    }
    for (int i = 1; i <= n; i++) {
      scanf("%d%d%lld", a + i, b + i, c + i);
      if (b[i] < 0) {
        int mid = -b[i] / (a[i] + a[i]);
        for (int j = mid; j <= mid + n + 2 && j <= m; j++) {
          if (j >= 1) {
            key.push_back(j);
          }
        }
        for (int j = mid - 1; j >= mid - n - 2 && j >= 1; j--) {
          if (j <= m) {
            key.push_back(j);
          }
        }
      }
    }
    sort(begin(key), end(key));
    key.resize(unique(begin(key), end(key)) - begin(key));
    // for (int x: key) {
    //   dbg(x);
    // }
    f.init(n + (int)key.size() + 2, 1, 2);
    for (int j = 0; j < (int)key.size(); j++) {
      f.add(3 + n + j, 2, 1, 0);
    }
    for (int i = 1; i <= n; i++) {
      f.add(1, i + 2, 1, 0);
      for (int j = 0; j < (int)key.size(); j++) {
        int x = key[j];
        ll val = (1ll * a[i] * x * x + 1ll * b[i] * x + c[i]);
        f.add(i + 2, 3 + n + j, 1, val);
      }
    }
    // printf("%lld\n", f.km(n, (int)key.size()));
    f.solve();
    // for (ll x: costs) {
    //   dbg(x);
    // }
    for (int i = 0; i < n; i++) {
      printf("%lld%c", costs[i], " \n"[i == n - 1]);
    }
  }
  return 0;
}