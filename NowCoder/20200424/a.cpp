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
const int maxn = 200000 + 5;

int n, m, deg[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      deg[i] = 0;
    }
    for (int i = 1, u, v; i <= m; i++) {
      scanf("%d%d", &u, &v);
      deg[u]++; deg[v]++;
    }
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
      sum += 1ll * deg[i] * (n - 1 - deg[i]);
    }
    ll mx = 1ll * n * (n - 1) * (n - 2) / 3;
    if (sum >= mx) {
      puts("no");
    } else {
      puts("yes");
    }
  }
  return 0;
}