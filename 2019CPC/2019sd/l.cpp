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
const int maxn = 500 + 5;

int n, m, G[maxn][maxn];
vector<int> edge[maxn];

bool vis[maxn];
void dfs(int u) {
  if (vis[u]) return ;
  vis[u] = true;
  for (int v: edge[u]) {
    dfs(v);
    G[u][v] = 1;
    for (int i = 1; i <= n; i++) {
      G[u][i] |= G[v][i];
    }
  }
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      edge[i].clear();
      vis[i] = false;
      for (int j = 1; j <= n; j++) {
        G[i][j] = 0;
      }
    }
    bool flag = true;
    for (int i = 1; i <= m; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      if (u == v) {
        flag = false;
      }
      edge[u].push_back(v);
    }
    for (int i = 1; i <= n; i++) {
      if (vis[i]) continue;
      dfs(i);
    }
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (i == j) continue;
        if (G[i][j] && G[j][i]) {
          flag = false;
        }
      }
    }
    if (flag) {
      for (int i = 1; i <= n; i++) {
        int L = 0, R = 0;
        for (int j = 1; j <= n; j++) {
          if (i == j) continue;
          if (G[i][j]) {
            L++;
          } else if (G[j][i]) {
            R++;
          }
        }
        if (L < (n + 1) / 2 && R < (n + 1) / 2) {
          putchar('1');
        } else {
          putchar('0');
        }
      }
      puts("");
    } else {
      for (int i = 1; i <= n; i++) {
        putchar('0');
      }
      puts("");
    }
  }
  return 0;
}