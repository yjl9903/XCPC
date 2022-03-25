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
const int maxn = 1000000 + 5;

int n;
char s[maxn];

int main() {
  scanf("%d%s", &n, s + 1);
  int sum = 0;
  for (int i = 1; i <= n; i++) {
    if (s[i] == '(') sum++;
    else sum--;
  }
  if (sum) {
    return puts("-1"), 0;
  }
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    if (s[i] == '(') {
      sum++;
    } else {
      sum--;
      if (sum < 0) {
        i++;
        ans++;
        while (i <= n && sum < 0) {
          if (s[i] == '(') sum++;
          else sum--;
          i++; ans++;
        }
        i--;
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}