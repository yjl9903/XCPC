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

int n, k, cnt[maxn];
ll a[maxn];

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d", &n, &k);
    vector<ll> v = {1};
    while (v.back() <= 1e16) {
      v.push_back(1ll * v.back() * k);
    }
    for (int i = 0; i <= (int)v.size(); i++) {
      cnt[i] = 0;
    }
    bool flag = true;
    for (int i = 1; i <= n; i++) {
      scanf("%I64d", a + i);
      ll x = a[i];
      for (int i = (int)v.size() - 1; i >= 0; i--) {
        if (x >= v[i]) {
          x -= v[i]; cnt[i]++;
        }
      }
      if (x) {
        flag = false;
      }
    }
    for (int i = 0; i < (int)v.size(); i++) {
      if (cnt[i] > 1) {
        flag = false;
      }
    }
    puts(flag ? "YES" : "NO");
  }
  return 0;
}