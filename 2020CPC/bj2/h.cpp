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
const int maxm = 105;

int n, m, w[maxn], v[maxn];
vector<ll> bag[maxm];
ll f[maxn], g[maxn];

int main() {
  while (scanf("%d%d", &n, &m) == 2) {
    for (int i = 0; i <= m; i++) {
      f[i] = g[i] = 0;
    }
    for (int i = 1; i < maxm; i++) {
      bag[i].clear();
    }
    for (int i = 1; i <= n; i++) {
      scanf("%d%d", v + i, w + i);
      bag[v[i]].push_back(w[i]);
    }
    for (int i = 1; i < maxm; i++) {
      if (bag[i].empty()) continue;
      sort(bag[i].begin(), bag[i].end(), greater<ll>());
      for (int j = 1; j < bag[i].size(); j++) {
        bag[i][j] += bag[i][j - 1];
      }
      for (int i = 0; i <= m; i++) g[i] = f[i];
      int x = i;
      auto& vec = bag[i];
      for (int j = 0; j < i; j++) {
        function<void(int,int,int,int)> solve = [&](int L, int R, int l, int r) {
          if (L > R) return ;
          int mid = (L + R) / 2, cur = mid;
          for (int i = min(r, mid - 1); i >= l; i--) {
            if (mid > (int)vec.size() + i) break;
            if (g[j + mid * x] < f[j + i * x] + vec[mid - i - 1]) {
              cur = i;
              g[j + mid * x] = f[j + i * x] + vec[mid - i - 1];
            }
          }
          solve(L, mid - 1, l, cur);
          solve(mid + 1, R, cur, r);
        };
        solve(0, (m - j) / i, 0, (m - j) / i);
      }
      for (int i = 0; i <= m; i++) {
        f[i] = max(f[i], g[i]);
      }
    }
    ll ans = f[m];
    for (int i = 0; i <= m; i++) ans = max(ans, f[i]);
    printf("%lld\n", ans);
  }
  return 0;
}