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
  #define dbg(args...) cout << "" << #args << " -> ", err(args)
  void err() { std::cout << "" << std::endl; }
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
const int maxn = 100000 + 5;

char s[maxn];
int n, q, ri[maxn];

namespace Runs {
  struct SA {
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
    void build(int nn, const char* s) {
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
      if (l < 1 || l > n) return 0;
      if (r < 1 || r > n) return 0;
      if (l == r) return n - l + 1;
      l = x[l]; r = x[r];
      if (l > r) swap(l, r);
      l++; int k = __lg(r - l + 1);
      return min(dp[k][l], dp[k][r - (1 << k) + 1]);
    }
  } ori, rev;

  int n; char s[maxn];

  bool cmp(int x, int y) {
    int len = ori.qlcp(x, y);
    // if (x + len > n) return false;
    // if (y + len > n) return true;
    return s[x + len] < s[y + len];
  }

  void find(int type) {
    static int st[maxn], stn;
    stn = 0; st[stn++] = n + 1;
    for (int i = n; i >= 1; i--) {
      // dbg(i);
      // int x = stn;
      // while (x > 1) dbg(x, st[x - 1], cmp(i, st[stn - 1])), x--;
      while (stn > 1 && cmp(i, st[stn - 1]) == type) stn--;
      // check(i, st[stn - 1]);
      // dbg(i, st[stn - 1]);
      ri[i] = st[stn - 1] - 1;
      st[stn++] = i;
    }
  }
  void build(int nn, char* ss) {
    n = nn;
    for (int i = 1; i <= n; i++) s[i] = ss[i];
    s[n + 1] = 0;
    ori.build(n, ss); // 原串
    reverse(ss + 1, ss + n + 1);
    rev.build(n, ss); // 反串
    find(1);
  }
}
using Runs::ori;

int main() {
  scanf("%s%d", s + 1, &q);
  n = strlen(s + 1);
  Runs::build(n, s);
  for (int i = 1, l, k; i <= q; i++) {
    scanf("%d%d", &l, &k);
    if (k == 1) {
      printf("%d %d\n", l, n);
    } else if (l == n) {
      printf("%d %d\n", l, l);
    } else {
      int per = ri[l] - l + 1;
      int tmp = min(ori.qlcp(l, ri[l] + 1), n - ri[l]);
      int len = tmp / per * per;
      int cnt = tmp / per + 1;
      if (ri[l] + 1 + len <= n) {
        if (cnt % k == 0) {
          printf("%d %d\n", l + cnt / k * (k - 1) * per, n);
        } else {
          printf("%d %d\n", l, l + ((cnt + k) / k) * per - 1);
        }
      } else {
        printf("%d %d\n", l, l + ((cnt + k - 1) / k) * per - 1);
      }
    }
  }
  return 0;
}