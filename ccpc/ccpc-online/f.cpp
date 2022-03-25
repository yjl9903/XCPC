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
const int maxn = 500 + 5;

int n, ans[maxn], vis[maxn];

struct Edge {
  int k, b, to; ll lim;
  Edge(int kk = 0, int bb = 0, int t = -1, ll l = inf) {
    k = kk;
    b = bb;
    to = t;
    lim = l;
  }
};

struct Fn {
  ll k, b;
  ll L, R;

  ll eval(ll x) {
    return k * x + b;
  }
};

vector<Edge> edge[maxn];
vector<Fn> fns[maxn];

void dfs(int u) {
  if (vis[u]) return ;
  vis[u] = true;
  if (u == n) {
    fns[u].push_back(Fn { 1, 0, -inf, inf });
    return ;
  }

  for (int i = 0; i < edge[u].size(); i++) {
    int to = edge[u][i].to;
    ll L = i == 0 ? -inf : edge[u][i - 1].lim;
    ll R = edge[u][i].lim;
    int k = edge[u][i].k;
    int b = edge[u][i].b;

    dfs(to);
    
    if (k == 0) {
      for (int i = 0; i < fns[to].size(); i++) {
        if (fns[to][i].L <= b && b <= fns[to][i].R) {
          ll tB = 1ll * fns[to][i].k * b + fns[to][i].b;
          fns[u].push_back(Fn { 0, tB, L, R });
        }
      }
    } else {
      ll tot = L, fL = 1ll * k * L + b, fR = 1ll * k * R + b;
      for (int i = 0; i < fns[to].size(); i++) {
        if (fL >= fns[to][i].L) {
          ll tK = 1ll * k * fns[to][i].k;
          ll tB = 1ll * fns[to][i].k * b + fns[to][i].b;
          if (fns[to][i].R <= fR) {
            ll tR = (fns[to][i].R - b) / k;
            fns[u].push_back(Fn { tK, tB, L, tR });
            L = tR;
            fL = k * L + b;
          } else {
            fns[u].push_back(Fn { tK, tB, L, R });
          }
        }
      }
    }
  }

  for (int i = 0; i + 1 < fns[u].size(); i++) {
    ll pos = fns[u][i].R;
    ll v1 = fns[u][i].eval(pos);
    ll v2 = fns[u][i + 1].eval(pos);
    if (v1 != v2) {
      ans[u] = false;
    }
  }
}

int main() {
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      ans[i] = true;
      vis[i] = false;
      edge[i].clear();
      fns[i].clear();
    }
    for (int i = 1; i < n; i++) {
      int k;
      scanf("%d", &k);
      for (int j = 0; j <= k; j++) {
        int c, b, d, a;
        scanf("%d%d%d", &c, &b, &d);
        if (j < k) {
          scanf("%d", &a);
          edge[i].emplace_back(c, b, d, a);
        } else {
          edge[i].emplace_back(c, b, d);
        }
      }
    }
    for (int i = 1; i < n; i++) {
      if (vis[i]) continue;
      dfs(i);
    }
    bool flag = true;
    for (int i = 1; i < n; i++) flag &= ans[i];
    printf("Case #%d: ", ++kase);
    puts(flag ? "YES" : "NO");
  }
  return 0;
}