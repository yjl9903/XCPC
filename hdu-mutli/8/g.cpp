#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#include <numeric>
#include <string>
#include <map>
#include <set>
#include <random>
#include <ctime>
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

const int B = 1000;

mt19937 rnd(time(nullptr));

int n, a[maxn];
double f[maxn];

int main() {
  f[0] = 1.0;
  for (int i = 1; i < 105; i++) f[i] = f[i - 1] * i;
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    int g = -1;
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      if (g == -1) {
        g = a[i];
      } else {
        g = __gcd(g, a[i]);
      }
    }
    if (g > 1) {
      puts(n % 2 ? "1.000000" : "0.0000000");
      continue;
    }
    double fz = 0, fm = 0;
    for (int i = 0; i < B; i++) {
      vector<int> ord(n);
      iota(begin(ord), end(ord), 1);
      shuffle(begin(ord), end(ord), rnd);
      int g = a[ord[0]];
      if (g > 1) {
        for (int i = 1; i < n; i++) {
          int val = __gcd(g, a[ord[i]]);
          if (val == 1) {
            if (i % 2) {
              // ans += 1.0;
              fz += f[i];
              fm += f[i + 1];
            }
            break;
          } else {
            g = val;
          }
        }
      }
    }
    printf("%.6lf\n", fz / fm);
  }
  return 0;
}