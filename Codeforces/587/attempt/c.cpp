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

int n, k;
char s[maxn];

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1
  ll mn[maxn << 2], tag[maxn << 2];
  void build(int l = 0, int r = n, int rt = 1) {
    mn[rt] = tag[rt] = inf;
    if (l == r) return ;
    int m = (l + r) / 2;
    build(lson); build(rson);
  }
  void pushdown(int rt) {
    if (tag[rt] == inf) return ;
    ll t = tag[rt];
    mn[rt << 1] = mn[rt << 1 | 1] = t;
    tag[rt << 1] = tag[rt << 1 | 1] = t;
    tag[rt] = inf;
  }
  void update(int L, int R, ll x, int l = 0, int r = n, int rt = 1) {
    if (L <= l && r <= R) {
      mn[rt] = x; tag[rt] = x; return ;
    }
    int m = (l + r) / 2; pushdown(rt);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    mn[rt] = min(mn[rt << 1], mn[rt << 1 | 1]);
  }
  ll query(int L, int R, int l = 0, int r = n, int rt = 1) {
    if (L <= l && r <= R) return mn[rt];
    ll ans = inf, m = (l + r) / 2; pushdown(rt);
    if (L <= m) ans = query(L, R, lson);
    if (R > m) ans = min(ans, query(L, R, rson));
    return ans;
  }
}

int main() {
  scanf("%d%d%s", &n, &k, s + 1);
  SegT::build();
  vector< tuple<int,int,int> > evs;
  for (int i = 1; i <= n; i++) {
    if (s[i] == '1') {
      evs.emplace_back(max(i - k, 1), min(i + k, n), i);
    } else {
      evs.emplace_back(i, i, i);
    }
  }
  sort(evs.begin(), evs.end(), [](auto a, auto b) {
    return get<1>(a) < get<1>(b);
  });
  for (int i = 1, p = 0; i <= n; i++) {
    
  }
  cout << SegT::query(n, n) << endl;
  return 0;
}