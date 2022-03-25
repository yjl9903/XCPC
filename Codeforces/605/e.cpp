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
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, a[maxn], dfn[maxn];
int dis[maxn][2], ans[maxn];

void dfs(int u) {
  if (dfn[u] == 10) return ;
  dfn[u]++;
  if (u - a[u] >= 1) {
    int y = a[u - a[u]] % 2;
    dis[u][y] = 1;
    dfs(u - a[u]);
    if (dis[u - a[u]][y ^ 1] != -1) {
      int nd = dis[u - a[u]][y ^ 1] + 1;
      if (dis[u][y ^ 1] == -1 || dis[u][y ^ 1] < nd) {
        dis[u][y ^ 1] = nd;
      }
    }
  }
  if (u + a[u] <= n) {
    int y = a[u + a[u]] % 2;
    dis[u][y] = 1;
    dfs(u + a[u]);
    if (dis[u + a[u]][y ^ 1] != -1) {
      int nd = dis[u + a[u]][y ^ 1] + 1;
      if (dis[u][y ^ 1] == -1 || dis[u][y ^ 1] < nd) {
        dis[u][y ^ 1] = nd;
      }
    }
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    dis[i][0] = dis[i][1] = -1;
  }
  for (int i = 1; i <= n; i++) {
    while (dfn[i] < 10) dfs(i);
  }
  for (int i = 1; i <= n; i++) {
    // dbg(i, a[i], dis[i][0], dis[i][1]);
    printf("%d ", dis[i][(a[i] % 2) ^ 1]);
  }
  return 0;
}