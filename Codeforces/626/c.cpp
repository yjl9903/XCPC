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
#include <random>
#include <ctime>
#include <map>
#include <set>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using ull = unsigned long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 500000 + 5;

mt19937_64 rnd(time(nullptr));

int n, m;
ull val[maxn], sum[maxn];
ll c[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
      scanf("%I64d", c + i);
      val[i] = rnd();
      sum[i] = 0;
    }
    for (int i = 1, u, v; i <= m; i++) {
      scanf("%d%d", &u, &v);
      sum[v] ^= val[u];
    }
    map<ull,ll> mp;
    for (int i = 1; i <= n; i++) {
      if (sum[i]) {
        mp[sum[i]] += c[i];
      }
    }
    ll ans = 0;
    for (auto& x: mp) {
      ans = __gcd(ans, x.second);
    }
    printf("%I64d\n", ans);
  }
  return 0;
}