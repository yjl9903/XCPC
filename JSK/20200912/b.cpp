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
const int maxn = 300000 + 5;

int n, m, a[maxn][2];
bool vis[maxn];

struct Seg {
  int tp, l, r, val;
} b[maxn];

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i][0]);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i][1]);
  }
  ll ans = 0;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d%d%d", &b[i].tp, &b[i].l, &b[i].r, &b[i].val);
    b[i].tp--;
    ll sum1 = b[i].val, sum2 = 0;
    for (int j = b[i].l; j <= b[i].r; j++) {
      vis[j] = true;
      sum1 += a[j][b[i].tp];
      sum2 += max(a[j][0], a[j][1]);
    }
    ans += max(sum1, sum2);
  }
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {
      ans += max(a[i][0], a[i][1]);
    }
  }
  printf("%lld\n", ans);
  return 0;
}