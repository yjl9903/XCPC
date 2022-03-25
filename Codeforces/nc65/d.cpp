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
  #define dbg(args...) cout << "\033[32;1m" << #args << " -> ", err(args)
  void err() { std::cout << "\033[39;0m" << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int mod = 998244353;
const ll inf = 1ll << 62;
const int maxn = 200000 + 5;

int n, m, h[maxn];
int ql[maxn], qr[maxn], qw[maxn];

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1
  ll mn[maxn << 2], tag[maxn << 2];
  void build(int l = 1, int r = n, int rt = 1) {
    if (l == r) {
      mn[rt] = h[l]; return ;
    }
    int m = (l + r) / 2;
    build(lson); build(rson);
    mn[rt] = min(mn[rt << 1], mn[rt << 1 | 1]);
  }
  void pushdown(int rt) {
    ll t = tag[rt];
    mn[rt << 1] -= t;
    tag[rt << 1] += t;
    mn[rt << 1 | 1] -= t;
    tag[rt << 1 | 1] += t;
    tag[rt] = 0;
  }
  void update(int L, int R, int x, int l = 1, int r = n, int rt = 1) {
    if (L <= l && r <= R) {
      mn[rt] -= x; tag[rt] += x;
      return ;
    }
    int m = (l + r) / 2; pushdown(rt);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    mn[rt] = min(mn[rt << 1], mn[rt << 1 | 1]);
  }
};

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) scanf("%d", h + i);
  SegT::build();
  vector<PII> evs;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d%d", ql + i, qr + i, qw + i);
    evs.emplace_back(ql[i], i);
    evs.emplace_back(qr[i] + 1, -i);
    SegT::update(ql[i], qr[i], qw[i]);
  }
  sort(begin(evs), end(evs), [&](PII a, PII b) {
    return a.first < b.first;
  });
  dbg(SegT::mn[1]);
  int p = 0; ll ans = 0;
  for (int i = 1; i <= n; i++) {
    while (p < m + m && evs[p].first == i) {
      if (evs[p].second > 0) {
        int id = evs[p].second;
        SegT::update(ql[id], qr[id], -qw[id]);
      } else {
        int id = -evs[p].second;
        SegT::update(ql[id], qr[id], qw[id]);
      }
      p++;
    }
    ll mn = SegT::mn[1];
    dbg(i, mn);
    ans = max(ans, h[i] - mn);
  }
  cout << ans;
  return 0;
}