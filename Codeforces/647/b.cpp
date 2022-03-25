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
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 1e9 + 7;
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

int n, p, a[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &p);
    set<int> st;
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
      if (st.count(a[i])) {
        st.erase(a[i]);
      } else {
        st.insert(a[i]);
      }
    }
    if (p == 1 || st.empty()) {
      printf("%d\n", (int)st.size() % 2);
    } else {
      auto it = st.end(); it--;
      int ans = qpow(p, *it); st.erase(it);
      for (int x: st) {
        ans = sub(ans, qpow(p, x));
      }
      printf("%d\n", ans);
    }
  }
  return 0;
}