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
const int maxn = 300000 + 5;

int n, k;
char s[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%s", &n, &k, s);
    bool ok = true;
    for (int i = k; i < n; i++) {
      if (s[i] != '?') {
        if (s[i % k] != '?' && s[i] != s[i % k]) {
          ok = false;
          break;
        }
        s[i % k] = s[i];
      }
    }
    int cnt[2] = { 0, 0 };
    for (int i = 0; i < k; i++) {
      if (s[i] != '?') {
        cnt[s[i] - '0']++;
      }
    }
    ok &= cnt[0] <= k / 2 && cnt[1] <= k / 2;
    puts(ok ? "YES" : "NO");
  }
  return 0;
}