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

inline int add(int x, int y) {
  x += y;
  return x >= mod ? x -= mod : x;
}
inline int sub(int x, int y) {
  x -= y;
  return x < 0 ? x += mod : x;
}
inline int mul(int x, int y) {
  return 1ll * x * y % mod;
}
inline int qpow(int x, ll n) {
  int r = 1;
  while (n > 0) {
    if (n & 1) r = 1ll * r * x % mod;
    n >>= 1; x = 1ll * x * x % mod;
  }
  return r;
}
inline int inv(int x) {
  return qpow(x, mod - 2);
}

int n, m, a[maxn], b[maxn];
vector<int> pos[maxn];

int main() {
  scanf("%d%d", &n, &m);
  vector<int> lsh;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    lsh.push_back(a[i]);
  }
  sort(begin(lsh), end(lsh));
  lsh.resize(unique(begin(lsh), end(lsh)) - begin(lsh));
  auto get = [&](int x) {
    return lower_bound(begin(lsh), end(lsh), x) - begin(lsh) + 1;
  };
  for (int i = 1; i <= n; i++) {
    a[i] = get(a[i]);
    pos[a[i]].push_back(i);
  }
  for (int i = 1; i <= m; i++) {
    scanf("%d", b + i);
    int rk = get(b[i]) - 1;
    if (rk >= (int)lsh.size() || lsh[rk] != b[i]) {
      puts("0");
      return 0;
    }
    b[i] = rk + 1;
  }
  if (b[1] > 1) {
    puts("0");
    return 0;
  }
  int R = pos[1].back() + 1, p = 2, ans = 1;
  for (int i = 2; i <= (int)lsh.size() && p <= m; i++) {
    assert(!pos[i].empty());
    // dbg(i, R);
    if (b[p] == i) {
      int last = pos[i].back();
      // dbg(b[p], last, R);
      if (R <= last) {
        ans = mul(ans, last - R + 1);
      } else {
        ans = 0; break;
      }
      p++;
    }
    R = max(R, pos[i].back() + 1);
  }
  printf("%d\n", ans);
  return 0;
}