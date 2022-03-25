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

int n, a[maxn], b[maxn], c[maxn];
vector<int> edge[maxn];

ll dp[maxn];
PII dfs(int u, int f) {
  PII cnt = { 0, 0 };
  if (b[u] != c[u]) {
    if (b[u] == 0) {
      cnt.first = 1;
    } else {
      cnt.second = 1;
    }
  }
  for (int v: edge[u]) {
    if (v == f) continue;
    a[v] = min(a[v], a[u]);
    auto tot = dfs(v, u);
    cnt.first += tot.first;
    cnt.second += tot.second;
    dp[u] += dp[v];
  }
  int x = min(cnt.first, cnt.second);
  dp[u] += 2ll * a[u] * x;
  cnt.first -= x;
  cnt.second -= x;
  return cnt;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d%d", a + i, b + i, c + i);  
  }
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  auto res = dfs(1, 0);
  if (res.first || res.second) {
    puts("-1");
  } else {
    printf("%I64d\n", dp[1]);
  }
  return 0;
}