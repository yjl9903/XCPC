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
const int maxn = 1000000 + 5;

int n, le[maxn], ri[maxn];
vector<int> edge[maxn];

int tot, siz[maxn];
void getsz(int u, int f) {
  siz[u] = 1;
  for (int v: edge[u]) {
    if (v == f) continue;
    getsz(v, u);
    siz[u] += siz[v];
  }
}

void dfs(int u, int f, int beg, int sr) {
  int sz = (int)edge[u].size() - (u != 1);
  le[u] = beg;
  ri[u] = sr + sz + 1;
  int tot = ri[u] - 1, sum = 0;
  for (int v: edge[u]) {
    if (v == f) continue;
    dfs(v, u, tot, ri[u] + sum);
    tot--; sum += 2 * siz[v] - 1;
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 2; i <= n; i++) {
    int u, v; scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  getsz(1, 0);
  dfs(1, 0, 1, 1);
  for (int i = 1; i <= n; i++) printf("%d %d\n", le[i], ri[i]);
  return 0;
}