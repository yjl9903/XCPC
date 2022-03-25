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
using ll = long long;
using PII = pair<int,int>;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 300000 + 5;

int n, h[maxn], b[maxn], pos[maxn], L[maxn], R[maxn];
vector<ll> evs[maxn];

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1

  ll a[maxn << 2];
  void update(int i, ll x, int l = 0, int r = n, int rt = 1) {
    if (l == r) {
      a[rt] = x;
      return ;
    }
    int m = (l + r) / 2;
    if (i <= m) update(i, x, lson);
    else update(i, x, rson);
    a[rt] = max(a[rt << 1], a[rt << 1 | 1]);
  }

  ll query(int L, int R, int l = 0, int r = n, int rt = 1) {
    if (L <= l && r <= R) return a[rt];
    int m = (l + r) / 2;
    if (R <= m) return query(L, R, lson);
    else if (L > m) return query(L, R, rson);
    else return max(query(L, R, lson), query(L, R, rson));
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", h + i);
    pos[h[i]] = i;
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", b + i);
  }
  set<int> st;
  for (int i = 1; i <= n; i++) {
    int p = pos[i];
    auto it = st.upper_bound(p);
    if (it != st.end()) {
      R[p] = *it;
    } else {
      R[p] = n + 1;
    }
    if (it != st.begin()) {
      it--;
      L[p] = *it;
    } else {
      L[p] = 0;
    }
    st.insert(p);
  }
  // for (int i = 1; i <= n; i++) {
  //   dbg(i, L[i], R[i]);
  // }
  multiset<ll> val;
  for (int i = 1; i <= n; i++) {
    for (auto& x: evs[i]) {
      val.erase(val.find(x));
    }
    ll cur = SegT::query(L[i], i - 1) + b[i];
    ll ans = cur;
    if (!val.empty()) {
      ans = max(ans, *val.rbegin());
    }
    SegT::update(i, ans);
    val.insert(cur);
    evs[R[i]].emplace_back(cur);
  }
  printf("%lld\n", SegT::query(n, n));
  return 0;
}