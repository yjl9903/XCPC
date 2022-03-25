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
#ifdef XLor
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, a[maxn], siz[maxn];
vector<PII> edge[maxn];
ll ans[maxn], sum[maxn], sumd[maxn], sume[maxn];

void predfs(int u, int f) {
  sum[u] = a[u];
  siz[u] = 1;
  for (auto& x: edge[u]) {
    int v = x.first;
    if (v == f) continue;
    predfs(v, u);
    sum[u] += sum[v];
    siz[u] += siz[v];
    sumd[u] += x.second * siz[v] + sumd[v];
    sume[u] += x.second * sum[v] + sume[v];
  }
}

ll s1 = 0, s2 = 0;
void dfs(int u, int f) {
  ans[u] = a[u] * s1 + s2;
  for (auto& x: edge[u]) {
    int v = x.first;
    if (v == f) continue;

    s1 -= x.second * siz[v];
    s1 += x.second * (n - siz[v]);
    s2 -= x.second * sum[v];
    s2 += x.second * (sum[1] - sum[v]);

    dfs(v, u);

    s1 += x.second * siz[v];
    s1 -= x.second * (n - siz[v]);
    s2 += x.second * sum[v];
    s2 -= x.second * (sum[1] - sum[v]);
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  for (int i = 2, u, v, w; i <= n; i++) {
    scanf("%d%d%d", &u, &v, &w);
    edge[u].emplace_back(v, w);
    edge[v].emplace_back(u, w);
  }
  predfs(1, 0);
  s1 = sumd[1];
  s2 = sume[1];
  dfs(1, 0);
  for (int i = 1; i <= n; i++) {
    printf("%I64d\n", ans[i]);
  }
  return 0;
}