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
const int maxn = 500000 + 5;

int n, h[maxn], ans[maxn];

double cal(int x, int y) {
  return h[y] - h[x] + sqrt(abs(x - y));
}

void dfs(int l, int r, int L, int R) {
  if (l > r || L > R) return ;
  int pos = l;
  int m = (l + r) / 2;
  dbg(l, r, m);
  for (int i = L; i <= m && i <= R; i++) {
    if (cal(m, i) > cal(m, pos)) {
      pos = i;
    }
  }
  ans[m] = max(ans[m], (int)ceil(cal(m, pos)));
  dfs(l, m - 1, L, pos);
  dfs(m + 1, r, pos, R);
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", h + i);
  }
  dfs(1, n, 1, n);
  reverse(h + 1, h + n + 1);
  reverse(ans + 1, ans + n + 1);
  dfs(1, n, 1, n);
  for (int i = n; i >= 1; i--) {
    printf("%d\n", ans[i]);
  }
  return 0;
}