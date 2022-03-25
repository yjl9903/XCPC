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
const int maxn = 500000 + 5;

bool check(char c) {
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

char s[maxn];
int n;

int main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  ll ans = 0;
  for (int st = 1; st <= 2; st++) {
    for (int i = st, j = st; i + 1 <= n; ) {
      if (!check(s[i]) && check(s[i + 1])) {
        while (j + 1 <= n && !check(s[j]) && check(s[j + 1])
          && s[j] == s[i] && s[j + 1] == s[i + 1]) {
          j += 2;
        }
        int len = (j - i) / 2;
        if (i > 2 && !check(s[i - 2]) && check(s[i - 1])) len++;
        dbg(i, j, len);
        ll tot = 1ll * len * (len + 1) / 2 - (len + len - 1);
        ans += max(tot, 0ll);
        i = j;
      } else {
        i += 2;
        j += 2;
      }
    }
  }
  cout << ans << endl;
  return 0;
}