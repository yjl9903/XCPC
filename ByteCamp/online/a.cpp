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
typedef long long ll;
typedef pair<ll,ll> PII;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 300000 + 5;

int n, cnt, a[maxn];

PII operator - (PII a, PII b) {
  return make_pair(a.first - b.first, a.second - b.second);
}
ll cross(PII a, PII b) {
  return a.first * b.second - a.second * b.first;
}
ll xmult(PII a, PII b, PII c) {
  // 0 -> 三点共线
  // + -> AC 在 AB 的逆时针方向
  // - -> AC 在 AB 的顺时针方向
  return cross(b - a, c - a);
}

vector<PII> stk;
bool check(PII x) {
  if ((int)stk.size() <= 2) return false;
  return xmult(stk[(int)stk.size() - 2], stk.back(), x) > 0;
}
void push(int x, int y) {
  PII v(x, y);
  while (check(v)) {
    stk.pop_back();
  }
  stk.push_back(v);
}
ll query(int x, int y) {
  assert(!stk.empty());
  ll h = stk.front().second, i = stk.front().first;
  ll ans = 1ll * x * h - 1ll * y * i;
  for (int l = 0, r = (int)stk.size() - 1; l <= r;) {
    int len = (r - l) / 3, m1 = l + len, m2 = r - len;
    ll s1 = (ll)x * stk[m1].second - (ll)y * stk[m1].first;
    ll s2 = (ll)x * stk[m2].second - (ll)y * stk[m2].first;
    if (s1 > s2) {
      r = m2 - 1;
      if (ans < s1) ans = s1;
    } else {
      l = m1 + 1;
      if (ans < s2) ans = s2;
    }
  }
  return ans - 1ll * x * a[cnt] + 1ll * y * (cnt + 1);
}

int main() {
  scanf("%d", &n);
  for (int i = 1, b, x, y; i <= n; i++) {
    scanf("%d%d%d", &b, &x, &y);
    if (b >= a[cnt]) {
      a[++cnt] = b; // b, cnt
      push(cnt, b);
    }
    printf("%lld\n", query(x, y));
  }
  return 0;
}