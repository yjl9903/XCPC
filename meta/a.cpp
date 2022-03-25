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

int n, x, a[maxn];
int suf[maxn];

int main() {
  while (scanf("%d%d", &n, &x) == 2) {
    for (int i = 1; i <= n; i++) {
      scanf("%d", a + i);
    }
    suf[n] = a[n];
    for (int i = n - 1; i >= 1; i--) {
      suf[i] = max(suf[i + 1], a[i]);
    }
    ll p = a[n], q = a[1];
    for (int i = 1; i < n; i++) {
      if (1ll * p * a[i] < 1ll * q * suf[i + 1]) {
        p = suf[i + 1]; 
        q = a[i];
      }
    }
    p *= x;
    ll g = __gcd(p, q);
    printf("%lld/%lld\n", p / g, q / g);
  }
  return 0;
}