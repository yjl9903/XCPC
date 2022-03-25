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
const int inf = 24 * 60;
const int maxn = 200000 + 5;

struct Line {
  int l, r, id;
} a[maxn];

int n;

int main() {
  int T, kase = 0; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d%d", &a[i].l, &a[i].r);
      a[i].id = i;
    }
    sort(a + 1, a + 1 + n, [](Line a, Line b) {
      if (a.l == b.l) return a.r < b.r;
      return a.l < b.l;
    });
    string ans(n, ' ');
    int la = -1, lb = -1, flag = true;
    for (int i = 1; i <= n; i++) {
      if (a[i].l >= la) {
        ans[a[i].id - 1] = 'C';
        la = a[i].r;
      } else if (a[i].l >= lb) {
        ans[a[i].id - 1] = 'J';
        lb = a[i].r;
      } else {
        flag = false;
      }
    }
    printf("Case #%d: ", ++kase);
    if (flag) {
      puts(ans.c_str());
    } else {
      puts("IMPOSSIBLE");
    }
  }
  return 0;
}