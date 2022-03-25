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

int n, a[maxn];
vector<int> edge[maxn];

ll all, sum[maxn];
int siz[maxn], fa[maxn];
void predfs(int u, int f) {
  fa[u] = f;
  sum[u] = a[u]; siz[u] = 1;
  for (int v: edge[u]) {
    if (v == f) continue;
    predfs(v, u);
    sum[u] += sum[v];
    siz[u] += siz[v];
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i); all += a[i];
  }
  vector<tuple<int,int,int> > egs;
  for (int i = 2; i <= n; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    edge[u].push_back(v);
    edge[v].push_back(u);
    egs.emplace_back(u, v, w);
  }
  predfs(1, 0);
  for (int i = 0; i + 1 < n; i++) {
    int u, v, w; tie(u, v, w) = egs[i];
    if (fa[u] != v) swap(u, v);
    ll ans = sum[u] * (n - siz[u]);
    ans += (all - sum[u]) * siz[u];
    printf("%lld\n", ans * w * 2ll);
  }
  return 0;
}