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

int n;

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    int x = n;
    ll ans = 1e18;
    int a = -1, b = -1;
    for (int i = 2; 1ll * i * i <= x; i++) {
      if (x % i) continue;
      while (x % i == 0) x /= i;
      if (1ll * n / i * (i - 1) < ans) {
        ans = 1ll * n / i * (i - 1);
        a = n / i;
        b = n / i * (i - 1);
      }
    }
    if (x > 1) {
      if (1ll * n / x * (x - 1) < ans) {
        ans = 1ll * n / x * (x - 1);
        a = n / x;
        b = n / x * (x - 1);
      }
    }
    printf("%d %d\n", a, b);
  }
  return 0;
}