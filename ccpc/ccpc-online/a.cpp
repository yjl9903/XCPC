#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>
#include <functional>
#include <algorithm>
#include <utility>
#include <vector>
#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 400000 + 5;

int n, nn, L[maxn], R[maxn], H[maxn];
vector<int> lsh;

namespace SegTC {
  int cnt[maxn << 2], len[maxn << 2];
  void upd(int rt, int l, int r) {
    if (cnt[rt]) {
      len[rt] = lsh[r] - lsh[l - 1];
    } else if (l < r) {
      len[rt] = len[rt << 1] + len[rt << 1 | 1];
    } else {
      len[rt] = 0;
    }
  }
  void build(int l = 1, int r = nn, int rt = 1) {
    cnt[rt] = len[rt] = 0;
    if (l == r) return ;
    int m = (l + r) / 2;
    build(lson);
    build(rson);
  }
  void update(int L, int R, int l = 1, int r = nn, int rt = 1) {
    if (L <= l && r <= R) {
      cnt[rt]++;
      upd(rt, l, r);
      return ;
    }
    int m = (l + r) / 2;
    if (L <= m) update(L, R, lson);
    if (R > m) update(L, R, rson);
    upd(rt, l, r);
  }

  int ans() {
    return len[1];
  }
}

namespace SegTB {
  ll a[maxn << 2];
  int al[maxn << 2], ar[maxn << 2], cnt[maxn << 2];
  int mn[maxn << 2], smn[maxn << 2];

  void pushup(int rt) {
    int ls = rt << 1, rs = rt << 1 | 1;

    al[rt] = al[ls];
    ar[rt] = ar[rs];
    if (mn[ls] == mn[rs]) {
      mn[rt] = mn[ls];
      smn[rt] = min(smn[ls], smn[rs]);
    } else if (mn[ls] < mn[rs]) {
      mn[rt] = mn[ls];
      smn[rt] = min(smn[ls], mn[rs]);
    } else if (mn[ls] > mn[rs]) {
      mn[rt] = mn[rs];
      smn[rt] = min(smn[rs], mn[ls]);
    } else {
      assert(false);
    }

    cnt[rt] = 0;
    if (mn[rt] == mn[ls]) {
      cnt[rt] += cnt[ls];
    }
    if (mn[rt] == mn[rs]) {
      cnt[rt] += cnt[rs];
    }
    if (ar[ls] == mn[rt] && al[rs] != mn[rt]) {
      cnt[rt]++;
    } else if (ar[ls] != mn[rt] && al[rs] == mn[rt]) {
      cnt[rt]++;
    }
    a[rt] = a[ls] + a[rs] + abs(ar[ls] - al[rs]);
  }

  void build(int l = 1, int r = nn, int rt = 1) {
    if (l == r) {
      a[rt] = 0;
      cnt[rt] = 0;
      al[rt] = ar[rt] = 0;
      mn[rt] = 0;
      smn[rt] = inf;
      return ;
    }
    int m = (l + r) / 2;
    build(lson);
    build(rson);
    pushup(rt);
  }

  void upd(int rt, int x) {
    al[rt] = max(al[rt], x);
    ar[rt] = max(ar[rt], x);
    a[rt] -= 1ll * (x - mn[rt]) * cnt[rt];
    mn[rt] = x;
  }
  void update(int L, int R, int x, int l = 1, int r = nn, int rt = 1) {
    if (L <= l && r <= R) {
      if (x <= mn[rt]) return ;
      if (x < smn[rt]) {
        upd(rt, x);
        return ;
      }
      assert(l != r);
    }
    int m = (l + r) / 2;
    {
      int ls = rt << 1, rs = rt << 1 | 1;
      if (mn[ls] < mn[rt]) {
        upd(ls, mn[rt]);
      }
      if (mn[rs] < mn[rt]) {
        upd(rs, mn[rt]);
      }
    }
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    pushup(rt);
  }

  ll ans() {
    return a[1];
  }
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    lsh.clear();
    lsh.push_back(0);
    lsh.push_back(inf);
    for (int i = 1; i <= n; i++) {
      scanf("%d%d%d", L + i, R + i, H + i);
      lsh.push_back(L[i]);
      lsh.push_back(R[i]);
    }
    sort(lsh.begin(), lsh.end());
    lsh.resize(unique(lsh.begin(), lsh.end()) - lsh.begin());
    nn = lsh.size();
    auto gid = [&](int x) {
      return lower_bound(lsh.begin(), lsh.end(), x) - lsh.begin() + 1;
    };
    SegTC::build();
    SegTB::build();
    for (int i = 1; i <= n; i++) {
      int l = gid(L[i]);
      int r = gid(R[i]) - 1;
      assert(l <= r);
      SegTC::update(l, r);
      SegTB::update(l, r, H[i]);
      printf("%lld\n", SegTB::ans() + 2ll * SegTC::ans());
    }
  }
  return 0;
}