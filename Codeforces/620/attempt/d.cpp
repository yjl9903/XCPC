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
const int maxn = 100000 + 5;

int n, ans[maxn];
char s[maxn];

void solvea() {
  ans[1] = 1;
  if (s[1] == '<') ans[2] = 2;
  else ans[2] = 0;
  for (int i = 1, j; i < n;) {
    j = i;
    while (j < n && s[j] == s[i]) j++;
    for (int k = i + 1; k < j; k++) {
      if (s[i] == '<') {
        ans[k + 1] = ans[k] + 1;
      } else {
        ans[k + 1] = ans[k] - 1;
      }
    }
    if (s[i] == '<') {
      ans[j + 1] = ans[i] - 1;
    } else {
      ans[j + 1] = ans[i] + 1;
    }
    i = j;
  }
  int mn = ans[1];
  for (int i = 2; i <= n; i++) mn = min(ans[i], mn);
  mn = 1 - mn;
  for (int i = 1; i <= n; i++) {
    printf("%d ", ans[i] + mn);
  }
  puts("");
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%s", &n, s + 1);
    solvea();
  }
  return 0;
}