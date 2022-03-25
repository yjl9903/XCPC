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
ll k, a[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%lld", &n, &k);
    for (int i = 1; i <= n; i++) {
      scanf("%lld", a + i);
    }
    sort(a + 1, a + 1 + n);
    ll g = a[2] - a[1];
    for (int i = 3; i <= n; i++) {
      g = __gcd(g, a[i] - a[i - 1]);
    }
    bool flag = false;
    k = (k % g + g) % g;
    for (int i = 1; i <= n; i++) {
      if ((a[i] % g + g) % g == k) {
        flag = true;
        break;
      }
    }
    puts(flag ? "YES" : "NO");
  }
  return 0;
}