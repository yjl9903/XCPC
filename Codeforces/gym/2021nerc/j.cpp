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
const ll inf = 1ll << 60;
const int maxn = 200000 + 5;

int n, m, k;
int pre[maxn];

int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}
bool join(int x, int y) {
  x = find(x);
  y = find(y);
  if (x != y) {
    pre[x] = y;
    return true;
  }
  return false;
}

struct Edge {
  int u, v, w;

  bool operator < (const Edge& y) const {
    return w < y.w;
  }
} e[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++) {
      scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
    }
    sort(e + 1, e + 1 + m);
    for (int i = 1; i <= n; i++) {
      pre[i] = i;
    }
    ll ans = inf;
    int mx = -1, cnt = 0;
    for (int i = m; i >= 1; i--) {
      if (e[i].w > k) continue;
      if (join(e[i].u, e[i].v)) {
        cnt++;
        if (mx == -1) {
          mx = e[i].w;
        }
      }
    }
    if (cnt == n - 1) {
      ans = k - mx;
    }
    if (e[m].w > k) {
      for (int i = 1; i <= n; i++) {
        pre[i] = i;
      }
      int cnt = 0, mn = -1;
      ll sum = 0;
      for (int i = 1; i <= m; i++) {
        int w = e[i].w < k ? 0 : e[i].w - k;
        if (mn == -1 && e[i].w >= k) {
          mn = e[i].w - k;
        }
        if (join(e[i].u, e[i].v)) {
          cnt++;
          sum += w;
        }
      }
      if (cnt == n - 1) {
        if (sum == 0) {
          ans = min(ans, 1ll * mn);
        } else {
          ans = min(ans, sum);
        }
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}