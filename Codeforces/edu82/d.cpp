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
const int maxn = 100000 + 5;

ll n;
int m, a[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    ll ans = 0, sum = 0;
    vector<ll> cnt(63, 0);
    scanf("%I64d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
      scanf("%d", a + i);
      sum += a[i];
      cnt[__builtin_ctz(a[i])]++;
    }
    if (sum < n) {
      puts("-1"); continue;
    }
    for (int i = 0; i < 62; i++) {
      if (n >> i & 1) {
        if (!cnt[i]) {
          for (int j = i + 1; j < 62; j++) {
            if (cnt[j]) {
              for (int k = j; k > i; k--) {
                cnt[k]--; ans++;
                cnt[k - 1] += 2;
              }
              break;
            }
          }
        }
        cnt[i]--;
      }
      cnt[i + 1] += cnt[i] / 2;
    }
    printf("%I64d\n", ans);
  }
  return 0;
}