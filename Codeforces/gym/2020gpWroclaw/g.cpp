#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int, int>;
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 400000 + 5;

inline int add(int x, int y) {
  x += y;
  return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
  x -= y;
  return x < 0 ? x += mod : x;
}
inline int mul(int x, int y) {
  return 1ll * x * y % mod;
}
inline int qpow(int x, ll n) {
  int r = 1;
  while (n > 0) {
    if (n & 1) r = 1ll * r * x % mod;
    n >>= 1; x = 1ll * x * x % mod;
  }
  return r;
}
inline int inv(int x) {
  return qpow(x, mod - 2);
}

int n, m, k, cnt;
vector<int> edge[maxn * 2], bcc[maxn];

namespace cactus {
  struct E {
    int to, nxt;
  } e[maxn * 2];
  int head[maxn], ecnt;
  void adde(int u, int v) {
    e[++ecnt] = {v, head[u]};
    head[u] = ecnt;
  }
  int tot, dfn[maxn], fa[maxn];
  bool ring[maxn];
  void clear(int n) {
    cnt = ecnt = tot = 0;
    for (int i = 1; i <= n; i++) {
      head[i] = dfn[i] = 0;
    }
    for (int i = 1; i <= n + n; i++) {
      edge[i].clear();
    }
  }
  void dfs(int u, int f) {
    dfn[u] = ++tot;
    for (int i = head[u]; i; i = e[i].nxt) {
      int v = e[i].to;
      if (v == f) continue;
      if (!dfn[v]) {
        fa[v] = u;
        ring[u] = false;
        dfs(v, u);
        if (!ring[u]) {
          edge[u].push_back(v);
          edge[v].push_back(u);
        }
      } else if (dfn[v] < dfn[u]) {
        cnt++;
        int rt = cnt + n;
        bcc[cnt].clear();
        edge[rt].push_back(v);
        edge[v].push_back(rt);
        bcc[cnt].push_back(v);
        for (int x = u; x != v; x = fa[x]) {
          ring[x] = true;
          bcc[cnt].push_back(x);
          edge[rt].push_back(x);
          edge[x].push_back(rt);
        }
        ring[v] = true;
      }
    }
  }
  void build() { dfs(1, 0); }
}  // namespace cactus

int calL(int n) {
  return mul(k, qpow(k - 1, n - 1));
}

int calR(int n) {
  int ans = qpow(k - 1, n);
  if (n % 2 == 0) {
    ans = add(ans, k - 1);
  } else {
    ans = sub(ans, k - 1);
  }
  return ans;
}

int ans = 1;
void dfs(int u, int f) {
  if (u > n) {
    int sz = bcc[u - n].size();
    bool find = false;
    for (int x: bcc[u - n]) {
      if (x == 1) {
        find = true;
        break;
      }
    }
    int cur = 1;
    if (!find) {
      // cur = sub(cur, 2);
      cur = 0;
      for (int i = sz, f = 1; i >= 2; i--, f ^= 1) {
        if (f) {
          cur = add(cur, qpow(k - 1, i));
        } else {
          cur = sub(cur, qpow(k - 1, i));
        }
      }
      cur = mul(cur, inv(k - 1));
    } else {
      cur = mul(calR(sz), inv(k));
    }
    ans = mul(ans, cur);
    dbg(u, cur);
  } else {
    if (u == 1) ans = mul(ans, k);
    else if (f <= n) ans = mul(ans, k - 1);
  }
  dbg(u, f);
  for (int v: edge[u]) {
    if (v == f) continue;
    dfs(v, u);
  }
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &n, &m, &k);
    cactus::clear(n);
    for (int i = 1; i <= m; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      cactus::adde(u, v);
      cactus::adde(v, u);
    }
    cactus::build();
    ans = 1;
    dfs(1, 0);
    printf("%d\n", ans);
  }
  return 0;
}