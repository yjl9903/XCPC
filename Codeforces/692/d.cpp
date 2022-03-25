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

int n, a[maxn], cnt[maxn];
ll T;
char s[maxn];

int main() {
  scanf("%d%lld%s", &n, &T, s + 1);
  for (int i = 1; i <= n; i++) {
    a[i] = 1 << (s[i] - 'a');
    if (i == n) {
      T -= a[i];
    } else {
      T += a[i];
    }
  }
  if (T < 0) {
    puts("No");
    return 0;
  }
  for (int i = 1; i <= n - 2; i++) {
    cnt[s[i] - 'a' + 1]++;
  }
  ll need = 0;
  for (int i = 60; i >= 0; i--) {
    if (T >> i & 1) {
      need++;
    }
    need = max(need - cnt[i], 0ll);
    need <<= 1;
  }
  if (need == 0ll) {
    puts("Yes");
  } else {
    puts("No");
  }
  return 0;
}