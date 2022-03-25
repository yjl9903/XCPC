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
#include <random>
#include <ctime>
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 300000 + 5;

mt19937_64 rnd(time(nullptr));

int n, a[maxn];
ll val[maxn], pre[maxn], b[maxn];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    val[i] = rnd();
    pre[i] = val[i] ^ pre[i - 1];
  }
  ll ans = 0;
  for (int tp = 0; tp < 2; tp++) {
    for (int i = 1; i <= n; i++) {
      b[i] = val[a[i]] ^ b[i - 1];
    }
    for (int i = 1; i <= n; i++) {
      if (a[i] > 1) continue;
      set<int> vis = { 1 };
      ans += tp == 0;
      for (int j = i + 1, mx = 1; j <= n; j++) {
        if (vis.count(a[j])) break;
        mx = max(mx, a[j]); vis.insert(a[j]);
        if (j >= mx && pre[mx] == (b[j] ^ b[j - mx])) {
          ans++;
        }
      }
    }
    reverse(a + 1, a + 1 + n);
  }
  cout << ans << endl;
  return 0;
}