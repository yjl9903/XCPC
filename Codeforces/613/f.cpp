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
const int maxn = 100000 + 5;

int n, mu[maxn], a[maxn], cnt[maxn];
vector<int> d[maxn];

int query(int x) {
  int r = 0;
  for (int i: d[x]) r += mu[i] * cnt[i];
  return r;
}
void update(int x, int v) {
  for (int i: d[x]) cnt[i] += v;
}

int main() {
  mu[1] = 1;
  for (int i = 1; i < maxn; i++) {
    for (int j = i; j < maxn; j += i) {
      d[j].push_back(i);
    }
    if (i > 1) {
      if (i / d[i][1] % d[i][1]) {
        mu[i] = -mu[i / d[i][1]];
      } else {
        mu[i] = 0;
      }
    }
  }
  scanf("%d", &n);
  ll ans = 0;
  for (int i = 1, x; i <= n; i++) {
    scanf("%d", &x); a[x]++;
    if (a[x] == 2) {
      ans = max(ans, 1ll * x);
    }
  }
  for (int i = 1; i < maxn; i++) {
    vector<int> stk;
    for (int j = maxn / i * i; j > 0; j -= i) {
      if (!a[j]) continue;
      int cnt = query(j / i);
      while (cnt) {
        if (__gcd(stk.back(), j / i) == 1) {
          cnt--;
          ans = max(ans, 1ll * stk.back() * j);
        }
        update(stk.back(), -1);
        stk.pop_back();
      }
      update(j / i, 1); stk.push_back(j / i);
    }
    while (!stk.empty()) {
      update(stk.back(), -1); stk.pop_back();
    }
  }
  printf("%I64d\n", ans);
  return 0;
}