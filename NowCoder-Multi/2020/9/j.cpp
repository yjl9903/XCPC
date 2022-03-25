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
const int maxn = 500 + 5;

int n, m, a[maxn][maxn], R[maxn][maxn], ok[maxn], pre[maxn];

int pool[(int)1e6 + 5];
int* cnt = pool + (int)5e5 + 2;
vector<int> evs[maxn];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      scanf("%d", &a[i][j]);
    }
    for (int j = 1; j <= m; j++) {
      if (a[i][j] == 0) {
        R[i][j] = -1;
      } else {
        int st = j;
        while (j <= m && a[i][j] == 1) j++;
        j--;
        for (int k = st; k <= j; k++) {
          R[i][k] = j;
        }
      }
    }
  }
  ll ans = 0;
  for (int i = 1; i < n; i++) {
    for (int j = 1; j <= m; j++) {
      int r = min(R[i][j], R[i + 1][j]);
      if (r >= j + 1) {
        ans += r - j;
      }
    }
  }
  for (int u = 1; u + 2 <= n; u++) {
    for (int i = 1; i <= m; i++) {
      ok[i] = a[u][i] & a[u + 1][i];
    }
    for (int d = u + 2; d <= n; d++) {
      for (int i = 1; i <= m; i++) {
        ok[i] &= a[d][i];
      }
      for (int i = 1; i < m; i++) {
        if (ok[i] && ok[i + 1]) {
          ans++;
        }
      }
    }
  }
  for (int u = 2; u + 1 <= n; u++) {
    for (int d = u; d + 1 <= n; d++) {
      int s = 0;
      for (int i = 1; i <= m; i++) {
        s += a[d][i] ? 1 : -1;
        if (d == u) {
          ok[i] = a[d][i];
          pre[i] = s;
        } else {
          ok[i] &= a[d][i];
          pre[i] += s;
        }
      }

      for (int i = 1; i < m; i++) {
        if (ok[i + 1]) {
          ans += cnt[pre[i]];
          ans += cnt[pre[i] - 1];
          ans += cnt[pre[i] + 1];
        }
        if (ok[i]) {
          int r = min(R[u - 1][i], R[d + 1][i]);
          if (r >= i + 2) {
            cnt[pre[i]]++;
            evs[r - 1].push_back(pre[i]);
          }
        }
        for (int x: evs[i]) {
          cnt[x]--;
        }
        evs[i].clear();
      }
    }
  }
  printf("%lld\n", ans);
  return 0;
}