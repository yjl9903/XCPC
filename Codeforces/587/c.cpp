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
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, k, tag[maxn];
char s[maxn];
ll ans = 0;

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1
  ll sum[maxn << 2], tag[maxn << 2];
  void build(int l = 0, int r = n, int rt = 1) {
    sum[rt] = tag[rt] = 0;
    if (l == r) return ;
    int m = (l + r) / 2;
    build(lson); build(rson);
  }
  void pushdown(int rt, int ln, int rn) {
    if (!tag[rt]) return ;
    ll t = tag[rt];
    sum[rt << 1] = ln; sum[rt << 1 | 1] = rn;
    tag[rt << 1] = tag[rt << 1 | 1] = t;
    tag[rt] = 0;
  }
  void update(int L, int R, ll x, int l = 0, int r = n, int rt = 1) {
    if (L <= l && r <= R) {
      sum[rt] = r - l + 1; tag[rt] = 1;
      return ;
    }
    int m = (l + r) / 2; pushdown(rt, m - l + 1, r - m);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
  }
  ll query(int L, int R, int l = 0, int r = n, int rt = 1) {
    if (L <= l && r <= R) return sum[rt];
    ll ans = 0, m = (l + r) / 2; pushdown(rt, m - l + 1, r - m);
    if (L <= m) ans = query(L, R, lson);
    if (R > m) ans += query(L, R, rson);
    return ans;
  }
}

void upd(int i) {
  if (i > n || i < 0) return ;
  if (s[i] == '1') {
    int l = max(1, i - k), r = min(n, i + k);
    if (SegT::query(l, r) < r - l + 1) {
      ans += i;
      SegT::update(l, r, 1);
    }
  }
}

int main() {
  scanf("%d%d%s", &n, &k, s + 1);
  SegT::build();
  
  cout << ans << endl;
  return 0;
}