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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

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
    for (int i = 1; i <= n; i++) dp[0][i] = i;
    for (int j = 1; j < 20; j++) {
      for (int i = 1; i + (1 << j) <= n + 1; i++) {
        int l = dp[j - 1][i];
        int r = dp[j - 1][i + (1 << (j - 1))];
        if (h[l] > h[r]) dp[j][i] = l;
        else dp[j][i] = r;
      }
    }
  }
  int qlcp(int l, int r) {
    l = x[l]; r = x[r];
    if (l > r) swap(l, r);
    l++; int k = __lg(r - l + 1);
    int x = dp[k][l], y = dp[k][r - (1 << k) + 1];
    if (h[x] < h[y]) return x;
    else return y;
  }
}

int n;
char s[maxn];

double solve(int l, int r) {
  if (l == r) return n - l + 1;
  int m = SA::qlcp(l, r);
  double a = solve(l, m - 1);
  double b = solve(m + 1, r);
  
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    SA::build(n, s);
    printf("%.9lf\n", solve(1, n));
  }
  return 0;
}