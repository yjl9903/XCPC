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
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int x, n, s, L, R;

int cal(int L, int R) {
  if (x % n == 0) {
    if (L <= s && s <= R) {
      return 0;
    } else {
      return inf;
    }
  }
  int g = __gcd(x, n);
  int tag = s % g;
  // int pos = s;
  // for (int i = 0; i < n / g; i++) {
  //   if (L <= pos && pos <= R) {
  //     return i;
  //   }
  //   pos = (pos + x) % n;
  // }
  int st = L % g, ed = R % g;
  if (R - L + 1 < g) {
    if (st <= ed) {
      if (st <= tag && tag <= ed) {
        
      } else {
        return inf;
      }
    }
  } else {

  }
  return inf;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d%d%d%d", &x, &n, &s, &L, &R);
    int ans = inf;
    if (L <= R) {
      ans = cal(L, R);
    } else {
      ans = min(cal(L, n - 1), cal(0, R));
    }
    if (ans == inf) {
      puts("-1");
    } else {
      printf("%d\n", ans);
    }
  }
  return 0;
}