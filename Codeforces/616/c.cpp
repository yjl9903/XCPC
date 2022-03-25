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
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 300000 + 5;

int n, k, a[maxn], pre[maxn], siz[maxn];
vector<int> vis[maxn], edge[maxn];

ll ans, cnt[maxn][2];
int col[maxn];
void dfs(int u) {
  cnt[u][col[u]] = 1;
  for (int x: edge[u]) {
    if (vis[x].size() == 1) continue;
    int i = u ^ vis[x][0] ^ vis[x][1];
    if (col[i] == -1) {
      col[i] = col[u] ^ !a[x];
      dfs(i);
    }
  }
}

int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}
void add(int u, ll s0, ll s1) {
  ans -= min(cnt[u][0], cnt[u][1]);
  cnt[u][0] = min(1ll * inf, cnt[u][0] + s0);
  cnt[u][1] = min(1ll * inf, cnt[u][1] + s1);
  ans += min(cnt[u][0], cnt[u][1]);
}
bool join(int x, int y) {
  x = find(x); y = find(y);
  if (x == y) return false;
  if (siz[x] > siz[y]) swap(x, y);
  add(y, cnt[x][0], cnt[x][1]);
  add(x, -cnt[x][0], -cnt[x][1]);
  pre[x] = y; siz[y] += siz[x];
  return true;
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    scanf("%1d", a + i);
  }
  for (int i = 1; i <= k; i++) {
    pre[i] = i; siz[i] = 1; col[i] = -1;
    int m, x; scanf("%d", &m);
    while (m--) {
      scanf("%d", &x);
      vis[x].push_back(i);
      edge[i].push_back(x);
    }
  }
  for (int i = 1; i <= k; i++) {
    if (col[i] != -1) continue;
    col[i] = 0; dfs(i);
  }
  for (int i = 1; i <= k; i++) {
    dbg(i, col[i], cnt[i][0], cnt[i][1]);
  }
  for (int i = 1; i <= n; i++) {
    if (vis[i].size() == 1) {
      int x = vis[i][0];
      dbg(x, col[x], a[i]);
      if (a[i] != col[x]) {
        add(find(x), inf, 0);
      } else {
        add(find(x), 0, inf);
      }
    } else if (vis[i].size() == 2) {
      join(vis[i][0], vis[i][1]);
    }
    printf("%I64d\n", ans);
  }
  return 0;
}