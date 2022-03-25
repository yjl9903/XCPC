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

int n, m, a[maxn], cnt[maxn], ans[maxn];

int qpow(int x, ll n, int mod) {
  int r = 1;
  while (n > 0) {
    if (n & 1) r = 1ll * r * x % mod;
    n >>= 1; x = 1ll * x * x % mod;
  }
  return r;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  sort(a + 1, a + 1 + n);
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < m; j++) {
      ans[j] += cnt[(a[i] + m - j) % m];
    }
    cnt[a[i] % m]++;
  }
  if (ans[0]) {
    puts("0"); return 0;
  }
  int r = 1;
  for (int j = 1; j < m; j++) {
    r = 1ll * r * qpow(j, ans[j], m) % m;
  }
  printf("%d\n", r);
  return 0;
}