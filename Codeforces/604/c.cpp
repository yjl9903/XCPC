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
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
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

int n, q, p[maxn], suf[maxn], sufs[maxn];

int main() {
  scanf("%d%d", &n, &q);
  const int iv = inv(100);
  for (int i = 1; i <= n; i++) {
    scanf("%d", p + i);
    p[i] = mul(p[i], iv);
  }
  suf[n + 1] = 1;
  for (int i = n; i >= 1; i--) {
    suf[i] = mul(suf[i + 1], p[i]);
    sufs[i] = add(sufs[i + 1], inv(suf[i]));
  }
  auto cal = [&](int l, int r) { // [l, r)
    return mul(sub(sufs[l], sufs[r]), suf[r]);
  };
  int ans = cal(1, n + 1);
  set<int> blk; 
  blk.insert(1); blk.insert(n + 1);
  while (q--) {
    int x; scanf("%d", &x);
    if (blk.count(x)) {
      auto it = blk.find(x);
      int l = *prev(it);
      int r = *next(it);
      ans = sub(ans, cal(l, x));
      ans = sub(ans, cal(x, r));
      ans = add(ans, cal(l, r));
      blk.erase(x);
    } else {
      blk.insert(x);
      auto it = blk.find(x);
      int l = *prev(it);
      int r = *next(it);
      ans = sub(ans, cal(l, r));
      ans = add(ans, cal(l, x));
      ans = add(ans, cal(x, r));
    }
    printf("%d\n", ans);
  }
  return 0;
}