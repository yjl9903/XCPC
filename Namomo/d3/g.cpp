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

int n;
PII a[maxn];
ll pre[maxn], suf[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &a[i].first, &a[i].second);
  }
  sort(a + 1, a + 1 + n);
  int last = 0;
  for (int i = 1, j = 1; i <= n; i = j) {
    int y1 = inf, y2 = -inf;
    while (j <= n && a[j].first == a[i].first) {
      y1 = min(y1, a[j].second);
      y2 = max(y2, a[j].second);
      j++;
    }
    // if (i < n && a[i].first < a[i + 1].first) {
    //   pre[i] = 1ll * (x2 - x1) * (y2 - y1);
    // }
    ll area = i > 1 ? 1ll * (a[i].first - a[i - 1].first) * (y2 - y1 + last) : 0;
    for (int k = i; k < j; k++) {
      pre[k] = pre[i - 1] + area;
      dbg(k, pre[k]);
    }
    last = y2 - y1;
  }
  last = 0;
  ll ans = 1e18, sum = 0;
  for (int i = n, j = n; i >= 1; i = j) {
    int y1 = inf, y2 = -inf;
    while (j >= 1 && a[j].first == a[i].first) {
      y1 = min(y1, a[j].second);
      y2 = max(y2, a[j].second);
      j--;
    }
    // if (i < n && a[i].first < a[i + 1].first) {
    //   pre[i] = 1ll * (x2 - x1) * (y2 - y1);
    // }
    sum += i < n ? 1ll * (a[i + 1].first - a[i].first) * (y2 - y1 + last) : 0;
    dbg(j, sum);
    ans = min(ans, sum + pre[j]);
    last = y2 - y1;
  }
  printf("%lld\n", (ans + 1) / 2);
  return 0;
}