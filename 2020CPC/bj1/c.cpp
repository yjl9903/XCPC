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

int n;
char s[maxn];

int main() {
  scanf("%s", s + 1);
  n = strlen(s + 1);
  int ans = 0, len = 0;
  for (int i = 1; i <= n + 1; i++) {
    if (i <= n && s[i] == 'w') {
      ans++;
      len++;
    } else {
      ans += len - 1;
      len = 0;
    }
  }
  printf("%d\n", ans);
  return 0;
}