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

int n, m, b[maxn], pre[maxn], ord[maxn];
vector<int> edge[maxn];

int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      scanf("%d", b + i);
      pre[i] = i;
      ord[i] = i;
      edge[i].clear();
    }
    for (int i = 1; i <= m; i++) {
      int u, v; scanf("%d%d", &u, &v);
      edge[u].push_back(v);
      edge[v].push_back(u);
    }

  }
  return 0;
}