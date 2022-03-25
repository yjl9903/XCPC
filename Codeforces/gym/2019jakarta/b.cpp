#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

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

int n, f[maxn], g[maxn], h[maxn];
vector<int> edge[maxn];

void dfs(int u, int ff) {
  for (auto it = edge[u].begin(); it != edge[u].end(); it++) {
    if (*it == ff) {
      edge[u].erase(it); break;
    }
  }
  int sz = (int)edge[u].size();
  int sum = 0, sum2 = 0;
  int pif = 1, pifg = 1;
  vector<int> vfg, vf;
  for (int v: edge[u]) {
    if (v == ff) continue;
    dfs(v, u);
    pif = mul(pif, f[v]);
    pifg = mul(pifg, add(f[v], g[v]));
    vfg.push_back(add(f[v], g[v]));
    vf.push_back(f[v]);
  }
  g[u] = h[u] = pif;

  vector<int> prefg(sz, 0), pref(sz, 0);
  vector<int> suffg(sz, 0), suff(sz, 0);
  for (int i = 0; i < sz; i++) {
    if (i == 0) {
      prefg[i] = vfg[i];
      pref[i] = vf[i];
    } else {
      prefg[i] = mul(prefg[i - 1], vfg[i]);
      pref[i] = mul(pref[i - 1], vf[i]);
    }
  }
  for (int i = sz - 1; i >= 0; i--) {
    if (i == sz - 1) {
      suffg[i] = vfg[i];
      suff[i] = vf[i];
    } else {
      suffg[i] = mul(suffg[i + 1], vfg[i]);
      suff[i] = mul(suff[i + 1], vf[i]);
    }
  }

  for (int i = 0; i < sz; i++) {
    int v = edge[u][i];
    int tg = mul(i == 0 ? 1 : pref[i - 1], i == sz - 1 ? 1 : suff[i + 1]);
    g[u] = add(g[u], mul(h[v], tg));
    int th = mul(i == 0 ? 1 : prefg[i - 1], i == sz - 1 ? 1 : suffg[i + 1]);
    h[u] = add(h[u], mul(h[v], th));
  }

  int pre = 0;
  for (int i = 0; i < sz; i++) {
    int v = edge[u][i];
    int suf = mul(h[v], i == sz - 1 ? 1 : suffg[i + 1]);
    f[u] = add(f[u], mul(pre, suf));
    pre = mul(pre, f[v] + g[v]);
    pre = add(pre, mul(h[v], i == 0 ? 1 : prefg[i - 1]));
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  dfs(1, 0);
  cout << add(f[1], g[1]) << endl;
  return 0;
}