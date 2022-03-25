#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <map>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, tot, flag, ans;
char s[maxn];
int ch[maxn][26], val[maxn], key[maxn];
bool vis[maxn];

int node() {
  tot++;
  ms(ch[tot], 0);
  val[tot] = key[tot] = -1;
  vis[tot] = false;
  return tot;
}

namespace LCA {
  int fa[maxn][20], dep[maxn];
  void dfs(int u, int f) {
    fa[u][0] = f;
    dep[u] = dep[f] + 1;
    for (int j = 1; j < 20; j++) {
      fa[u][j] = fa[fa[u][j - 1]][j - 1];
    }
    for (int c = 0; c < 26; c++) {
      int v = ch[u][c];
      if (v) {
        dfs(v, u);
      }
    }
  }

  void build() {
    dfs(1, 0);
  }

  int qlca(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    int tmp = dep[x] - dep[y];
    for (int i = 0; tmp; i++, tmp >>= 1)
      if (tmp & 1) x = fa[x][i];
    if (x == y) return x;
    for (int i = 19; i >= 0; i--) {
      if (fa[x][i] != fa[y][i]) {
        x = fa[x][i];
        y = fa[y][i];
      }
    }
    return fa[x][0];
  }
}

int dfs(int u) {
  if (!flag) return 0;

  int sum = 0, one = -1;
  for (int c = 0; c < 26; c++) {
    int v = ch[u][c];
    if (v) {
      int r = dfs(v);
      if (r) {
        sum += r;
        if (r == 1 && one == -1) {
          one = v;
        }
      }
    }
  }

  if (key[u] == -1) {
    if (sum == 0) {
      return 0;
    } else {
      if (one == -1) {
        vis[u] = true;
        return sum + 1;
      } else {
        assert(vis[one] && key[one] != -1);
        vis[u] = true;
        key[u] = key[one];
        vis[one] = false;
        key[one] = -1;
        return sum;
      }
    }
  } else {
    vis[u] = true;
    return sum + 1;
  }
}

void check(int u, int r = -1) {
  if (!flag) return ;
  if (vis[u]) r = key[u];
  if (val[u] != -1) {
    if (val[u] != r) {
      flag = false;
      return ;
    }
  }
  for (int c = 0; c < 26; c++) {
    int v = ch[u][c];
    if (v) {
      check(v, r);
    }
  }
}

int main() {
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    ans = tot = 0;
    flag = true;
    node();

    scanf("%d", &n);
    map<int,vector<int> > bag;
    for (int i = 1, x; i <= n; i++) {
      scanf("%s%d", s, &x);
      int u = 1;
      for (int j = 0; s[j]; j++) {
        int& nx = ch[u][s[j] - 'a'];
        if (!nx) {
          nx = node();
        }
        u = nx;
      }
      bag[x].push_back(u);
      if (val[u] == -1) {
        val[u] = x;
      } else if (val[u] != x) {
        flag = false;
      }
    }

    if (flag) {
      LCA::build();
      for (auto& x: bag) {
        auto& vec = x.second;
        int g = vec[0];
        for (int i = 1; i < (int)vec.size(); i++) {
          g = LCA::qlca(g, vec[i]);
        }
        if (key[g] == -1) {
          key[g] = x.first;
        } else {
          flag = false;
          break;
        }
      }
      ans = dfs(1);
      check(1);
    }

    printf("Case #%d: ", ++kase);
    if (flag) {
      printf("%d\n", ans);
    } else {
      puts("-1");
    }
  }
  return 0;
}