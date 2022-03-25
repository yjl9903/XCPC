#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a, b) memset(a, b, sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int, int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

typedef unsigned long long ull;
const int seed = 135;
const int p1 = 1e9 + 7, p2 = 1e9 + 9;
ull xp1[maxn], xp2[maxn], xp[maxn];
struct Hash {
  static void init() {
    xp1[0] = xp2[0] = xp[0] = 1;
    for (int i = 1; i < maxn; ++i) {
      xp1[i] = xp1[i - 1] * seed % p1;
      xp2[i] = xp2[i - 1] * seed % p2;
      xp[i] = xp[i - 1] * seed;
    }
  }

  ull h[maxn];
  ull build(int n, const char* s) {
    ull r1 = 0, r2 = 0;
    for (int i = 1; i <= n; i++) {
      r1 = (r1 * seed + s[i]) % p1;
      r2 = (r2 * seed + s[i]) % p2;
      h[i] = (r1 << 32) | r2;
    }
    return h[n];
  }

  ull get(int l, int r) {
    int len = r - l + 1;
    unsigned int mask32 = ~(0u);
    ull left1 = h[l - 1] >> 32, right1 = h[r] >> 32;
    ull left2 = h[l - 1] & mask32, right2 = h[r] & mask32;
    return (((right1 - left1 * xp1[len] % p1 + p1) % p1) << 32) |
           (((right2 - left2 * xp2[len] % p2 + p2) % p2));
  }
} h1, h2;

bool ok[255];
int n;
char s[maxn], t[maxn], rt[maxn];

int solve(int L, int R) {
  int n = R - L + 1;
  for (int i = 1; i <= n; i++) {
    t[i] = s[L + i - 1];
    rt[i] = s[R - i + 1];
    if (rt[i] == 'b') rt[i] = 'q';
    else if (rt[i] == 'q') rt[i] = 'b';
    else if (rt[i] == 'd') rt[i] = 'p';
    else if (rt[i] == 'p') rt[i] = 'd';
    else if (rt[i] == 'w') rt[i] = 'm';
    else if (rt[i] == 'm') rt[i] = 'w';
    else if (rt[i] == 'n') rt[i] = 'u';
    else if (rt[i] == 'u') rt[i] = 'n';
  }
  t[n + 1] = rt[n + 1] = 0;
  dbg(t + 1, rt + 1);
  h1.build(n, t);
  h2.build(n, rt);
  int ans = 1;
  for (int i = 1; i <= n; i++) {
    int l = 1, r = min(i - 1, n - i);
    dbg(i);
    while (l <= r) {
      int m = (l + r) / 2;
      // dbg(i - m, i + m, h1.get(i - m, i + m));
      // dbg(n - i + 1 - m, n - i + 1 + m, h2.get(n - i + 1 - m, n - i + 1 + m));
      if (h1.get(i - m, i + m) == h2.get(n - i + 1 - m, n - i + 1 + m)) {
        ans = max(ans, m + m + 1);
        l = m + 1;
      } else {
        r = m - 1;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    int l = 1, r = min(i, n - i);
    while (l <= r) {
      int m = (l + r) / 2;
      dbg(i - m + 1, i + m);
      dbg(n - i + 1 - m, n - i + 1 + m - 1);
      if (h1.get(i - m + 1, i + m) == h2.get(n - i + 1 - m, n - i + 1 + m - 1)) {
        ans = max(ans, m + m);
        l = m + 1;
      } else {
        r = m - 1;
      }
    }
  }
  return ans;
}

int main() {
  Hash::init();
  ok['b'] = ok['q'] = 1;
  ok['d'] = ok['p'] = 1;
  ok['w'] = ok['m'] = 1;
  ok['n'] = ok['u'] = 1;
  ok['o'] = ok['s'] = ok['x'] = ok['z'] = 1;
  scanf("%s", s + 1);
  n = strlen(s + 1);
  int ans = 0;
  for (int i = 1, j = 1; i <= n; i = j) {
    if (!ok[s[i]]) {
      j++;
    } else {
      while (j <= n && ok[s[j]]) j++;
      ans = max(ans, solve(i, j - 1));
    }
  }
  printf("%d\n", ans);
  return 0;
}