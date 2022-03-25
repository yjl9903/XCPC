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
const ll inf = 2e18;
const int maxn = 300 + 5;

struct LineContainer  {
  static bool modeQ; // Toggles operator < mode

  struct Line {
    mutable ll a, b, end;
    ll intersect(const Line& r) const {
      if (a == r.a) return b > r.b ? inf : -inf;
      ll u = b - r.b, d = r.a - a;
      return u / d - ((u ^ d) < 0 && u % d);
    }
    bool operator<(const Line& r) const {
      return modeQ ? end < r.end : a < r.a;
    }
  };

  multiset<Line> S;
  void clear() { S.clear(); }

  // Updates segment end
  bool update(multiset<Line>::iterator it) {
    auto cur = it++; cur->end = inf;
    if (it == S.end()) return false;
    cur->end = cur->intersect(*it);
    return cur->end >= it->end;
  }

  // Insert f(x) = ax + b, time: O(log n)
  void insert(ll a, ll b) {
    auto it = S.insert({ a, b, inf });
    while (update(it)) it = --S.erase(++it);
    while (it != S.begin() && update(--it)) {
      update(it = --S.erase(++it));
    }
    while (it != S.begin() && update(--it)) {
      update(it = --S.erase(++it));
    }
  }

  // Query max(f(x)), time: O(log n)
  ll query(ll x) {
    assert(!S.empty());
    modeQ = 1;
    auto l = *S.lower_bound({ 0, 0, x });
    modeQ = 0;
    return l.a * x + l.b;
  }
} f[maxn];

bool LineContainer::modeQ = false;

int n, Q[maxn][maxn], sQ[maxn][maxn];

int qcnt(int i, int l, int r) {
  assert(l <= i && i <= r);
  return sQ[i][r] + sQ[l - 1][i - 1] - sQ[i][i - 1] - sQ[l - 1][r];
}

ll g[maxn][maxn];
ll dfs(int l, int r) {
  if (l > r) return 0ll;
  if (g[l][r] != -inf) return g[l][r];
  ll ans = -inf;
  for (int i = l; i <= r; i++) {
    ll cur = dfs(l, i - 1) + dfs(i + 1, r);
    cur += f[i].query(qcnt(i, l, r));
    ans = max(ans, cur);
  }
  return g[l][r] = ans;
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    int sum = 0;
    for (int j = 0; j < i; j++) {
      sQ[i][j] = sQ[i - 1][j];
    }
    for (int j = i; j <= n; j++) {
      scanf("%d", &Q[i][j]);
      sum += Q[i][j];
      sQ[i][j] = sum + sQ[i - 1][j];
    }
  }
  for (int i = 1; i <= n; i++) {
    int k;
    scanf("%d", &k);
    for (int j = 0; j < k; j++) {
      ll v, b;
      scanf("%lld%lld", &v, &b);
      f[i].insert(v, -b);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      g[i][j] = -inf;
    }
  }
  printf("%lld\n", dfs(1, n));
  return 0;
}