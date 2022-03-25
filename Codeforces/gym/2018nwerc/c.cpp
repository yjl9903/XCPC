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
const double pi = acos(-1.0);

int n;
vector<int> edge[maxn];

double k = 0.0, step, x[maxn], y[maxn];

void dfs(int u, int f) {
  for (int v: edge[u]) {
    if (v == f) continue;
    x[v] = x[u] + cos(k);
    y[v] = y[u] + sin(k);
    k += step;
    dbg(k);
    dfs(v, u);
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 2; i <= n; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
  }
  step = pi / (n - 1);
  dfs(1, 0);
  for (int i = 1; i <= n; i++) {
    printf("%.8lf %.8lf\n", x[i], y[i]);
  }
  return 0;
}