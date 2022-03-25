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

int n, b[maxn];

int main() {
  scanf("%d", &n);
  map<int,ll> mp;
  for (int i = 1; i <= n; i++) {
    scanf("%d", b + i);
    mp[b[i] - i] += b[i];
  }
  ll ans = 0;
  for (auto& x: mp) ans = max(ans, x.second);
  cout << ans << endl;
  return 0;
}