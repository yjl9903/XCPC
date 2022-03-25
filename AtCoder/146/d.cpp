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
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, k, ans[maxn], col[maxn];
vector<PII> edge[maxn];

void dfs(int u, int f) {
  int c = 0;
  for (auto& x: edge[u]) {
    int v = x.first, id = x.second;
    if (v == f) continue;
    c++; if (c == col[u]) c++;
    col[v] = c; ans[id] = c;
    dfs(v, u);
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].emplace_back(v, i);
    edge[v].emplace_back(u, i);
  }
  for (int i = 1; i <= n; i++) {
    k = max(k, (int)edge[i].size());
  }
  dfs(1, 0);
  printf("%d\n", k);
  for (int i = 2; i <= n; i++) {
    printf("%d\n", ans[i]);
  }
  return 0;
}