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

char s[maxn], t[maxn];
int n, m, fail[maxn];

int main() {
  while (scanf("%s%s",s, t) == 2) {
    n = strlen(s);
    m = strlen(t);
    int ans = 0, len = n + m - __gcd(n, m);
    for (int i = 0; i < len; i++) {
      if (s[i % n] < t[i % m]) {
        ans = -1; break;
      } else if (s[i % n] > t[i % m]) {
        ans = 1; break;
      }
    }
    if (ans == -1) puts("<");
    else if (ans == 0) puts("=");
    else puts(">");
  }
  return 0;
}