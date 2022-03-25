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

int n, k, a[maxn];
ll pre[maxn], suf[maxn];

int main() {
  scanf("%d%d", &n, &k);
  map<int,int> cnt;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    cnt[a[i]]++;
  }
  for (auto& x: cnt) {
    if (x.second >= k) {
      puts("0");
      return 0;
    }
  }
  sort(a + 1, a + 1 + n);
  for (int i = 1; i <= n; i++) {
    pre[i] = a[i] + pre[i - 1];
  }
  for (int i = n; i >= 1; i--) {
    suf[i] = suf[i + 1] + a[i];
  }
  auto qL = [&](int x) {
    int k = upper_bound(a + 1, a + 1 + n, x) - a - 1;
    return make_pair(k, 1ll * k * x - pre[k]);
  };
  auto qR = [&](int x) {
    int k = lower_bound(a + 1, a + 1 + n, x) - a;
    return make_pair(n - k + 1, suf[k] - 1ll * x * (n - k + 1));
  };
  ll ans = 1e18;
  for (auto& x: cnt) {
    auto a = qL(x.first - 1);
    auto b = qR(x.first + 1);
    if (a.first + x.second >= k) {
      ans = min(ans, a.second + k - x.second);
    }
    if (b.first + x.second >= k) {
      ans = min(ans, b.second + k - x.second);
    }
    ans = min(ans, a.second + b.second + k - x.second);
  }
  printf("%I64d\n", ans);
  return 0;
}