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

int h, c, t;

bool check(ll k) {
  dbg(1ll * h * (k + 1) + 1ll * c * k, 1ll * t * (k + k + 1));
  return 1ll * h * (k + 1) + 1ll * c * k <= 1ll * t * (k + k + 1);
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d", &h, &c, &t);
    if (t + t == h + c) {
      printf("%d\n", 2);
    } else {
      vector< pair<double,int> > vec = {
        { abs(1.0 * (h + c) / 2.0 - t), 2 }
      };
      auto push = [&](int k) {
        if (k < 0) return ;
        double ans = (1.0 * (k + 1) * h + 1.0 * k * c) / (k + k + 1);
        vec.push_back({ abs(ans - t), k + k + 1 });
      };
      int mid = (h - t) / abs(t + t - h - c);
      for (int i = mid - 10; i <= mid + 10; i++) {
        push(i);
      }
      sort(begin(vec), end(vec));
      printf("%d\n", vec.front().second);
    }
  }
  return 0;
}