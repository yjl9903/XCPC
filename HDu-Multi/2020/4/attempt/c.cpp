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
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
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
const ll inf = 1ll << 60;
const int maxn = 6 + 5;

int n, m, ord[maxn], cost[maxn], val[maxn];
ll f[maxn], g[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    set<PII> st;
    for (int i = 1; i <= n + m; i++) {
      scanf("%d%d", cost + i, val + i);
      if (i > n) {
        st.insert({ cost[i], val[i] });
      } else {
        ord[i] = i;
      }
    }
    
    for (int i = 1; i < maxn; i++) {
      f[i] = -inf;
    }
    f[0] = 0;

    sort(ord + 1, ord + 1 + n, [&](int x, int y) {
      return cost[x] < cost[y];
    });

    for (int i = 1; i <= n; i++) {
      int c = cost[ord[i]];
      int v = val[ord[i]];
      for (int i = 0; i < maxn; i++) {
        g[i] = f[i];
      }
      for (int i = 0; i + c < maxn; i++) {
        g[i + c] = max(g[i + c], f[i] + v);
      }

      while (!st.empty()) {
        int R = 0;
        for (int i = maxn - 1; i >= 0; i--) {
          if (g[i] > 0) {
            R = i; break;
          }
        }
        auto it = st.begin();
        int c = it->first;
        int v = it->second;
        if (R < c) break;
        st.erase(it);
        dbg(R, c, v);

        for (int i = 0; i < maxn; i++) {
          f[i] = g[i];
        }
        for (int i = c; i < maxn; i++) {
          g[i - c] = max(g[i - c], f[i] + v);
        }
      }
      
      dbg(i);
      for (int i = 0; i < maxn; i++) {
        dbg(i, g[i]);
      }
      for (int i = 0; i < maxn; i++) {
        f[i] = g[i];
      }
      // dbg(i, f[0]);
    }
    printf("%lld\n", f[0]);
  }
  return 0;
}