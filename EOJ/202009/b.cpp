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

int n, k, deg[maxn];
vector<int> edge[maxn], bag[maxn];

int main() {
  scanf("%d%d", &n, &k);
  if (n == 2) {
    printf("%d\n", k);
    return 0;
  }
  for (int i = 2; i <= n; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
    deg[u]++;
    deg[v]++;
  }
  for (int i = 1; i <= n; i++) {
    if (deg[i] == 1) {
      bag[1].push_back(i);
    }
  }
  int ans = 0, tot = 1;
  while (k >= 2) {
    k -= 2;
    for (auto& u: bag[tot]) {
      ans++;
      deg[u] = -1;
      for (auto& v: edge[u]) {
        deg[v]--;
        if (deg[v] == 1) {
          bag[tot + 1].push_back(v);
        }
      }
    }
    tot++;
  }
  printf("%d\n", ans + k <= n ? ans + k : ans);
  return 0;
}