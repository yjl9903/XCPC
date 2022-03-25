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

const int maxn = 50 + 5;
const int maxm = 200 + 5;

int gi() {
  int n, c, sign = 0;
  while ((c = getchar()) < '-');
  if (c == '-') sign = 1, n = 0;
  else n = c - '0';
  while ((c = getchar()) >= '0') n = n * 10 + c - '0';
  return sign ? -n : n;
}

int head[maxn], tot = 1;
struct edge {
  int to, nxt, flow, cost;
} g[maxm];
void adde(int x, int y, int f, int c) {
  g[++tot] = edge { y, head[x], f, c };
  head[x] = tot;
  g[++tot] = edge { x, head[y], 0, -c };
  head[y] = tot;
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

int n, m, q;

vector<ll> costs;
void mcmf() {
  int s = 1, t = n;
  costs.clear();
  mc = mf = 0;
  while (spfa(s, t)) {
    int now = t;
    mf += flow[t]; mc += flow[t] * cost[t];
    
    dbg(flow[t], cost[t]);
    assert(flow[t] == 1);
    costs.push_back(cost[t]);
    
    while (now != s) {
      g[last[now]].flow -= flow[t];
      g[last[now] ^ 1].flow += flow[t];
      now = pre[now];
    }
  }
}

using Frac = pair<ll, ll>; // first / second
Frac make(ll fz, ll fm) {
  ll g = __gcd(fz, fm);
  return Frac { fz / g, fm / g };
}
Frac add(const Frac& a, const Frac& b) {
  ll fz = 1ll * a.first * b.second + 1ll * b.first * a.second;
  ll fm = 1ll * a.second * b.second;
  return make(fz, fm);
}
Frac sub(const Frac& a, const Frac& b) {
  ll fz = 1ll * a.first * b.second - 1ll * b.first * a.second;
  ll fm = 1ll * a.second * b.second;
  return make(fz, fm);
}
Frac mul(const Frac& a, ll k) {
  return make(a.first * k, a.second);
}

int main() {
  while (scanf("%d%d", &n, &m) == 2) {
    ms(head, 0); tot = 1;
    for (int i = 1, u, v, w; i <= m; i++) {
      // scanf("%d%d%d", &u, &v, &w);
      u = gi();
      v = gi();
      w = gi();
      adde(u, v, 1, w);
    }

    mcmf();

    vector<ll> pmx(costs.size());
    if (!costs.empty()) {
      pmx[0] = costs[0];
      for (int i = 1; i < (int)costs.size(); i++) {
        pmx[i] = max(pmx[i - 1], costs[i]);
        costs[i] += costs[i - 1];
      }
    }
    
    // scanf("%d", &q);
    q = gi();
    while (q--) {
      // int fz, fm; scanf("%d%d", &fz, &fm);
      int fz = gi();
      int fm = gi();

      if (costs.empty() || fz == 0) {
        puts("NaN");
        continue;
      }
      
      int need = fm / fz; if (fm % fz) need++;
      if (need > (int)costs.size()) {
        puts("NaN");
        continue;
      }

      Frac ans = mul(make(fz, fm), costs[need - 1]);
      if (need * fz > fm) {
        auto delta = make(need * fz - fm, fm);
        ans = sub(ans, mul(delta, pmx[need - 1]));
      }
      printf("%lld/%lld\n", ans.first, ans.second);

      // ll tot = 0;
      // int mx = 0;
      // Frac ans(0, 1), base = make(fz, fm);
      // for (int i = 0; i < (int)costs.size() && tot < fm; i++, tot += fz) {
      //   mx = max(mx, costs[i]);
      //   ans = add(ans, mul(base, costs[i]));
      // }
      // if (tot < fm) {
      //   puts("NaN");
      // } else {
      //   if (tot > fm) {
      //     auto delta = make(tot - fm, fm);
      //     ans = sub(ans, mul(delta, mx));
      //   }
      //   printf("%lld/%lld\n", ans.first, ans.second);
      // }
    }
  }
  return 0;
}