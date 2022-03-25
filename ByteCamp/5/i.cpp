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

int n, ri[maxn];
char s[maxn];

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
      while (stn > 1 && cmp(i, st[stn - 1]) == type) stn--;
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
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%s", &n, s + 1);
    Runs::build(n, s);
    for (int i = 1; i <= n; i++) {
      printf("%d%c", ri[i] - i + 1, " \n"[i == n]);
    }
  }
  return 0;
}