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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

ll cal(ll val, int d) {
  if (val == 0) return 0;
  return max(val - d, 1ll);
}

int n, rt, a[maxn];
int tot, dfn[maxn], dep[maxn], fa[20][maxn];
vector<int> edge[maxn], bag[maxn];

void getdep(int u, int f) {
  fa[0][u] = f;
  for (int i = 1; i < 20; i++) {
    fa[i][u] = fa[i - 1][fa[i - 1][u]];
  }
  dfn[u] = ++tot;
  dep[u] = dep[f] + 1;
  for (int v: edge[u]) {
    if (v == f) continue;
    getdep(v, u);
  }
}
int qlca(int x, int y) {
  if (dep[x] < dep[y]) swap(x, y);
  int tmp = dep[x] - dep[y];
  for (int i = 0; tmp; i++, tmp >>= 1)
    if (tmp & 1) x = fa[i][x];
  if (x == y) return x;
  for (int i = 19; i >= 0; i--) {
    if (fa[i][x] != fa[i][y]) {
      x = fa[i][x]; y = fa[i][y];
    }
  }
  return fa[0][x];
}

namespace VT {
  int stk[maxn], top;
  void build(vector<int>& vec) {
    sort(vec.begin(), vec.end(), [&](int a, int b) { return dfn[a] < dfn[b]; });
    stk[top = 1] = rt; edge[rt].clear();
    for (int x: vec) {
      if (x == rt) continue;
      int g = qlca(stk[top], x);
      if (g != stk[top]) {
        while (dfn[g] < dfn[stk[top - 1]]) {
          edge[stk[top - 1]].push_back(stk[top]); top--;
        }
        if (dfn[g] > dfn[stk[top - 1]]) {
          edge[g].clear();
          edge[g].push_back(stk[top]);
          stk[top] = g;
        } else {
          edge[g].push_back(stk[top]); top--;
        }
      }
      edge[x].clear(); stk[++top] = x;
    }
    for (int i = 1; i < top; i++) {
      edge[stk[i]].push_back(stk[i + 1]);
    }
  }
}

ll dfs(int u, int f) {
  ll ans = a[u];
  for (int v: edge[u]) {
    if (v == f) continue;
    ll val = dfs(v, u);
    ans += cal(val, dep[v] - dep[u]);
  }
  return ans;
}

int main() {
  scanf("%d%d", &n, &rt);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  getdep(rt, 0);
  ll ans = cal(a[rt], 1); a[rt] = 0;
  for (int i = 1; i <= n; i++) {
    bag[dep[i]].push_back(i);
    edge[i].clear();
  }
  for (int i = 2; i <= n; i++) {
    if (bag[i].empty()) continue;
    VT::build(bag[i]);
    ans += cal(dfs(rt, 0), 1);
    for (int x: bag[i]) a[x] = 0;
  }
  cout << ans << endl;
  return 0;
}