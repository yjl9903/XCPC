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
typedef pair<int,int> PII;
const int mod = 998244353;
const ll inf = 1ll << 60;
const int maxn = 200000 + 5;

int n, d, a[maxn];

ll F(int i) {
  return -1ll * i * d + a[i];
}
ll G(int i) {
  return 1ll * i * d + a[i];
}

struct SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1
  ll mn[maxn << 2]; int pos[maxn << 2];
  void pushup(int rt) {
    if (mn[rt << 1] < mn[rt << 1 | 1]) {
      mn[rt] = mn[rt << 1];
      pos[rt] = pos[rt << 1];
    } else {
      mn[rt] = mn[rt << 1 | 1];
      pos[rt] = pos[rt << 1 | 1];
    }
  }
  void build(function<ll(int)> f, int l = 1, int r = n, int rt = 1) {
    if (l == r) {
      mn[rt] = f(l); pos[rt] = l;
      return ;
    }
    int m = (l + r) / 2;
    build(f, lson); build(f, rson);
    pushup(rt);
  }
  void update(int i, ll x, int l = 1, int r = n, int rt = 1) {
    if (l == r) {
      mn[rt] = x; return ;
    }
    int m = (l + r) / 2;
    if (i <= m) update(i, x, lson);
    else update(i, x, rson);
    pushup(rt);
  }
  pair<ll,int> query(int L, int R, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) return { mn[rt], pos[rt] };
    int m = (l + r) / 2;
    pair<ll,int> ans(inf, -1);
    if (L <= m) ans = query(L, R, lson);
    if (R > m) ans = min(ans, query(L, R, rson));
    return ans;
  }
} pr, sf;

int pre[maxn], siz[maxn], last[maxn], nxt[maxn];
int find(int x) {
  return x == pre[x] ? x : pre[x] = find(pre[x]);
}
int join(int x, int y) {
  x = find(x); y = find(y);
  if (x == y) return false;
  if (siz[x] > siz[y]) swap(x, y);
  pre[x] = y; siz[y] += siz[x];
  return true;
}

int main() {
  scanf("%d%d", &n, &d);
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    pre[i] = i; siz[i] = 1;
  }
  pr.build(F); sf.build(G);
  ll ans = 0;
  for (int T = 1; T <= 20; T++) {
    for (int i = 1; i <= n; i++) last[i] = 0;
    for (int i = 1; i <= n; i++) {
      nxt[i] = last[find(i)];
      last[find(i)] = i;
    }
    vector<PII> egs;
    for (int i = 1; i <= n; i++) {
      if (i != find(i)) continue;
      for (int x = last[i]; x; x = nxt[x]) {
        pr.update(x, inf); sf.update(x, inf);
      }
      ll mn = inf; int u, v;
      for (int x = last[i]; x; x = nxt[x]) {
        if (x < n) {
          auto r = sf.query(x + 1, n);
          ll sum = r.first + F(x);
          if (r.second != -1 && sum < mn) {
            mn = sum; u = x; v = r.second;
          }
        }
        if (x > 1) {
          auto r = pr.query(1, x - 1);
          ll sum = r.first + G(x);
          if (r.second != -1 && sum < mn) {
            mn = sum; u = x; v = r.second;
          }
        }
      }
      if (mn < inf) {
        egs.emplace_back(u, v);
      }
      for (int x = last[i]; x; x = nxt[x]) {
        pr.update(x, F(x)); sf.update(x, G(x));
      }
    }
    if (egs.empty()) break;
    for (auto& e: egs) {
      int u = e.first,  v = e.second;
      if (join(u, v)) {
        ans += 1ll * d * abs(u - v) + a[u] + a[v];
      }
    }
  }
  cout << ans << endl;
  return 0;
}