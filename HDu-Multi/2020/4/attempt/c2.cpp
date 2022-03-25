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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 2000000 + 5;

int n, m;
ll f[maxn], g[maxn];
vector<PII> val[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= 1000; i++) {
      val[i].clear();
    }
    for (int i = 1; i <= n; i++) {
      int c, w; scanf("%d%d", &c, &w);
      val[c].emplace_back(w, 0);
    }
    for (int i = 1; i <= m; i++) {
      int c, w; scanf("%d%d", &c, &w);
      val[c].emplace_back(w, 1);
    }
    ll ans = 0;
    f[0] = g[0] = 0;
    int fL = 0, gL = 0;
    for (int c = 1; c <= 1000; c++) {
      vector<int> v[2];
      for (auto& x: val[c]) v[x.second].push_back(x.first);
      sort(begin(v[0]), end(v[0]), greater<int>());
      sort(begin(v[1]), end(v[1]), greater<int>());
      int i = 0, j = 0;
      while (i < v[0].size() && j < v[1].size()) {
        if (v[0][i] + v[1][j] >= 0) {
          ans += v[0][i] + v[1][j];
          i++;
          j++;
        } else {
          break;
        }
      }
      while (i < v[0].size()) {
        int val = v[0][i];
        for (int i = fL + 1; i <= c + fL; i++) {
          f[i] = -inf;
        }
        for (int i = c + fL; i >= c; i--) {
          f[i] = max(f[i], f[i - c] + val);
        }
        fL += c;
        i++;
      }
      while (j < v[1].size()) {
        int val = v[1][j];
        for (int i = gL + 1; i <= c + gL; i++) {
          g[i] = -inf;
        }
        for (int i = c + gL; i >= c; i--) {
          g[i] = max(g[i], g[i - c] + val);
        }
        gL += c;
        j++;
      }
    }
    ll res = 0;
    for (int i = 0; i <= fL && i <= gL; i++) {
      res = max(res, f[i] + g[i]);
    }
    printf("%lld\n", ans + res);
  }
  return 0;
}