#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int maxn = 100000 + 5;

int n, deg[maxn];
vector<int> edge[maxn];

int fa[maxn], dep[maxn], mxd = -1;
void dfs(int u) {
  if (dep[u] > mxd) mxd = dep[u];
  for (int v: edge[u]) {
    dep[v] = dep[u] + 1;
    fa[v] = u;
    dfs(v);
  }
}

int siz[maxn];
void getsz(int u) {
  siz[u] = mxd == dep[u];
  for (int v: edge[u]) {
    getsz(v);
    siz[u] += siz[v];
  }
}

int cnt = 0;
void print(int u) {
  printf("%d%c", u - 1, " \n"[cnt == mxd]);
  cnt++;
  for (int v: edge[u]) {
    if (siz[v] > 0) {
      print(v);
      break;
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    int k;
    scanf("%d", &k);
    while (k--) {
      int x;
      scanf("%d", &x);
      x++;
      deg[x]++;
      edge[i].push_back(x);
    }
  }
  int rt = -1;
  for (int i = 1; i <= n; i++) {
    sort(edge[i].begin(), edge[i].end());
    if (deg[i] == 0) {
      assert(rt == -1);
      rt = i;
    }
  }
  assert(rt != -1);
  dfs(rt);
  getsz(rt);
  printf("%d\n", mxd + 1);
  assert(siz[rt] != 0);
  print(rt);
  return 0;
}