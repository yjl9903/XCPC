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

int n, k, b[maxn], a[maxn];

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < 6; i++) {
    scanf("%d", b + i);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    a[i]--;
  }
  int ans = 0;
  for (int s = 1; s < 64; s++) {
    int cnt = 0;
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
      if (s >> a[i] & 1) {
        if (sum + b[a[i]] <= k) {
          sum += b[a[i]];
          cnt++;
        }
      }
    }
    ans = max(ans, cnt);
  }
  printf("%d\n", ans);
  return 0;
}