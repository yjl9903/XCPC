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

int n, a, b, vx[maxn], vy[maxn];
map<ll,int> mp;
map<PII,int> mp2;

int main() {
  scanf("%d%d%d", &n, &a, &b);
  for (int i = 1, x; i <= n; i++) {
    scanf("%d%d%d", &x, vx + i, vy + i);
    mp[1ll * a * vx[i] - vy[i]]++;
    mp2[PII(vx[i], vy[i])]++;
  }
  ll ans = 0;
  for (auto& x: mp) {
    ans += 1ll * x.second * (x.second - 1);
  }
  for (auto& x: mp2) {
    ans -= 1ll * x.second * (x.second - 1);
  }
  cout << ans << endl;
  return 0;
}