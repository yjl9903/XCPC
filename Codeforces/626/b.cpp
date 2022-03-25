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
const int maxn = 400000 + 5;
const int maxv = (1 << 26) + 5;

int n, a[maxn];

bool b[maxv];
void update(int i, int x) {
  for (i++; i < maxv; i += i & -i) b[i] ^= x;
}
int query(int i) {
  int r = 0;
  for (i++; i > 0; i -= i & -i) r ^= b[i];
  return r;
}
int query(int l, int r) {
  return query(r) ^ query(l - 1);
}

int cal(int p) {
  int ans = 0;
  int l = 1 << p;
  int r = (1 << (p + 1)) - 1;
  for (int i = 1; i <= n; i++) {
    int tot = a[i] & r;
    if (a[i] & (1 << p)) {
      ans ^= query(0, r - tot);
      ans ^= query(1 + l + r - tot, r);
    } else {
      ans ^= query(l - tot, r - tot);
    }
    update(tot, 1);
  }
  for (int i = 1; i <= n; i++) {
    update(a[i] & r, 1);
  }
  return ans;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  int ans = 0;
  for (int i = 0; i < 25; i++) {
    if (cal(i)) {
      ans += 1 << i;
    }
  }
  printf("%d\n", ans);
  return 0;
}