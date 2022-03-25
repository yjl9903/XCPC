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
  void build(int nn, int* s) {
    n = nn; // important
    m = 1e5 + 1;
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
  }
}

int n, m, q, a[maxn], b[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    int ans = 0;
    while (q--) {
      int op, c, i;
      scanf("%d%d%d", &op, &c, &i);
      if (op == 1) {
        b[1] = c;
        for (int i = 1; i <= n; i++) b[i + 1] = a[i];
        b[n + 2] = 0;
        SA::build(n + 1, b);
        ans = SA::x[i];
      } else {
        for (int i = 1; i <= n; i++) b[i] = a[i];
        b[n + 1] = c;
        b[n + 2] = 0;
        SA::build(n + 1, b);
        ans = SA::x[i];
      }
      printf("%d\n", ans);
    }
  }
  return 0;
}