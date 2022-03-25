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

int n, a[maxn], dep[maxn], fa[maxn];
vector<int> edge[maxn];

void dfs(int u, int f) {
  fa[u] = f; dep[u] = dep[f] + 1;
  for (int v: edge[u]) {
    if (v == f) continue;
    dfs(v, u);
  }
}
int query(int u, int v) {
  int ans = 0;
  while (u != v) {
    if (dep[u] < dep[v]) swap(u, v);
    ans++; u = fa[u];
  }
  return ans;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  dfs(1, 0);
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      ans = max(ans, max(a[i], a[j]) * query(i, j));
    }
  }
  cout << ans << endl;
  return 0;
}