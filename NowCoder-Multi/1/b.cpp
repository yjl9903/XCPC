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



int main() {
  int r, a, b, h;
  scanf("%d%d%d%d", &r, &a, &b, &h);
  if (b > r + r) {
    puts("Drop");
  } else {
    puts("Stuck");
    double p = 1.0 * h / sqrt(1.0 * h * h + (a - b) * (a - b) / 4.0);
    double x = (1.0 * b * b + 4.0 * r * r - 4.0 * b * r * p) / (4.0 - 4.0 * p * p);
    // dbg(x, sqrt(x - b * b / 4.0));
    double ans = sqrt(x - b * b / 4.0);
    printf("%.10lf\n", ans);
  }
  return 0;
}