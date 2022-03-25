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
const int maxn = 500000 + 5;

int n, a[maxn];
ll ans[maxn], cnt[maxn], c[maxn];
PII b[maxn];

void update(int i, ll x) {
  for (; i < maxn; i += i & -i) c[i] += x;
}
void update(int i) {
  update(i, 1ll * (cnt[i] + 1) * cnt[i] / 2 - 1ll * cnt[i] * (cnt[i] - 1) / 2);
  cnt[i]++;
}
ll query(int i) {
  ll r = 0;
  for (; i; i -= i & -i) r += c[i];
  return r;
}
ll query(int l, int r) {
  return query(r) - query(l - 1);
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d%d", a + i, &b[i].first, &b[i].second);
    cnt[a[i]]++;
  }
  for (int i = 1; i < maxn; i++) {
    cnt[i] = 1ll * cnt[i] * (cnt[i] - 1) / 2 + cnt[i - 1];
  }
  for (int i = 1; i <= n; i++) {
    ans[i] = cnt[b[i].second] - cnt[b[i].first - 1];
  }
  ms(cnt, 0);
  for (int i = 1; i <= n; i++) {
    update(a[i]); ans[i] -= query(b[i].first, b[i].second);
  }
  ms(cnt, 0); ms(c, 0);
  for (int i = n; i >= 1; i--) {
    update(a[i]); ans[i] -= query(b[i].first, b[i].second);
  }
  for (int i = 1; i <= n; i++) {
    printf("%lld ", ans[i]);
  }
  return 0;
}