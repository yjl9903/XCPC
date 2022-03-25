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
const int maxn = 100000 + 5;

int n, a[maxn], R[maxn], ord[maxn];
char s[maxn];

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
    n = nn; m = nn + 2; // important
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

int main() {
  while (scanf("%d%s", &n, s + 1) == 2) {
    for (int i = 1, j = 1; i <= n; i = j) {
      while (j <= n && s[j] == s[i]) {
        j++;
      }
      for (int k = i; k < j; k++) {
        R[k] = j;
      }
    }
    int pre[2] = { -1, -1 };
    for (int i = 1; i <= n; i++) {
      int ch = s[i] - 'a';
      if (pre[ch] == -1) {
        a[i] = 1;
      } else {
        a[i] = i - pre[ch] + 2;
      }
      pre[ch] = i;
      dbg(i, a[i]);
    }
    SA::build(n, a);
    for (int i = 1; i <= n; i++) {
      ord[i] = i;
    }
    auto rk = [&](int p) {
      if (p > n) {
        return -1;
      }
      return SA::x[p];
    };
    sort(ord + 1, ord + 1 + n, [&](int lhs, int rhs) {
      int len1 = R[lhs] - lhs;
      int len2 = R[rhs] - rhs;
      if (len1 != len2) {
        return len1 < len2;
      } else if (R[lhs] > n || R[rhs] > n) {
        return R[lhs] > n;
      } else {
        return rk(R[lhs] + 1) < rk(R[rhs] + 1);
      }
    });
    for (int i = 1; i <= n; i++) {
      printf("%d%c", ord[i], " \n"[i == n]);
    }
  }
  return 0;
}