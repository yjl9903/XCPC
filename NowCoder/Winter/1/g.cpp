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

int n, k, cnt[maxn][26];
char s[maxn];

int main() {
  scanf("%d%d%s", &n, &k, s + 1);
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 26; j++) {
      cnt[i][j] += cnt[i - 1][j];
    }
    cnt[i][s[i] - 'a']++;
  }
  int ans = inf;
  for (int i = 1; i <= n; i++) {
    int l = i, r = n, tot = -1;
    auto check = [&](int x) {
      for (int j = 0; j < 26; j++) {
        if (cnt[x][j] - cnt[i - 1][j] >= k) {
          return true;
        }
      }
      return false;
    };
    while (l <= r) {
      int m = (l + r) / 2;
      if (check(m)) {
        tot = m; r = m - 1;
      } else {
        l = m + 1;
      }
    }
    if (tot != -1) {
      ans = min(ans, tot - i + 1);
    }
  }
  if (ans == inf) {
    puts("-1");
  } else {
    printf("%d\n", ans);
  }
  return 0;
}