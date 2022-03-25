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
const int maxn = 500000 + 5;

int n, siz[maxn];
vector<int> edge[maxn];

void predfs(int u) {
  siz[u] = 1;
  for (int v: edge[u]) {
    predfs(v);
    siz[u] += siz[v];
  }
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      edge[i].clear();
    }
    for (int i = 2, fa; i <= n; i++) {
      scanf("%d", &fa);
      edge[fa].push_back(i);
    }
    predfs(1);
    ll ans = 0;
    function<void(int,ll)> dfs = [&](int u, ll sum) {
      sum += n - siz[u];
      ans = max(ans, sum);
      for (int v: edge[u]) {
        dfs(v, sum);
      }
    };
    dfs(1, 0);
    for (int i = 1; i <= n; i++) {
      ans += siz[i];
    }
    printf("%lld\n", ans);
  }
  return 0;
}