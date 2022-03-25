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
const int maxn = 500000 + 5;

int n, q, rt;
vector<int> edge[maxn];

namespace hld {
  int st[maxn], ed[maxn], dep[maxn];
  int euler[maxn * 2], cnt;
  int dp[21][maxn * 2];
  void dfs(int u, int f) {
    euler[++cnt] = u;
    st[u] = cnt;
    for (int v: edge[u]) {
      if (v == f) continue;
      dep[v] = dep[u] + 1;
      dfs(v, u);
      euler[++cnt] = u;
    }
    ed[u] = cnt;
  }
  void build(int rt = 1) {
    dep[rt] = 0;
    cnt = 0;
    dfs(rt, 0);
    for (int i = 1; i <= cnt; i++) {
      dp[0][i] = euler[i];
    }
    for (int j = 1; j < 21; j++) {
      for (int i = 1; i + (1 << j) <= cnt + 1; i++) {
        int l = dp[j - 1][i];
        int r = dp[j - 1][i + (1 << (j - 1))];
        if (dep[l] < dep[r]) {
          dp[j][i] = l;
        } else {
          dp[j][i] = r;
        }
      }
    }
  }
  int qlca(int u, int v) {
    int l = st[u], r = st[v];
    if (l > r) swap(l, r);
    int k = __lg(r - l + 1);
    int x = dp[k][l], y = dp[k][r - (1 << k) + 1];
    if (dep[x] < dep[y]) {
      return x;
    } else {
      return y;
    }
  }
  int qdis(int u, int v) {
    return dep[u] + dep[v] - 2 * dep[qlca(u, v)];
  }
}

int main() {
  scanf("%d%d%d", &n, &q, &rt);
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  hld::build(rt);
  // cout << "!" << endl;
  while (q--) {
    int x, y;
    scanf("%d%d", &x, &y);
    printf("%d\n", hld::qlca(x, y));
  }
  return 0;
}