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

int n, cnt[maxn], f[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    ms(f, 0);
    ms(cnt, 0);
    for (int i = 1; i <= n; i++) {
      int x;
      scanf("%d", &x);
      cnt[x]++;
    }
    int ans = 0;
    for (int i = 1; i < maxn; i++) {
      f[i] = max(f[i], cnt[i]);
      for (int j = i + i; j < maxn; j += i) {
        f[j] = max(f[j], f[i] + cnt[j]);
      }
    }
    for (int i = 1; i < maxn; i++) {
      ans = max(ans, f[i]);
    }
    printf("%d\n", n - ans);
  }
  return 0;
}