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
#include <random>
#include <ctime>
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

int n, p[maxn], ans = 0;
vector<int> edge[maxn];

int dp[maxn][2];
void predfs(int u, int f) {
  dp[u][0] = dp[u][1] = 0;
  for (int v: edge[u]) {
    if (v == f) continue;
    predfs(v, u);
    dp[u][0] = max(dp[u][0], dp[v][1]);
    dp[u][1] = max(dp[u][1], max(dp[v][0], dp[v][1]));
  }
  dp[u][0]++;
  dp[u][1] += (int)edge[u].size() - (u != 1 ? 1 : 0) - 1;
  ans = max(ans, dp[u][1]);
}

int main() {
  scanf("%d", &n);
  for (int i = 2, u, v; i <= n; i++) {
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  for (int i = 1; i <= n; i++) p[i] = i;
  clock_t start = clock();
  shuffle(p + 1, p + 1 + n, mt19937(time(nullptr)));
  for (int i = 1; i <= n && (double)(clock() - start) / CLOCKS_PER_SEC < 0.9; i++) {
    predfs(p[i], 0);
  }
  printf("%d\n", ans);
  return 0;
}