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
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const ll inf = 1ll << 60;
const int maxn = 100000 + 5;

int n, a[maxn]; ll mn;

struct Info {
  ll val[2][2];
  Info() {
    val[0][0] = val[0][1] = val[1][0] = val[1][1] = inf;
  }
  Info(int i) {
    if (a[i] >= mn) { // 两端点不匹配
      val[0][0] = a[i];
    } else {
      val[0][0] = inf;
    }
    if (a[i] + a[i - 1] >= mn) { // 左端点匹配
      val[1][0] = a[i] + a[i - 1];
    } else {
      val[1][0] = inf;
    }
    val[0][1] = -inf; // 右端点匹配
    val[1][1] = inf; // 两端均匹配，不存在
  }
  ll* operator [] (int x) { return val[x]; }
  const ll* operator [] (int x) const { return val[x]; }
  Info operator+(const Info& b) {
    Info r;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        ll x = max(val[i][0], b[0][j]);
        ll y = max(val[i][1], b[1][j]);
        r[i][j] = min(x, y);
      }
    }
    return r;
  }
} t[maxn << 2];

void build(int l = 1, int r = n, int rt = 1) {
  if (l == r) {
    t[rt] = Info(l); return ;
  }
  int m = (l + r) / 2;
  build(lson); build(rson);
  t[rt] = t[rt << 1] + t[rt << 1 | 1];
}
void update(int i, int l = 1, int r = n, int rt = 1) {
  if (l == r) {
    t[rt] = Info(l); return ;
  }
  int m = (l + r) / 2;
  if (i <= m) update(i, lson);
  else update(i, rson);
  t[rt] = t[rt << 1] + t[rt << 1 | 1];
}

ll cal(int mn) {
  vector<ll> f(n + 1, -inf), g(n + 1, -inf);
  for (int i = 1; i <= n; i++) {
    // f[i] = min(f[i - 1], g[i - 1]);
    f[i] = g[i - 1];
    ll one = a[i];
    ll two = a[i] + a[i - 1];
    if (one < mn) one = inf;
    if (two < mn) two = inf;
    g[i] = min(max(one, g[i - 1]), max(two, f[i - 1]));
  }
  return g[n];
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    vector<tuple<int,int,int> > teams;
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      teams.emplace_back(a[i], i, 1);
      if (i > 1) {
        teams.emplace_back(a[i - 1] + a[i], i, 2);
      }
    }
    sort(begin(teams), end(teams));
    mn = get<0>(teams[0]);
    build(); 
    ll ans = inf;
    for (int i = 0, j; i < n + n - 1; i = j) {
      ans = min(ans, min(t[1][0][0], t[1][1][0]) - mn);
      j = i;
      while (j < n + n - 1 && get<0>(teams[i]) == get<0>(teams[j])) j++;
      if (j == n + n - 1) break;
      mn = get<0>(teams[j]);
      for (int k = i; k < j; k++) update(get<1>(teams[k]));
    }
    printf("%lld\n", ans);
  }
  return 0;
}