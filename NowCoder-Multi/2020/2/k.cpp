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

const int Turn = 500;
const double pi = acos(-1.0);
const double eps = 1e-8;

inline double sqr(double x) { return x * x; }

int r1, r2, r3;
double Sin[Turn + 5], Cos[Turn + 5];

int main() {
  for (int i = 0; i <= Turn; i++) {
    Sin[i] = sin(2.0 * i * pi / Turn);
    Cos[i] = cos(2.0 * i * pi / Turn);
  }
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &r1, &r2, &r3);

    if (r1 > r2) swap(r1, r2);
    if (r2 > r3) swap(r2, r3);
    if (r1 > r2) swap(r1, r2);
    assert(r1 <= r2 && r2 <= r3);

    double ans = 0;
    for (int i = 0; i < Turn; i++) {
      double X = r2 * Cos[i], Y = r2 * Sin[i];
      double L = sqrt(sqr(X - r1) + sqr(Y));
      if (L < eps) continue;
      double H = r1 * Y / L;
      if (H >= r3) {
        ans += H * L / 2.0;
      } else {
        double alpha = asin(H / r3);
        double E = 2.0 * (H * alpha + sqrt(sqr(r3) - sqr(H)));
        ans += E * L;
      }
    }
    ans /= 2 * pi * Turn;
    printf("%.1lf\n", ans);
  }
  return 0;
}