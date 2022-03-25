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
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

struct Bit {
  int n, a[maxn * 2];
  void clear(int _n) {
    n = _n;
    for (int i = 0; i <= n + 10; i++) a[i] = 0;
  }
  void update(int i, int x) {
    for (; i; i -= i & -i) a[i] += x;
  }
  int query(int i) {
    int r = 0;
    for (; i <= n; i += i & -i) r += a[i];
    return r;
  }
} f0, f1;

int n, a[maxn];

ll pre[2][maxn], suf[maxn];
ll solve(int n, int* a, int offset, int isEnd = 1) {
  suf[n + 1] = 0;
  for (int i = n; i >= 1; i--) {
    suf[i] = a[i] + suf[i + 1];
  }
  vector<ll> lsh;
  int m0 = 0, m1 = 0;
  pre[0][0] = 0;
  for (int i = 2; i <= n; i += 2, m0++) {
    pre[0][m0 + 1] = pre[0][m0] + a[i - 1] - a[i];
  }
  for (int i = 0, j = 0; i <= n; i += 2, j++) {
    pre[0][j] += suf[i + 1];
    // dbg(0, i, pre[0][j]);
    lsh.push_back(pre[0][j]);
  }
  pre[1][1] = 0;
  for (int i = 3; i <= n; i += 2, m1++) {
    pre[1][m1 + 1] = pre[1][m1] + a[i - 1] - a[i];
  }
  for (int i = 1, j = 0; i <= n; i += 2, j++) {
    pre[1][j] += suf[i + 1];
    // dbg(1, i, pre[1][j]);
    lsh.push_back(pre[1][j]);
  }

  sort(lsh.begin(), lsh.end());
  lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
  auto gid = [&](ll x) {
    return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin() + 1;
  };
  f0.clear(n + n);
  f1.clear(n + n);
  if (n % 2 == 1) m1--;
  // else m0--;
  for (int j = 1; j <= m0; j++) {
    f0.update(gid(pre[0][j]), 1);
  }
  for (int j = 0; j <= m1; j++) {
    f1.update(gid(pre[1][j]), 1);
    // dbg(j, gid(pre[1][j]));
  }

  ll ans = 0, sumc = 0;
  for (int i = 1; i <= n - isEnd; i++) {
    sumc += a[i];
    if (i % 2 == 1) {
      ll val = sumc + (pre[1][i / 2] - suf[i + 1]) - offset;
      int id = gid(val + 1);
      ans += f1.query(id);
      // dbg(i, val, id, f1.query(id));
      f1.update(gid(pre[1][i / 2]), -1);
    } else {
      ll val = sumc + (pre[0][i / 2] - suf[i + 1]) - offset;
      int id = gid(val + 1);
      // dbg(i, val, id);
      ans += f0.query(id);
      // dbg(i, f0.query(id));
      f0.update(gid(pre[0][i / 2]), -1);
    }
  }
  return ans;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    if (n == 1) {
      puts("1");
    } else if (n == 2) {
      printf("%d\n", 1 + int(a[1] != a[2]));
    } else {
      ll ans = 0;
      {
        suf[n + 1] = 0;
        for (int i = n; i >= 1; i--) {
          suf[i] = suf[i + 1] + a[i];
        }
        ll sump = 0;
        for (int i = 1; i <= n; i++) {
          sump += a[i];
          if (i >= 2 && sump > suf[i + 1]) {
            ans++;
          }
        }
      }
      ans += solve(n, a, 0);
      ans += solve(n - 1, a, -a[n], 0);
      ans += solve(n - 1, a + 1, a[1]);
      ans += solve(n - 2, a + 1, a[1] - a[n], 0);
      printf("%lld\n", ans % mod);
    }
  }
  return 0;
}