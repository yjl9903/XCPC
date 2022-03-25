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

char s[maxn];

int main() {
  // puts("contest/171");
  // cin >> s;
  // int n = strlen(s);
  // for (int i = 2; i < n; i++) {
  //   int x = s[i - 2] - 'A';
  //   int y = s[i - 1] - 'A';
  //   dbg(x, s[i]);
  //   if ((x + y) % 26 != s[i] - 'A') {
  //     puts("NO");
  //     return 0;
  //   }
  // }
  // puts("YES");
  ll x;
  cin >> x;
  cout << (ll)((x + 8) / 9);
  return 0;
}