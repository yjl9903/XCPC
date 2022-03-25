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

int gid(int x) {
  return lower_bound(begin(lsh), end(lsh), x) - begin(lsh) + 1;
}

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
void update(int L, int R, int x, int l = 1, int r = nn, int rt = 1) {
  if (L <= l && r <= R) {
    cnt[rt]++;
    upd(rt, l, r);
    return ;
  }
  int m = (l + r) / 2;
  if (L <= m) update(L, R, x, lson);
  if (R > m) update(L, R, x, rson);
  upd(rt, l, r);
}

namespace SegTB {
  int mx[maxn << 2], mn[maxn << 2], cnt[maxn << 2], se[maxn << 2], add[maxn << 2];

  void pushup(int rt) {
    if (mx[rt << 1] == mx[rt << 1 | 1]) {
      se[rt] = max(se[rt << 1], se[rt << 1 | 1]);
      mx[rt] = mx[rt << 1];
    } else if (mx[rt << 1] < mx[rt << 1 | 1]) {
      se[rt] = max(mx[rt << 1], se[rt << 1 | 1]);
      mx[rt] = mx[rt << 1 | 1];
    } else {
      se[rt] = max(mx[rt << 1 | 1], se[rt << 1]);
      mx[rt] = mx[rt << 1];
    }
    mn[rt] = min(mn[rt << 1], mn[rt << 1 | 1]);
  }
  void pushdown(int rt) {
    if (add[rt] == -1) return;
    // 区间覆盖
    int& t = add[rt];
    int ls = rt << 1, rs = rt << 1 | 1;
    if (mx[ls] > t && t > se[ls]) {
      add[ls] = mx[ls] = t;
    }
    if (mx[rs] > t && t > se[rs]) {
      add[rs] = mx[rs] = t;
    }
    t = -1;
  }
  void build(int l = 1, int r = nn, int rt = 1) {
    add[rt] = -1; 
    if (l == r) {
      mn[rt] = mx[rt] = 0;
      se[rt] = -1;
      return;
    }
    int m = l + r >> 1;
    build(lson); build(rson);
    pushup(rt);
  }
  void update(int L, int R, int t, int l = 1, int r = nn, int rt = 1) {
    // if (mx[rt] <= t) return;
    if (mn[rt] > t) return ;
    if (L <= l && r <= R && mx[rt] <= t) {
      mn[rt] = mx[rt] = add[rt] = t;
      return;
    }
    if (l == r) return ;
    int m = l + r >> 1; 
    pushdown(rt);
    if (L <= m) update(L, R, t, lson);
    if (R > m) update(L, R, t, rson);
    pushup(rt);
  }
  int query(int x, int l = 1, int r = nn, int rt = 1) {
    if (l == r) return mx[rt];
    int m = (l + r) / 2;
    pushdown(rt);
    if (x <= m) return query(x, lson);
    else return query(x, rson);
  }
  void print() {
    for (int i = 1; i <= nn; i++) {
      dbg(i, query(i));
    }
  }
  int cal(int pos) {
    int idR = gid(pos);
    int hR = query(idR);
    int idL = gid(pos - 1);
    if (idL == idR) {
      idL--;
    }
    int hL = idL == 0 ? 0 : query(idL);
    return abs(hR - hL);
  }
}


int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d", &n);
    lsh.clear();
    for (int i = 1; i <= n; i++) {
      scanf("%d%d%d", L + i, R + i, H + i);
      lsh.push_back(L[i]);
      lsh.push_back(R[i]);
    }
    sort(begin(lsh), end(lsh));
    lsh.resize(unique(begin(lsh), end(lsh)) - begin(lsh));
    nn = lsh.size();
    lsh.push_back(inf);
    build();
    SegTB::build();
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
      ans -= SegTB::cal(L[i]);
      ans -= SegTB::cal(R[i]);
      // dbg(ans);
      update(gid(L[i]), gid(R[i]) - 1, H[i]);
      SegTB::update(gid(L[i]), gid(R[i]) - 1, H[i]);
      // SegTB::print();
      ans += SegTB::cal(L[i]);
      // dbg(ans);
      ans += SegTB::cal(R[i]);
      // dbg(ans);
      printf("%lld %lld\n", ans + 2ll * len[1]);
    }
  }
  return 0;
}