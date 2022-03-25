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

int n, a[maxn];
vector<int> edge[maxn];

int ans = 1, dep[maxn], rt, vis[maxn];
int dfs(int u, int f) {
  vis[u] = 1;
  int mx = 1;
  for (int v: edge[u]) {
    if (v == f) continue;
    if (a[v] != 1) continue;
    int tot = dfs(v, u);
    mx = max(mx, 1 + tot);
    ans = max(ans, mx + tot);
  }
  return mx;
}

int main() {
  scanf("%d", &n);
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  int cnto = -1, isz = 0, mn = inf;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    if (a[i] == 0) {
      isz = 1;
    } else if (a[i] == 1) {
      cnto = i;
    } else {
      mn = min(a[i], mn);
    }
  }
  if (isz) {
    puts("0/1");
    return 0;
  } else if (cnto == -1) {
    printf("%d/%d\n", mn, 1);
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    if (a[i] == 1 && !vis[i]) {
      dfs(i, 0);
    }
  }
  printf("%d/%d\n", 1, ans);
  return 0;
}