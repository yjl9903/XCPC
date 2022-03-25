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

int a, b, c, d;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d", &a, &b, &c, &d);
    int x, y, x1, y1, x2, y2;
    scanf("%d%d%d%d%d%d", &x, &y, &x1, &y1, &x2, &y2);
    int flag = 0;
    if (x1 == x2 && (a || b)) flag++;
    if (y1 == y2 && (c || d)) flag++;
    if (x - a + b < x1 || x - a + b > x2) flag++;
    if (y - c + d < y1 || y - c + d > y2) flag++;
    if (flag) puts("No");
    else puts("Yes");
  }  
  return 0;
}