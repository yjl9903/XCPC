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
const ll inf = 1ll << 60;
const int maxn = 500000 + 5;

int n, a[maxn], b[maxn], pos[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    if (i > 1 && a[i] == a[i - 1]) pos[i] = pos[i - 1];
    else pos[i] = i;
  }
  sort(a + 1, a + 1 + n);
  ll ans = -inf;
  for (int i = 7; i <= n; i++) {
    if (a[i - 1] + a[i - 2] < a[i - 3] + a[i - 4] + a[i - 5] + a[i - 6]) {
      ll sum = a[i - 1] + a[i - 2] + a[i - 3] + a[i - 4] + a[i - 5] + a[i - 6];
      int id = lower_bound(a + 1, a + 1 + n, a[i - 1] + a[i - 2]) - a - 1;
      dbg(i, id);
      if (i <= id) {
        sum += a[id];
        ans = max(ans, sum);
      }
    }
  }
  for (int i = 5; i + 2 <= n; i++) {
    int id = lower_bound(a + 1, a + 1 + n, a[i - 1] + a[i - 2] + a[i - 3] + a[i - 4] - a[i]) - a - 1;
    dbg(i, id);
    if (id == n) {
      id--;
    }
    if (id > i) {
      id = max(pos[id], i + 1);
      int id2 = lower_bound(a + 1, a + 1 + n, a[id] + a[i]) - a - 1;
      if (id2 > id) {
        ans = max(ans, 1ll * a[i - 1] + a[i - 2] + a[i - 3] + a[i - 4] + a[i] + a[id] + a[id2]);
      }
    }
  }
  if (ans == -inf) {
    puts("-1");
  } else {
    printf("%lld\n", ans);
  }
  return 0;
}