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
#include <unordered_map>
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
char s[maxn];

int f(char c) {
  if (c >= 'a' && c <= 'z') {
    return c - 'a';
  } else {
    return c - 'A' + 26;
  }
}

int main() {
  scanf("%d%s", &n, s + 1);
  unordered_map<ll,int> mp;
  mp[0] = 1;
  ll ans = 0, state = 0;
  for (int i = 1; i <= n; i++) {
    state ^= 1ll << f(s[i]);
    if (mp.count(state)) {
      ans += mp[state];
    }
    for (int c = 0; c < 52; c++) {
      if (mp.count(state ^ (1ll << c))) {
        ans += mp[state ^ (1ll << c)];
      }
    }
    mp[state]++;
  }
  printf("%lld\n", ans);
  return 0;
}