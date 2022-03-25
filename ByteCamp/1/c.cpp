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

int n, pre[maxn], siz[maxn];
tuple<int,int,int> edge[maxn];

int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}
void join(int x, int y) {
  x = find(x); y = find(y);
  if (x == y) return ;
  pre[x] = y; siz[y] += siz[x];
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    pre[i] = i; siz[i] = 1;
  }
  for (int i = 1, u, v, w; i < n; i++) {
    scanf("%d%d%d", &u, &v, &w);
    edge[i] = { w, u, v };
  }
  sort(edge + 1, edge + n);
  reverse(edge + 1, edge + n);
  ll ans = 0;
  for (int i = 1; i < n; i++) {
    int w, u, v; tie(w, u, v) = edge[i];
    join(u, v);
    ans = max(ans, 1ll * w * (siz[find(u)] - 1));
  }
  printf("%lld\n", ans);
  return 0;
}