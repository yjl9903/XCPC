#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
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
using ull = unsigned long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int threshold = 10000000;
const int maxn = 500000 + 5;

ull k1, k2;
ull xorShift() {
  ull k3 = k1, k4 = k2;
  k1 = k4;
  k3 ^= (k3 << 23);
  k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
  return k2 + k4;
}

struct Ope {
  int dx, id, step;
};

int n, m, a[maxn], b[maxn], step[maxn];
ll res[maxn];
Ope ope[maxn];

int main() {
  while (scanf("%d%d%llu%llu", &n, &m, &k1, &k2) == 4) {
    set<PII> st[3];
    for (int i = 1; i <= n; i++) {
      a[i] = xorShift() % threshold + 1;
      b[i] = xorShift() % threshold + 1;
      step[i] = 0;
      st[0].emplace(a[i], i);
      st[1].emplace(a[i] + b[i], i);
      st[2].emplace(a[i] + b[i] + a[i], i);
    }

    auto nxt = [&](int step) -> Ope {
      if (step == 1) {
        if (st[0].empty()) return { -1, -1, -1 };
        auto it = st[0].end();
        it--;
        auto tot = Ope { it->first, it->second, 1 };
        st[0].erase(it);
        if ()
        return tot;
      } else if (step == 2) {

      } else if (step == 3) {

      }
      return { -1, -1, -1 };
    };

    ll ans = 0;
    for (int i = 1; i <= m; i++) {
      res[i] = 0;

      auto op1 = nxt(1);
      if (op1.dx != -1) {
        res[i] = res[i - 1] + op1.dx;
      }

      ans ^= res[i];
    }
    printf("%lld\n", ans);
  }
  return 0;
}