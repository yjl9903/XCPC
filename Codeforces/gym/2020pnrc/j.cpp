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
const int maxn = 200000 + 5;

const double eps = 1e-10;
const double pi = acos(-1.0);

int n;

struct Seg {
  double pos, k, b;

  bool operator<(const Seg& b) const {
    return pos < b.pos;
  }
};

vector<Seg> evs;

void push(double L, double R, double k, double b) {
  dbg(L, R, k, b);
  evs.push_back({ L, k, b });
  evs.push_back({ R - eps, -k, -b });
}

int main() {
  scanf("%d", &n);
  double sum = 0;
  for (int i = 1; i <= n; i++) {
    dbg(i);
    double t, s, a;
    scanf("%lf%lf%lf", &t, &s, &a);

    if (abs(s) <= eps) {
      sum += t;
      continue;
    }

    double len = pi;
    if (t < s * pi) {
      len = t / s;
    }

    if (a + len <= 2.0 * pi) {
      // [a, a + len]
      push(a, a + len, -s, t + s * a);
    } else {
      // [a, 2pi]
      push(a, 2.0 * pi, -s, t + s * a);
      // [0, (a+len) - 2pi]
      push(0, a + len - 2.0 * pi, -s, t + s * a - 2.0 * pi * s);
    }

    if (a - len >= 0) {
      // [a - len, a]
      push(a - len, a, s, t - s * a);
    } else {
      // [0, a]
      push(0, a, s, t - s * a);
      // [2pi-(len-a), 2pi]
      push(2.0 * pi - len + a, 2.0 * pi, s, t - s * a - 2.0 * pi * s);
    }
  }
  sort(begin(evs), end(evs));
  double k = 0, b = 0;
  double ans = 0;
  for (auto x: evs) {
    k += x.k;
    b += x.b;
    ans = max(ans, k * x.pos + b);
  }
  printf("%.8lf\n", ans + sum);
  return 0;
}