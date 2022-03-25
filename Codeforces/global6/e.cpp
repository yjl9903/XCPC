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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, q, a[maxn], b[maxn];
map<int,int> mp[maxn];

int main() {
  scanf("%d", &n);
  ll ans = 0;
  for (int i = 1; i <= n; i++) scanf("%d", a + i), ans += a[i];
  scanf("%d", &q);
  auto add = [&](int u, int x) {
    ans += min(a[u], b[u]);
    b[u] += x;
    ans -= min(a[u], b[u]);
  };
  while (q--) {
    int s, t, u;
    scanf("%d%d%d", &s, &t, &u);
    if (mp[s].count(t)) {
      add(mp[s][t], -1);
      mp[s].erase(t);
    }
    if (u > 0) {
      add(mp[s][t] = u, 1);
      mp[s][t] = u;
    }
    printf("%I64d\n", ans);
  }
  return 0;
}