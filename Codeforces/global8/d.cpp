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

int n, a[maxn], b[maxn], cnt[30];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    for (int j = 0; j < 22; j++) {
      if (a[i] & (1 << j)) {
        cnt[j]++;
      }
    }
  }
  for (int j = 0; j < 22; j++) {
    // dbg(j, cnt[j]);
    for (int i = 1; i <= cnt[j]; i++) {
      b[i] |= 1 << j;
    }
  }
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += 1ll * b[i] * b[i];
  }
  cout << ans << endl;
  return 0;
}