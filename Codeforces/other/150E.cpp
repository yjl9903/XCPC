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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

struct fastIO {
  static const int SIZE = 1 << 20;
  char s[SIZE]; int it, len;
  fastIO() { it = len = 0; }
  inline char get() {
    if (it < len) return s[it++];
    it = 0; len = fread(s, 1, SIZE, stdin);
    if (len == 0) return EOF;
    else return s[it++];
  }
  inline bool notend() {
    char c = get();
    while (c == ' ' || c == '\n') c = get();
    if (it > 0) it--;
    return c != EOF;
  }
} buff;
inline int gi() {
  int r = 0; bool ng = 0;
  char c = buff.get();
  while (c != '-' && (c < '0' || c > '9')) c = buff.get();
  if (c == '-') ng = 1, c = buff.get();
  while (c >= '0' && c <= '9') r = r * 10 + c - '0', c = buff.get();
  return ng ? -r : r;
}

int n, L, R, B, ans = -1, ansU, ansV, dq[maxn];
vector<PII> edge[maxn];

int vis[maxn], siz[maxn], sum, mn, rt;
void getrt(int u, int f) {
  siz[u] = 1; int t = 0;
  for (auto& x: edge[u]) {
    int v = x.first;
    if (v == f || vis[v]) continue;
    getrt(v, u); siz[u] += siz[v];
    t = max(t, siz[v]);
  }
  t = max(t, sum - siz[u]);
  if (t < mn) mn = t, rt = u;
}
int getrt(int u) {
  sum = siz[u]; mn = 1e9; rt = 0;
  getrt(u, 0); return rt;
}

int f[maxn], fp[maxn], g[maxn], gp[maxn];
void solve(int u) {
  vis[u] = 1;
  vector<tuple<int,int,int> > vec;
  int mxd = 1;
  function<void(int,int,int)> predfs = [&](int u, int f, int d) {
    mxd = max(mxd, d);
    for (auto& x: edge[u]) {
      int v = x.first;
      if (v == f || vis[v]) continue;
      predfs(v, u, d + 1);
    }
  };
  for (auto& x: edge[u]) {
    int v = x.first;
    if (vis[v]) continue;
    mxd = 1; predfs(v, u, 1);
    vec.emplace_back(mxd, v, x.second);
  }
  sort(begin(vec), end(vec));
  function<void(int,int,int,int)> dfs = [&](int u, int f, int d, int w) {
    if (w > g[d]) {
      g[d] = w; gp[d] = u;
    }
    for (auto& x: edge[u]) {
      int v = x.first, y = x.second;
      if (v == f || vis[v]) continue;
      dfs(v, u, d + 1, w + (y >= B ? 1 : -1));
    }
  };
  int rU, rV;
  auto check = [&](int x) -> bool {
    B = x;
    f[0] = 0; int m = 0;
    for (auto& x: vec) {
      int D, v, w; tie(D, v, w) = x;
      for (int i = 1; i <= D; i++) {
        g[i] = -inf;
      }
      dfs(v, u, 1, w >= B ? 1 : -1);
      if (m == 0) {
        for (int i = 1; i <= D; i++) {
          if (L <= i && i <= R && g[i] >= 0) {
            rU = u; rV = gp[i];
            return true;
          }
          f[i] = g[i]; fp[i] = gp[i];
        }
        m = D;
        continue;
      }
      int h = 1, t = 0, j = m;
      for (int i = 1; i <= D; i++) {
        if (L <= i && i <= R && g[i] >= 0) {
          rU = u; rV = gp[i];
          return true;
        }
        while (j > 0 && j >= L - i) {
          while (h <= t && f[j] >= f[dq[t]]) t--;
          dq[++t] = j; j--;
        }
        while (h <= t && dq[h] > R - i) h++;
        if (h <= t) {
          if (f[dq[h]] + g[i] >= 0) {
            rU = fp[dq[h]]; rV = gp[i];
            return true;
          }
        }
      }
      for (int i = 1; i <= D; i++) {
        if (i <= m) {
          if (g[i] > f[i]) {
            f[i] = g[i]; fp[i] = gp[i];
          }
        } else {
          f[i] = g[i]; fp[i] = gp[i];
        }
      }
      m = D;
    }
    return false;
  };
  int l = 0, r = 1e9, res = -10, tU = 0, tV = 0;
  while (l <= r) {
    int m = (l + r) / 2;
    if (check(m)) {
      tU = rU; tV = rV;
      res = m; l = m + 1;
    } else {
      r = m - 1;
    }
  }
  if (res > ans) {
    ans = res; ansU = tU; ansV = tV;
  }
  for (auto& x: edge[u]) {
    int v = x.first;
    if (vis[v]) continue;
    solve(getrt(v));
  }
}

int main() {
  n = gi(); L = gi(); R = gi();
  for (int i = 2, u, v, w; i <= n; i++) {
    u = gi(); v = gi(); w = gi();
    edge[u].emplace_back(v, w);
    edge[v].emplace_back(u, w);
  }
  siz[1] = n; solve(getrt(1));
  assert(ans != -1);
  printf("%d %d\n", ansU, ansV);
  return 0;
}