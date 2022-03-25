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

int n, q, k, L, pcnt = 1, tot;
char s[maxn];

int ch[maxn][26], match[maxn], fa[20][maxn], dfn[maxn], dep[maxn];
int insert(char s[], int id) {
  int u = 1;
  for (int i = 0; s[i]; i++) {
    int c = s[i] - 'a';
    if (!ch[u][c]) {
      ch[u][c] = ++pcnt;
    }
    u = ch[u][c];
  }
  match[id] = u;
  return u;
}

void getdep(int u, int f) {
  fa[0][u] = f;
  for (int i = 1; i < 20; i++) {
    fa[i][u] = fa[i - 1][fa[i - 1][u]];
  }
  dfn[u] = ++tot;
  dep[u] = dep[f] + 1;
  for (int i = 0; i < 26; i++) {
    int v = ch[u][i];
    if (v) {
      getdep(v, u);
    }
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

int ans, key[maxn], siz[maxn];
vector<int> edge[maxn];
namespace VT {
  const int rt = 1;
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

void dfs(int u) {
  siz[u] = key[u];
  for (int v: edge[u]) {
    dfs(v);
    siz[u] += siz[v];
    if (siz[v] == L) {
      ans += dep[v] - dep[u];
    }
  }
}

int main() {
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; i++) {
    scanf("%s", s);
    insert(s, i);
  }
  getdep(1, 0);
  for (int i = 1; i <= q; i++) {
    scanf("%d%d", &k, &L);
    vector<int> vec;
    for (int j = 1, x; j <= k; j++) {
      scanf("%d", &x);
      x = match[x];
      key[x] = 1;
      vec.push_back(x);
    }
    VT::build(vec);
    ans = 0; dfs(1);
    printf("%d\n", ans);
    for (int x: vec) key[x] = 0;
  }
  return 0;
}