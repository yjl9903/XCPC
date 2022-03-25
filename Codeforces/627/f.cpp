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

int n, key[maxn];
vector<int> edge[maxn];

int siz[maxn], ans[maxn];
void predfs(int u, int f) {
  siz[u] = key[u] ? 1 : -1;
  for (int v: edge[u]) {
    if (v == f) continue;
    predfs(v, u);
    if (siz[v] > 0) siz[u] += siz[v];
  }
}
void dfs(int u, int f) {
  int sum = ans[u];
  for (int v: edge[u]) {
    if (v == f) continue;
    int tot = sum;
    if (siz[v] > 0) tot -= siz[v];
    ans[v] = siz[v];
    if (tot > 0) ans[v] += tot;
    dfs(v, u);
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", key + i);
  }
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  predfs(1, 0);
  ans[1] = siz[1];
  dfs(1, 0);
  for (int i = 1; i <= n; i++) {
    printf("%d ", ans[i]);
  }
  return 0;
}