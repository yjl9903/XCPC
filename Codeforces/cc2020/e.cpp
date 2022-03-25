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
const int maxn = 100000 + 5;

int n, p, k, a[maxn], id[maxn], b[maxn][7];
ll f[500], g[500];

int main() {
  scanf("%d%d%d", &n, &p, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i); id[i] = i;
  }
  sort(id + 1, id + 1 + n, [&](int x, int y) {
    return a[x] > a[y];
  });
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < p; j++) {
      scanf("%d", &b[i][j]);
    }
  }
  int ss = 1 << p;
  for (int s = 1; s < ss; s++) f[s] = -1e16;
  for (int i = 1; i <= n; i++) {
    int id = ::id[i];
    for (int s = 0; s < ss; s++) {
      g[s] = f[s];
      for (int j = 0; j < p; j++) {
        if (s >> j & 1) {
          g[s] = max(g[s], f[s ^ (1 << j)] + b[id][j]);
        }
      }
      if (i - 1 - __builtin_popcount(s) < k) {
        g[s] = max(g[s], f[s] + a[id]);
      }
    }
    swap(f, g);
  }
  printf("%I64d\n", f[ss - 1]);
  return 0;
}