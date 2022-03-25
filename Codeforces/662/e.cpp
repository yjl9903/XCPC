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
const int mod = 1e9 + 7;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

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

namespace SA {
    int n, m, sa[maxn], h[maxn], c[maxn], x[maxn], y[maxn];
    void rsort() {
        for (int i = 1; i <= m; i++) c[i] = 0;
        for (int i = 1; i <= n; i++) c[x[i]]++;
        for (int i = 1; i <= m; i++) c[i] += c[i - 1];
        for (int i = n; i >= 1; i--) sa[c[x[y[i]]]--] = y[i];
    }
    int cmp(int i, int j, int k) {
        int a = i + k > n ? -1 : y[i + k];
        int b = j + k > n ? -1 : y[j + k];
        return y[i] == y[j] && a == b;
    }
    int dp[21][maxn];
    void build(int nn, char* s) {
        n = nn; m = 255;
        for (int i = 1; i <= n; i++) x[i] = s[i], y[i] = i;
        rsort();
        for (int k = 1, p; k <= n; k += k, m = p) {
            p = 0;
            for (int i = n; i > n - k; i--) y[++p] = i;
            for (int i = 1; i <= n; i++) if (sa[i] > k) y[++p] = sa[i] - k;
            rsort();
            for (int i = 1; i <= n; i++) swap(x[i], y[i]);
            x[sa[1]] = p = 1;
            for (int i = 2; i <= n; i++) x[sa[i]] = cmp(sa[i], sa[i - 1], k) ? p : ++p;
        }
        for (int i = 1; i <= n; i++) x[sa[i]] = i;
        for (int i = 1, k = 0; i <= n; i++) {
            if (k) k--;
            int j = sa[x[i] - 1];
            while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k++;
            h[x[i]] = k;
        }
        for (int i = 1; i <= n; i++) dp[0][i] = h[i];
        for (int j = 1; j < 21; j++) {
            for (int i = 1; i + (1 << j) <= n + 1; i++) {
                dp[j][i] = min(dp[j - 1][i], dp[j - 1][i + (1 << (j - 1))]);
            }
        }
    }
    int qlcp(int l, int r) {
        if (l <= 0) return 0;
        if (r <= 0) return 0;
        if (l == r) return n - l + 1;
        l = x[l]; r = x[r];
        if (l > r) swap(l, r);
        l++; int k = __lg(r - l + 1);
        return min(dp[k][l], dp[k][r - (1 << k) + 1]);
    }
}

int n;
char pre[maxn], tot[maxn], tmp[maxn];
string s[maxn];

int f[maxn], g[3][maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%s", tmp);
    s[i] = tmp;
  }
  for (int i = 0; i <= s[1].length(); i++) f[i] = 1;
  for (int i = 2; i <= n; i++) {
    int tlen = s[i].length(), plen = s[i - 1].length(), len = 0;
    for (int j = 1; j <= plen; j++) {
      pre[j] = s[i - 1][j - 1];
      tmp[++len] = pre[j];
    }
    tmp[++len] = 'z' + 1;
    pre[plen + 1] = 0;
    for (int j = 1; j <= tlen; j++) {
      tot[j] = s[i][j - 1];
      tmp[++len] = tot[j];
    }
    tot[tlen + 1] = 0;
    tmp[++len] = 0;
    tmp[len + 1] = 0;
    SA::build(len, tmp);
    for (int j = 0; j <= tlen + 1; j++) {
      g[0][j] = g[1][j] = g[2][j] = 0;
    }
    dbg(i, len, plen, tlen);
    int lcp = SA::qlcp(1, plen + 2);
    dbg(lcp);
    for (int j = 0; j <= plen; j++) {
      if (j > lcp + 1) {
        // pos <= lcp
        g[1][0] = add(g[1][0], f[j]);
        g[1][lcp + 1] = sub(g[1][lcp + 1], f[j]);
        // pos > lcp
        if (lcp < plen && lcp < tlen) {
          if (pre[lcp + 1] < tot[lcp + 1]) {
            g[0][lcp + 1] = add(g[0][lcp + 1], f[j]);
          }
        }
      } else {
        int lcp2 = SA::qlcp(j + 1, plen + 1 + j);
        // pos < j - 1
        if (0 <= j - 1) {
          g[1][0] = add(g[1][0], f[j]);
          g[1][j - 1] = sub(g[1][j - 1], f[j]);
        }
        // j - 1 <= pos <= j + lcp2 - 1
        int L = max(1, j - 1);
        if (L <= j + lcp2) {
          g[2][L] = add(g[2][L], f[j]);
          g[2][j + lcp2] = sub(g[2][j + lcp2], f[j]);
        }
        dbg(j, lcp2);
        // pos >= j + lcp2
        if (j + lcp2 < plen && j - 1 + lcp2 < tlen) {
          int p = j + lcp2 + (j + lcp2 == 0);
          if (pre[j + lcp2 + 1] < tot[p]) {
            g[0][j + lcp2] = add(g[0][j + lcp2], f[j]);
            dbg("g0", j + lcp2);
          }
        }
      }
    }
    auto pRk = [&](int i) {
      return SA::x[i];
    };
    auto tRk = [&](int i) {
      return SA::x[plen + i + 1];
    };
    for (int j = 0; j <= tlen; j++) {
      if (j) {
        g[0][j] = add(g[0][j], g[0][j - 1]);
        g[1][j] = add(g[1][j], g[1][j - 1]);
        g[2][j] = add(g[2][j], g[2][j - 1]);
      }
      int cur = g[0][j];
      if (j && tRk(j + 1) > tRk(j)) {
        cur = add(cur, g[1][j]);
      }
      if (tRk(j + 1) > tRk(j + 1)) {
        cur = add(cur, g[2][j]);
      }
      f[j] = cur;
      dbg(j, g[0][j], f[j]);
    }
    dbg("OK");
  }
  int ans = 0;
  for (int i = 0; i <= s[n].length(); i++) {
    ans = add(ans, f[i]);
  }
  printf("%d\n", ans);
  return 0;
}