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
const int maxn = 2000 + 5;

int n, m, a, b, M[maxn][maxn];

struct BIT {
  ll a[maxn][maxn];
  inline int lowbit(int x) { return x & -x; }
  void clear() {
    for (int i = 0; i <= n + 1; i++) {
      for (int j = 0; j <= m + 1; j++) {
        a[i][j] = 0;
      }
    }
  }
  void update(int x, int y, ll val) {
    for (int i = x; i <= n + 1; i += lowbit(i)) {
      for (int j = y; j <= m + 1; j += lowbit(j)) {
        a[i][j] += val;
      }
    }
  }
  ll query(int x, int y) {
    ll r = 0;
    for (int i = x; i; i -= lowbit(i)) {
      for (int j = y; j; j -= lowbit(j)) {
        r += a[i][j];
      }
    }
    return r;
  }
} f;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d", &n, &m, &a, &b);
    f.clear();
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        scanf("%d", &M[i][j]);
        f.update(i, j, M[i][j]);
        f.update(i + 1, j, -M[i][j]);
        f.update(i, j + 1, -M[i][j]);
        f.update(i + 1, j + 1, M[i][j]);
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        dbg(i, j, f.query(i, j));
      }
    }
    bool flag = true;
    for (int i = 1; i + a - 1 <= n && flag; i++) {
      for (int j = 1; j + b - 1 <= m && flag; j++) {
        ll val = f.query(i, j);
        if (val < 0) {
          flag = false;
        } else if (val > 0) {
          f.update(i, j, -val);
          f.update(i + a, j + b, -val);
          f.update(i + a, j, val);
          f.update(i, j + b, val);
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        if (f.query(i, j)) {
          flag = false;
        }
      }
    }
    puts(flag ? "^_^" : "QAQ");
  }
  return 0;
}