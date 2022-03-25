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
const int inf = 1 << 30;
const int maxn = 3000 + 5;

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

int n, ch[maxn][2];
bool isClique[maxn];

int pre[maxn], siz[maxn], cnt[maxn];
int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}
bool join(int x, int y) {
  x = find(x);
  y = find(y);
  if (x == y) return false;
  pre[x] = y;
  siz[y] += siz[x];
  cnt[y] += cnt[x];
  return true;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    pre[i] = i;
    siz[i] = 1;
  }
  vector<tuple<int,int,int> > egs;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int w;
      scanf("%d", &w);
      if (j < i) {
        egs.emplace_back(w, j, i);
      }
    }
  }
  sort(begin(egs), end(egs));
  int vsz = n;
  for (auto [w, u, v]: egs) {
    int x = find(u), y = find(v);
    if (x != y) {
      vsz++;
      pre[vsz] = vsz;
      join(x, vsz);
      join(y, vsz);
      siz[vsz] = siz[x] + siz[y];
      cnt[vsz] = cnt[x] + cnt[y];
      ch[vsz][0] = x;
      ch[vsz][1] = y;
    }
    int rt = find(u);
    cnt[rt]++;
    if (cnt[rt] == siz[rt] * (siz[rt] - 1) / 2) {
      isClique[rt] = true;
    }
  }
  function<vector<int>(int)> dfs = [&](int u) {
    vector<int> f(n + 1, 0);
    if (u <= n) {
      f[1] = 1;
      return f;
    }
    if (isClique[u]) {
      f[1] = 1;
    }
    auto g = dfs(ch[u][0]);
    auto h = dfs(ch[u][1]);
    for (int i = 1; i <= siz[ch[u][0]]; i++) {
      for (int j = 1; i + j <= siz[u]; j++) {
        int val = mul(g[i], h[j]);
        f[i + j] = add(f[i + j], val);
      }
    }
    return f;
  };

  vector<int> ans;
  for (int i = 1; i <= vsz; i++) {
    if (i == find(i)) {
      ans = dfs(i);
      break;
    }
  }

  for (int i = 1; i <= n; i++) {
    printf("%d ", ans[i]);
  }
  return 0;
}