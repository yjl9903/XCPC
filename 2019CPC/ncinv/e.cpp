#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include <functional>
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
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;
const int maxm = 30000 + 5;

struct fastIO {
    char s[100000]; int it,len;
    fastIO() { it = len = 0; }
    inline char get() {
        if (it < len) return s[it++];
        it = 0; len = fread(s, 1, 100000, stdin);
        if (len == 0) return EOF;
        else return s[it++];
    }
    bool notend() {
        char c = get();
        while(c == ' ' || c == '\n') c = get();
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

namespace Mu {
  int mu[maxm], vis[maxm], prime[maxm], tot;
  vector<int> mud[maxm];
  void getMu() {
    tot = 0; mu[1] = 1;
    for (int i = 2; i < maxm; ++i) {
      if (!vis[i]) prime[++tot] = i, mu[i] = -1;
      for (int j = 1; j <= tot && i * prime[j] < maxm; j++) {
        vis[i * prime[j]] = 1;
        if (i % prime[j] == 0) {
          mu[i * prime[j]] = 0; break;
        }
        mu[i * prime[j]] = -mu[i];
      }
    }
    for (int i = 1; i < maxm; i++) {
      for (int x = 1; x * x <= i; x++) {
        if (i % x) continue;
        if (mu[x]) mud[i].push_back(x);
        if (x * x != i && mu[i / x]) mud[i].push_back(i / x);
      }
    }
  }
}
using Mu::mu;
using Mu::mud;

int n, D, a[maxn];
int vis[maxn], mxd[maxn], son[maxn], dp[maxn];
int* f[maxn];

struct Edge {
  int to, nxt;
} e[maxn * 2];
int ecnt, head[maxn];
void adde(int u, int v) {
  e[++ecnt] = { v, head[u] };
  head[u] = ecnt;
}
vector<int> ig[maxm];

int main() {
  Mu::getMu();
  int T = gi(), kase = 0;
  while (T--) {
    n = gi(); D = gi();
    ecnt = 0;
    for (int i = 1; i <= n; i++) head[i] = vis[i] = 0;
    for (int i = 1; i <= 30000; i++) ig[i].clear();
    for (int i = 1; i <= n; i++) {
      a[i] = gi();
      for (auto x: mud[a[i]]) ig[x].push_back(i);
    }
    for (int i = 2, u, v; i <= n; i++) {
      u = gi(); v = gi();
      adde(u, v); adde(v, u);
    }
    ll ans = 0;
    for (int i = 2; i <= 30000; i++) {
      if (ig[i].empty()) continue;
      int xs = -mu[i];
      for (auto& x: ig[i]) {
        if (vis[x] == i) continue;
        int cnt = 0;
        function<void(int,int)> predfs = [&](int u, int ff) {
          cnt++; vis[u] = i; son[u] = mxd[u] = 0;
          for (int j = head[u]; j; j = e[j].nxt) {
            int v = e[j].to;
            if (v == ff || a[v] % i) continue;
            predfs(v, u);
            if (mxd[v] > mxd[u]) {
              son[u] = v; mxd[u] = mxd[v];
            }
          }
          mxd[u]++;
        };
        int *tot = dp;
        auto make = [&](int u) {
          f[u] = tot; tot += mxd[u];
        };
        function<void(int,int)> dfs = [&](int u, int ff) {
          if (son[u]) {
            int v = son[u];
            f[v] = f[u] + 1;
            dfs(v, u);
          }
          if (mxd[u] - 1 >= D) ans += xs * f[u][D];
          f[u][0] = 1;
          for (int j = head[u]; j; j = e[j].nxt) {
            int v = e[j].to;
            if (v == ff || v == son[u] || a[v] % i) continue;
            make(v); dfs(v, u);
            for (int i = max(D - mxd[u], 0); i < mxd[v] && i < D; i++) {
              ans += 1ll * xs * f[v][i] * f[u][D - i - 1];
            }
            for (int i = 0; i < mxd[v] && i < D; i++) {
              f[u][i + 1] += f[v][i];
            }
          }
        };
        predfs(x, 0); 
        make(x); for (int i = 0; i <= cnt; i++) dp[i] = 0;
        dfs(x, 0);
      }
    }
    printf("Case #%d: %lld\n", ++kase, 2ll * ans);
  }
  return 0;
}