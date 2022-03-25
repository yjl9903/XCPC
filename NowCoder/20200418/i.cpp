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
const int maxn = 1000000 + 5;

int n, m, rt, a[maxn];
vector<int> edge[maxn];

ll c[maxn];
void update(int i, int x) {
  for (; i <= n; i += i & -i) c[i] += x;
}
ll query(int i) {
  ll r = 0;
  for (; i; i -= i & -i) r += c[i];
  return r;
}
ll query(int l, int r) {
  return query(r) - query(l - 1);
}

int tot, dfn[maxn], siz[maxn];
void dfs(int u, int f) {
  dfn[u] = ++tot; siz[u] = 1;
  update(tot, a[u]);
  for (int v: edge[u]) {
    if (v == f) continue;
    dfs(v, u);
    siz[u] += siz[v];
  }
}

int main() {
  scanf("%d%d%d", &n, &m, &rt);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  dfs(rt, 0);
  for (int i = 1, op, u; i <= m; i++) {
    scanf("%d%d", &op, &u);
    if (op == 1) {
      int x; scanf("%d", &x);
      update(dfn[u], x);
    } else if (op == 2) {
      printf("%lld\n", query(dfn[u], dfn[u] + siz[u] - 1));
    }
  }
  return 0;
}