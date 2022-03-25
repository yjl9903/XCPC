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
#ifdef XLor
  #define dbg(args...) cout << #args << " -> ", err(args)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 100000 + 5;

int n, pre[maxn], xx[maxn], yy[maxn], tmp[maxn];

int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}
bool join(int x, int y) {
  x = find(x); y = find(y);
  if (x == y) return false;
  pre[x] = y;
  return true;
}

int a[maxn], c[maxn], st[maxn], ed[maxn];
tuple<ll, int, int> eg[maxn];
int idx[maxn], idq[maxn];
PII p[maxn];

ll slope(int aa, int bb, int cc) {
  PII a = p[aa], b = p[bb], c = p[cc];
  ll x = 1ll * (b.second - a.second) * (c.first - b.first);
  ll y = 1ll * (c.second - b.second) * (b.first - a.first);
  return x - y;
}

ll dot(int aa, int bb) {
  PII a = p[aa], b = p[bb];
  return 1ll * a.first * b.first + 1ll * a.second * b.second;
}

void update(int xl, int xr, int ql, int qr) {
  vector<int> vec;
  for (int i = xl; i <= xr; i++) {
    if (i > xl && p[idx[i]].first == p[idx[i - 1]].first) continue;
    while (vec.size() > 1 && slope(vec[(int)vec.size() - 2], vec[(int)vec.size() - 1], idx[i]) > 0) {
      vec.pop_back();
    }
    vec.push_back(idx[i]);
  }
  vector<int> hull, mn;
  hull.push_back(vec.front());
  mn.push_back(a[vec.front()]);
  for (int i = 1; i + 1 < (int)vec.size(); i++) {
    if (slope(vec[i - 1], vec[i], vec[i + 1]) != 0) {
      hull.push_back(vec[i]);
      mn.push_back(a[vec[i]]);
    } else {
      mn[mn.size() - 1] = min(mn.back(), a[vec[i]]);
    }
  }
  hull.push_back(vec.back());
  mn.push_back(a[vec.back()]);
  for (int i = ql, j = 0; i <= qr; i++) {
    int qx = idq[i];
    while (j + 1 < (int)hull.size() && dot(qx, hull[j]) > dot(qx, hull[j + 1])) j++;
    ll tot = dot(qx, hull[j]);
    auto& r = eg[c[qx]];
    if (j + 1 < (int)hull.size() && tot == dot(qx, hull[j + 1])) {
      int u = mn[j], v = a[qx];
      if (u > v) swap(u, v);
      r = min(r, tuple<ll, int, int> { tot, u, v });
    } else {
      int u = a[hull[j]], v = a[qx];
      if (u > v) swap(u, v);
      r = min(r, tuple<ll, int, int> { tot, u, v });
    }
  }
}

bool cmpx(int lhs, int rhs) {
  return p[lhs] < p[rhs];
}

bool cmpk(int lhs, int rhs) {
  return 1ll * p[lhs].second * p[rhs].first < 1ll * p[rhs].second * p[lhs].first;
}

void solve(int l, int r) {
  if (l == r) {
    int L = st[l], R = ed[l];
    for (int i = L; i <= R; i++) {
      idx[i] = idq[i] = i;
    }
    sort(idx + L, idx + R + 1, cmpx);
    sort(idq + L, idq + R + 1, cmpk);
    return ;
  }
  int m = (l + r) / 2;
  solve(l, m);
  solve(m + 1, r);
  update(st[l], ed[m], st[m + 1], ed[r]);
  update(st[m + 1], ed[r], st[l], ed[m + 1]);

  int l1 = st[l], r1 = ed[m];
  int l2 = st[m + 1], r2 = ed[r];
  int k = st[l] - 1;
  while (l1 <= r1 && l2 <= r2) {
    if (cmpx(idx[l1], idx[l2])) {
      tmp[++k] = idx[l1++];
    } else {
      tmp[++k] = idx[l2++];
    }
  }
  while (l1 <= r1) tmp[++k] = idx[l1++];
  while (l2 <= r2) tmp[++k] = idx[l2++];
  for (int i = st[l]; i <= ed[r]; i++) {
    idx[i] = tmp[i];
  }

  l1 = st[l], r1 = ed[m];
  l2 = st[m + 1], r2 = ed[r];
  k = st[l] - 1;
  while (l1 <= r1 && l2 <= r2) {
    if (cmpk(idq[l1], idq[l2])) {
      tmp[++k] = idq[l1++];
    } else {
      tmp[++k] = idq[l2++];
    }
  }
  while (l1 <= r1) tmp[++k] = idq[l1++];
  while (l2 <= r2) tmp[++k] = idq[l2++];
  for (int i = st[l]; i <= ed[r]; i++) {
    idq[i] = tmp[i];
  }
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d%d", xx + i, yy + i);
      pre[i] = a[i] = i;
    }
    ll ans = 0;
    while (true) {
      for (int i = 1; i <= n; i++) find(i);
      sort(a + 1, a + 1 + n, [&](int lhs, int rhs) { return pre[lhs] < pre[rhs]; });
      int cnt = 1;
      for (int i = 1, j = 1; i <= n; i = j, cnt++) {
        while (j <= n && pre[a[j]] == pre[a[i]]) {
          // c[a[j]] = cnt;
          c[j] = cnt;
          p[j] = { xx[a[j]], yy[a[j]] };
          j++;
        }
        st[cnt] = i;
        ed[cnt] = j - 1;
      }
      if (cnt == 2) break;
      for (int i = 1; i < cnt; i++) {
        eg[i] = tuple<ll, int, int> { 1ll << 60, 0, 0 };
      }
      solve(1, cnt - 1);

      for (int i = 1; i < cnt; i++) {
        ll w; int u, v;
        tie(w, u, v) = eg[i];
        assert(u != 0 && v != 0);
        if (join(u, v)) {
          ans += w;
        }
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}