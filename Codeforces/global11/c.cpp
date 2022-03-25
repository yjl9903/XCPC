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

int r, n, t[maxn], x[maxn], y[maxn];
int pref[maxn], f[maxn];

int main() {
  scanf("%d%d", &r, &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d%d", t + i, x + i, y + i);
  }
  x[0] = y[0] = 1;
  for (int i = 1; i <= n; i++) {
    f[i] = -inf;
    for (int j = i - 1; j >= 0; j--) {
      if (t[i] - t[j] > r + r + 1) {
        f[i] = max(f[i], pref[j] + 1);
        break;
      } else if (abs(x[i] - x[j]) + abs(y[i] - y[j]) <= t[i] - t[j]) {
        f[i] = max(f[i], f[j] + 1);
      }
    }
    pref[i] = max(pref[i - 1], f[i]);
  }
  printf("%d", pref[n]);
  return 0;
}