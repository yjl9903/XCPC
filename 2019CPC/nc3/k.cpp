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
const int maxn = 100000 + 5;

int n, k, a[maxn];
vector<int> edge[maxn];

int c[maxn];
void update(int i, int x) {
  for (i++; i < maxn; i += i & -i) c[i] += x;
}
int query(int i) {
  int r = 0;
  for (i++; i; i -= i & -i) r += c[i];
  return r;
}

int tot, dep[maxn], rdfn[maxn], dfn[maxn], siz[maxn], son[maxn];
void predfs(int u, int f) {
  dep[u] = dep[f] + 1;
  siz[u] = 1;
  dfn[u] = ++tot; rdfn[tot] = u;
  for (int v: edge[u]) {
    if (v == f) continue;
    predfs(v, u);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) son[u] = v;
  }
}

struct Query { // a[i]=c, dfn[i]<=l, dep[i]<=d
  int l, d, op;
  bool operator<(const Query& b) const {
    if (l == b.l) return abs(op) < abs(b.op);
    return l < b.l;
  }
};
vector<Query> que[maxn];

void dfs(int u, int f) {
  for (int v: edge[u]) {
    if (v == f) continue;
    dfs(v, u);
    if (v == son[u]) continue;
    for (int i = dfn[v]; i <= dfn[v] + siz[v] - 1; i++) {
      int x = rdfn[i];
      if (dep[x] - dep[u] >= k) continue;
      int c = 2 * a[u] - a[x];
      if (c > n) continue;
      if (c < 0) continue;
      int d = min(dep[u] + k - (dep[x] - dep[u]), n);

      que[c].push_back({ dfn[son[u]] - 1, d, -1 });
      que[c].push_back({ dfn[son[u]] + siz[son[u]] - 1, d, 1 });

      que[c].push_back({ dfn[u], d, -1 });
      que[c].push_back({ dfn[u] + siz[u] - 1, d, 1 });

      que[c].push_back({ dfn[v] - 1, d, 1 });
      que[c].push_back({ dfn[v] + siz[v] - 1, d, -1 });
    }
  }
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  for (int i = 2, fa; i <= n; i++) {
    scanf("%d", &fa);
    edge[fa].push_back(i);
  }
  predfs(1, 0); dfs(1, 0);
  for (int i = 1; i <= n; i++) {
    que[a[i]].push_back({ dfn[i], dep[i], 0 });
  }
  ll ans = 0;
  for (int c = 0; c <= n; c++) {
    sort(que[c].begin(), que[c].end());
    for (auto& q: que[c]) {
      if (q.op == 0) {
        update(q.d, 1);
      } else {
        ans += q.op * query(q.d);
      }
    }
  }
  cout << ans << endl;
  return 0;
}