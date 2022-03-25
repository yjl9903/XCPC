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

int n, ans[maxn][2];
vector<int> edge[maxn];

int son[maxn], siz[maxn], fa[maxn];
void dfs(int u, int f) {
  siz[u] = 1; fa[u] = f;
  int mx = 0, son = 0;
  for (int v: edge[u]) {
    if (v == f) continue;
    dfs(v, u);
    siz[u] += siz[v];
    if (siz[v] > mx) {
      mx = siz[v]; son = v;
    }
  }
  ::son[u] = son;
  if (siz[u] == 1) {
    ans[u][0] = u;
    return ;
  }
  if (2 * mx < siz[u]) ans[u][0] = u;
  else if (2 * mx == siz[u]) ans[u][0] = u, ans[u][1] = son;
  else {
    int x = ans[son][0];
    auto check = [&](int x) {
      if (2 * siz[::son[x]] > siz[u]) return false;
      if (2 * (siz[u] - siz[x]) > siz[u]) return false;
      return true;
    };
    while (!check(x)) x = fa[x];
    ans[u][0] = x;
    if (x != u && check(fa[x])) ans[u][1] = fa[x];
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  dfs(1, 0);
  for (int i = 1; i <= n; i++) {
    if (ans[i][1]) {
      int a = ans[i][0], b = ans[i][1];
      if (a > b) swap(a, b);
      printf("%d %d\n", a, b);
    } else {
      printf("%d\n", ans[i][0]);
    }
  }
  return 0;
}