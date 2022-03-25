#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#ifdef XLor
  #define dbg(args...) do { cout << #args << " -> "; err(args); } while (0)
  void err() { std::cout << std::endl; }
  template<typename T, typename...Args>
  void err(T a, Args...args) { std::cout << a << ' '; err(args...); }
#else
  #define dbg(...)
#endif
#define ms(a,b) memset(a,b,sizeof(a))
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
typedef pair<int,ll> PIL;
const int mod = 998244353;
const int inf = 1 << 30;
const int maxn = 200000 + 5;

int n, il[maxn], ir[maxn]; ll k;
vector<PIL> work[maxn];

namespace SegT {
  #define lson l, m, rt << 1
  #define rson m + 1, r, rt << 1 | 1
  struct Info {
    ll val; int pos;
    Info operator+(const Info& b) {
      if (val >= b.val) return (Info){ val, pos };
      else return (Info){ b.val, b.pos };
    }
    Info& operator+=(const ll b) {
      val += b; return *this;
    }
  } a[maxn * 4];

  void build(int l = 1, int r = 2e5, int rt = 1) {
    if (l == r) {
      a[rt].val = 0; a[rt].pos = l; return ;
    }
    int m = (l + r) / 2;
    build(lson); build(rson);
    a[rt] = a[rt << 1] + a[rt << 1 | 1];
  }

  ll tag[maxn * 4];
  void pushdown(int rt) {
    if (!tag[rt]) return ;
    ll t = tag[rt];
    a[rt << 1] += t; tag[rt << 1] += t;
    a[rt << 1 | 1] += t; tag[rt << 1 | 1] += t;
    tag[rt] = 0;
  }
  
  void update(int L, int R, ll x, int l = 1, int r = 2e5, int rt = 1) {
    if (L <= l && r <= R) {
      a[rt] += x; tag[rt] += x; return ;
    }
    int m = (l + r) / 2; pushdown(rt);
    if (L <= m) update(L, R, x, lson);
    if (R > m) update(L, R, x, rson);
    a[rt] = a[rt << 1] + a[rt << 1 | 1];
  }

  Info query(int L, int R, int l = 1, int r = 2e5, int rt = 1) {
    if (L <= l && r <= R) return a[rt];
    int m = (l + r) / 2; pushdown(rt);
    if (L <= m && R > m) return query(L, R, lson) + query(L, R, rson);
    else if (R <= m) return query(L, R, lson);
    else return query(L, R, rson);
  }
}

int main() {
  scanf("%d%I64d", &n, &k);
  SegT::build();
  for (int i = 1; i <= n; i++) {
    int l, r; ll p; scanf("%d%d%I64d", &l, &r, &p);
    il[i] = l; ir[i] = r;
    work[r].push_back({l, p});
  }
  ll ans = 0; int al = 1, ar = 1;
  for (int i = 1; i < maxn; i++) {
    SegT::update(1, i, -k);
    for (auto& x: work[i]) {
      SegT::update(1, x.first, x.second);
    }
    auto tot = SegT::query(1, i);
    // dbg(tot.pos, i, tot.val);
    if (tot.val > ans) {
      ans = tot.val; al = tot.pos; ar = i;
    }
  }
  if (ans == 0) puts("0");
  else {
    printf("%I64d %d %d ", ans, al, ar);
    vector<int> ans;
    for (int i = 1; i <= n; i++) {
      if (il[i] >= al && ir[i] <= ar) {
        ans.push_back(i);
      }
    }
    printf("%d\n", (int)ans.size());
    for (int x: ans) printf("%d ", x);
    puts("");
  }
  return 0;
}