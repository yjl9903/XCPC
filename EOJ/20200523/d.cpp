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
void dfs(int u, int f) {
  vis[u] = 1;
  ans = max(ans, dep[u]);
  if (dep[u] > dep[rt]) rt = u;
  for (int v: edge[u]) {
    if (v == f) continue;
    if (a[v] != 1) continue;
    dep[v] = dep[u] + 1;
    dfs(v, u);
  }
}

int dfs2(int u, int f) {
  int mx = 0;
  for (int v: edge[u]) {
    if (v == f) continue;
    if (a[v] != 1) continue;
    mx = max(mx, dfs2(v, u));
  }
  return mx + 1;
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
      dep[i] = 1; rt = i;
      dfs(i, 0);
      dep[rt] = 1;
      dfs(rt, 0);
    }
  }
  int ans2 = -1;
  for (int i = 1; i <= n; i++) {
    if (a[i] == 2) {
      vector<int> v;
      for (int x: edge[i]) {
        if (a[x] == 1) {
          v.push_back(dfs2(x, 0));
        }
      }
      sort(begin(v), end(v), greater<int>());
      if (v.size() >= 2) {
        ans2 = max(ans2, v[1]);
      }
    }
  }
  if (ans2 == -1) {
    printf("%d/%d\n", 1, ans);
  } else {
    if (2 * ans < 2 * ans2 + 1) {
      printf("%d/%d\n", 2, 2 * ans2 + 1);
    } else {
      printf("%d/%d", 1, ans);
    }
  }
  return 0;
}